#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library
struct mydata {
	char msg[20];

};
struct XTServerInfo {
	char* host;
	u_short port;
	u_short max_clients;
};

class Server {
public:
	Server(XTServerInfo);
	int Init();
	int End();

	WSADATA wsa;
	SOCKET master;
	SOCKET new_socket;
	SOCKET clients[30];

private:
	XTServerInfo info;
	u_short max_clients;

};

