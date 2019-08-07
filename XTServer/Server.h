#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdint.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library

/*
LC_ALL 	selecciona toda la configuración regional
LC_COLLATE 	selecciona la categoría cotejo de la configuración regional
LC_CTYPE 	selecciona la categoría de clasificación caracteres del entorno local
LC_MONETARY 	selecciona la categoría de formato monetario de la configuración regional
LC_NUMERIC 	selecciona la categoría de formato numérico de la configuración regional
LC_TIME 	selecciona el tiempo de la categoría de formato de la configuración regional

*/

typedef struct {
	unsigned short Keep_Alive_Header;
	unsigned short Keep_Alive_ID;
	unsigned long Keep_Alive_Device_ID;
} Keep_Alivestruct;




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

	void (*CallConection)(SOCKET master, SOCKET client, SOCKET clients[], int index, short int max_clients);
	void (*CallMsgReceived)(SOCKET master, SOCKET client, char * buffer, int valread, int index);

	void (*CallClientError)(SOCKET master, SOCKET client, char* buffer, int valread, int index, int error_code);
	void (*CallClientError2)(int index);
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

