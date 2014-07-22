#include <winsock.h>
#include <iostream>
#include <windows.h>

#pragma comment (lib, "ws2_32.lib")

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

	int Val = InitWinSock();
	//if Val is not zero, init fails
	if (Val) {
		MessageBox(NULL, "Winsock Init Error", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	//mem alloc
	Connects = new SOCKET[DEFAULT_SOCKET_ARRAY_SIZE];

	//create listen socket and connect socket
	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);

	//set local host
	addr.sin_addr.s_addr = inet_addr("192.168.1.103");
	//set port to 8000
	addr.sin_port = htons(8000);
	//type of connection
	addr.sin_family = AF_INET;

	//bind listen socket to the address struct
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

	//listen to incoming connection; max server storage size is set to DEFAULT_SOCKET_ARRAY_SIZE
	listen(sListen, DEFAULT_SOCKET_ARRAY_SIZE);

	while (true) {
		if (sConnect = accept(sListen, (SOCKADDR*)&addr, &addrlen)) {
			std::cout << "New incoming connection.\n";
			//the server will assign the new coming client an unique ID
			char* client_ID = new char[DEFAULT_CLIENT_ID_SIZE];
			ZeroMemory(client_ID, DEFAULT_CLIENT_ID_SIZE);
			sprintf_s(client_ID, DEFAULT_CLIENT_ID_SIZE, "%d", socket_counter);
			//send it to client through its socket
			send(sConnect, client_ID, DEFAULT_CLIENT_ID_SIZE, NULL);
			Connects[socket_counter++] = sConnect;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ServerThread, (LPVOID)(socket_counter - 1), NULL, NULL);
		}
		Sleep(DEFAULT_ACCEPT_INTERVAL);
	}

}