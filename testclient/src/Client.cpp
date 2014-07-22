#include <iostream>
#include <winsock.h>
#include <windows.h>

#pragma comment (lib, "ws2_32.lib")

#define DEFAULT_RECEIVE_INTERVAL 50
#define DEFAULT_MESSAGE_SIZE 256
#define DEFAULT_CLIENT_ID_SIZE 64

SOCKET sConnect;

SOCKADDR_IN addr;

int Startup_WinSock() {
	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);

	int Val = WSAStartup(DLLVersion, &wsaData);

	return Val;
}

int ClientThread() {
	char* Buffer = new char[DEFAULT_MESSAGE_SIZE];
	int size = 0;

	while (true) {
		ZeroMemory(Buffer, 256);
		if ((size = recv(sConnect, Buffer, DEFAULT_MESSAGE_SIZE, NULL) > 0))
			std::cout << Buffer << std::endl;
		Sleep(DEFAULT_RECEIVE_INTERVAL);
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

	int Val = Startup_WinSock();

	if (Val) {
		std::cerr << "Init fails.\n";
		exit(1);
	}

	sConnect = socket(AF_INET, SOCK_STREAM, NULL);

	addr.sin_addr.s_addr = inet_addr("192.168.1.103");
	addr.sin_port = htons(8000);
	addr.sin_family = AF_INET;

	std::cout << "Press [Enter] to continue.\n";
	std::cin.get();

	Val = connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));

	if (Val) {
		std::cerr << "Can't connect to server.\n";
		exit(1);
	}
	else {
		system("cls");

		int ID;
		char* nID = new char[DEFAULT_CLIENT_ID_SIZE];
		char* msg = new char[DEFAULT_CLIENT_ID_SIZE];
		ZeroMemory(nID, DEFAULT_CLIENT_ID_SIZE);
		ZeroMemory(msg, DEFAULT_CLIENT_ID_SIZE);

		recv(sConnect, nID, DEFAULT_CLIENT_ID_SIZE, NULL);

		std::cout << "Your ID: " << nID << std::endl;
		std::cout << "Press [Enter] to continue to chat.\n";
		std::cin.get();

		system("cls");

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL);

		while (true) {
			char* MSG = new char[DEFAULT_MESSAGE_SIZE];
			ZeroMemory(MSG, DEFAULT_MESSAGE_SIZE);

			std::cin.getline(MSG, DEFAULT_MESSAGE_SIZE);
			send(sConnect, MSG, DEFAULT_MESSAGE_SIZE, NULL);

			Sleep(DEFAULT_RECEIVE_INTERVAL);
		}
	}
}