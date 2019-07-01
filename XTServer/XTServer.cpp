#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Server.h"
void _CallConection(SOCKET master, SOCKET client);
void _CallMsgReceived(SOCKET master, SOCKET client, char* buffer, int valread);

int main()
{
	
	system("cls");
	std::cout << "XT Server v1.0 !!!\n";
	ServerInfo info;
	info.host = (char*)"127.0.0.1";
	info.port = 12345;
	info.max_clients = 30;
	Server* s = new Server(info);
	s->CallConection = _CallConection;
	s->CallMsgReceived = _CallMsgReceived;
	s->init();
}

void _CallConection(SOCKET master, SOCKET client) {
	/*
	puts("is conecting, wait please!");

	char buffer[] = "yes";
	send(client, buffer, 3, 0);
*/
}

void _CallMsgReceived(SOCKET master, SOCKET client, char* buffer, int valread) {
	puts("responding...");

	char buffer_aux[] = "<<iniciando>>";

	if (buffer[0] == '*') {
		send(client, buffer_aux, strlen(buffer_aux), 0);
	} else {
		strcat((char*)buffer, "-yanny-");
		send(client, buffer, valread+5, 0);
	}

	
	
}