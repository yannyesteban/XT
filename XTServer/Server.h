#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdint.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library


struct InfoClient {
	char device_id[10];

};

struct mydata {
	char msg[20];

};

struct ServerInfo {
	char* host;
	u_short port;
	u_short max_clients;
};

class Server {
public:
	Server(ServerInfo _info) ;

	void init();
	void setOptions();

	void start();
	void end();

	void (*CallConection)(SOCKET master, SOCKET client);
	void (*CallMsgReceived)(SOCKET master, SOCKET client, char * buffer, int valread);
private:
	WSADATA wsa;
	SOCKET master;
	
	SOCKET new_socket;
	SOCKET clients[30];
	ServerInfo Info;
	u_short max_clients;
	
	struct sockaddr_in server, address;

	void _startUp();
	void _createSocket();
	void _bing();
	void _listen();

};

