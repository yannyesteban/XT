#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
//#include "Counter.h"

struct mydata {
	char msg[20];

};

struct ClientInfo {
	char* host;
	u_short port;
	
};

class Client {

public:
	Client(ClientInfo _info);


private:

	ClientInfo Info;
	WSADATA wsa;
	SOCKET master;

	int _startUp();
	int _createSocket();


	
protected:


};

