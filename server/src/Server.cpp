#include <WS2tcpip.h>
#include <iostream>
#include <windows.h>

#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"ws2_32.lib")

//the max sockets to store in server buffer
#define DEFAULT_SOCKET_ARRAY_SIZE 64
//the amount of time in milisec in between every server-acceptance
#define DEFAULT_ACCEPT_INTERVAL 50
#define DEFAULT_MESSAGE_SIZE 256
#define DEFAULT_CLIENT_ID_SIZE 64

SOCKADDR_IN addr;  //addr struct: contains info about server address and port
int addrlen = sizeof(addr);
int socket_counter = 0;
SOCKET sConnect;   //server socket for incoming connection
SOCKET sListen;    //server listener socket
SOCKET* Connects;  //server socket array: stores connected client sockets

int InitWinSock() {
	int Val = 0;
	WSAData wsaData;
	WORD DLLVERSION = MAKEWORD(2, 2);
	//initialize winsock
	Val = WSAStartup(DLLVERSION, &wsaData);

	return Val;
}

int ServerThread(int ID) {
	char* RecvBuffer = new char[DEFAULT_MESSAGE_SIZE];
	char* SendBuffer = new char[DEFAULT_MESSAGE_SIZE];
	int size = 0;

	while (true) {
		ZeroMemory(RecvBuffer, DEFAULT_MESSAGE_SIZE);
		if ((size = recv(Connects[ID], RecvBuffer, DEFAULT_MESSAGE_SIZE, NULL)) > 0) {
			for (int i = 0; i < socket_counter; i++) {
				ZeroMemory(SendBuffer, DEFAULT_MESSAGE_SIZE);
				if (Connects[i] == Connects[ID]) {
					sprintf_s(SendBuffer, DEFAULT_MESSAGE_SIZE, "You said: %s", RecvBuffer);
					send(Connects[ID], SendBuffer, DEFAULT_MESSAGE_SIZE, NULL);
				}
				else {
					sprintf_s(SendBuffer, DEFAULT_MESSAGE_SIZE, "Client[%d] said: %s", ID, RecvBuffer);
					send(Connects[i], SendBuffer, DEFAULT_MESSAGE_SIZE, NULL);
				}
			}
		}
	}

	return 0;
}

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8000"

#include <wininet.h>

namespace IPuR
{
	//download file from WWW in a buffer
	bool WWWFileBuffer(char *host, char *path, char *outBuffer, int outBufferSize)
	{
		bool retval = false;
		LPTSTR AcceptTypes[2] = { TEXT("*/*"), NULL };
		DWORD dwSize = outBufferSize - 1, dwFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE;
		HINTERNET opn = NULL, con = NULL, req = NULL;
		opn = InternetOpen(TEXT("Evilzone.org"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		if (!opn)
			return retval;
		con = InternetConnect(opn, host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
		if (!con)
			return retval;
		req = HttpOpenRequest(con, TEXT("GET"), path, HTTP_VERSION, NULL, (LPCTSTR*)AcceptTypes, dwFlags, 0);
		if (!req)
			return retval;
		if (HttpSendRequest(req, NULL, 0, NULL, 0))
		{
			DWORD statCodeLen = sizeof(DWORD);
			DWORD statCode;
			if (HttpQueryInfo(req,
				HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
				&statCode, &statCodeLen, NULL))
			{
				if (statCode == 200 && InternetReadFile(req, (LPVOID)outBuffer, outBufferSize - 1, &dwSize))
				{
					retval = TRUE;
				}
			}
		}
		InternetCloseHandle(req);
		InternetCloseHandle(con);
		InternetCloseHandle(opn);
		return retval;
	}


	BOOL GetWanIP(char *ip, int size)
	{
		bool retval = false;
		char *tmpip = new char[150];
		memset(ip, 0, size);

		//www.whatismyip.org
		if (!retval)
		{
			memset(tmpip, 0, 150);
			WWWFileBuffer("www.whatismyip.org", NULL, tmpip, 150);
			if (strlen(tmpip) > 0 && inet_addr(tmpip) != INADDR_NONE)
			{
				retval = true;
			}
		}

		//automation.whatismyip.com/n09230945.asp
		if (!retval)
		{
			memset(tmpip, 0, 150);
			WWWFileBuffer("automation.whatismyip.com", "/n09230945.asp", tmpip, 150);
			if (strlen(tmpip) > 0 && inet_addr(tmpip) != INADDR_NONE)
			{
				retval = true;
			}
		}

		//www.showmyip.com/simple
		if (!retval)
		{
			memset(tmpip, 0, 150);
			WWWFileBuffer("www.showmyip.com", "/simple", tmpip, 150);
			if (strlen(tmpip) > 0 && inet_addr(tmpip) != INADDR_NONE)
			{
				retval = true;
			}
		}

		//myip.dnsomatic.com
		if (!retval)
		{
			memset(tmpip, 0, 150);
			WWWFileBuffer("myip.dnsomatic.com", NULL, tmpip, 150);
			if (strlen(tmpip) > 0 && inet_addr(tmpip) != INADDR_NONE)
			{
				retval = true;
			}
		}

		//checkip.dyndns.org
		if (!retval)
		{
			memset(tmpip, 0, 150);
			WWWFileBuffer("checkip.dyndns.org", NULL, tmpip, 150);
			if (strlen(tmpip) > 0)
			{
				strcpy_s(tmpip, 150, (strstr(tmpip, ":") + 2));
				int res = (int)(strstr(tmpip, "<") - tmpip);
				tmpip[res] = '\0';
				if (inet_addr(tmpip) != INADDR_NONE)
				{
					retval = true;
				}
				else
					retval = false;
			}
		}

		if (retval)
			strcpy_s(ip, size, tmpip);
		delete[] tmpip;
		return retval;
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	AllocConsole();
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode & ~ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	std::cout << "Sever initilized.\n";

	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	hostent* host = gethostbyname("fwankie.wicp.net");
	if (host == NULL)
	{
		WSACleanup();
		return FALSE;
	}

	char* pszIP = (char *)inet_ntoa(*(struct in_addr *)(host->h_addr));
	printf("host IP Address: %s\n", pszIP);


	struct sockaddr_in* saddr_in = (struct sockaddr_in*)result->ai_addr;
	printf("hostname: %s\n", inet_ntoa(saddr_in->sin_addr));
	//printf("sockaddr_in size is: %d\n", (int)sizeof(in_addr));
	saddr_in->sin_addr.S_un.S_addr = inet_addr(pszIP);

	//char ip[16];
	//IPuR::GetWanIP(ip, 16);
	//getchar();
	//printf("hostname: %s\n", ip);



	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else  {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}