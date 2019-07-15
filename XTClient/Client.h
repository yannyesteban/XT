#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Counter.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
//#include "Counter.h"

struct InfoSocket {
	SOCKET socket;
	char buffer[100];
	char tag[7]  = "SIMPLE";
	char tag2[7] = "COMPLX";
};

struct mydata {
	char msg[20];

};

struct ClientInfo {
	char* host;
	PCSTR port;
	
};

class Client {

public:
	Client(ClientInfo _info);
	void init();

private:

	ClientInfo Info;
	InfoSocket Info2;
	WSADATA wsa;
	SOCKET master;

	HANDLE hClientThread;
	DWORD dwThreadId;

	int _startUp();
	int _createSocket();
	int _listen();
	int _thread(InfoSocket &INFO);


	
protected:


};

