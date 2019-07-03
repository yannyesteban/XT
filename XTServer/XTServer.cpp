#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iterator>
#include <map> 
#include <sys/timeb.h>
#include <time.h>
#include "Server.h"

struct MsgToClient {
	char token;
	char id[10];
	char cmd[100];
};
std::map<std::string, SOCKET> clients;
std::map<std::string, SOCKET>::iterator it;

void _CallConection(SOCKET master, SOCKET client);
void _CallMsgReceived(SOCKET master, SOCKET client, char* buffer, int valread);

struct timeb start, end;
int getDiff() {
	return (int)(1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
}

int main()
{
	
	system("cls");
	std::cout << "XT Server v1.0 !!!\n";
	ServerInfo info;
	info.host = (char*)"127.0.0.1";
	info.port = 3311;
	info.max_clients = 30;
	Server* s = new Server(info);
	s->CallConection = _CallConection;
	s->CallMsgReceived = _CallMsgReceived;
	s->init();
}

void _CallConection(SOCKET master, SOCKET client) {

	ftime(&start);
	/*
	char fecha[25];//ctime devuelve 26 caracteres pero tambien se podría usar un puntero de char
	time_t current_time;
	current_time = time(NULL);
	ctime(&current_time);
	strcpy(fecha, ctime(&current_time));
	//printf("%s\n", fecha);
*/
	printf("Inicio \n\n");
	/*
	puts("is conecting, wait please!");

	char buffer[] = "yes";
	send(client, buffer, 3, 0);
*/
}

void _CallMsgReceived(SOCKET master, SOCKET client, char* buffer, int valread) {

	ftime(&end);

	printf("segundos %d\n", getDiff()/1000 );

	ftime(&start);
	/*
	char fecha[25];//ctime devuelve 26 caracteres pero tambien se podría usar un puntero de char
	time_t current_time;
	current_time = time(NULL);
	ctime(&current_time);
	strcpy(fecha, ctime(&current_time));
	printf("%s\n", fecha);
*/
	//printf("Inicio [%s]\n\n", fecha);

	printf("Conectando ---> [%s]\n", buffer);

	Keep_Alivestruct* st =(Keep_Alivestruct*)buffer;

	printf("Keep_Alive_Device_ID: %d\n",st->Keep_Alive_Device_ID);
	printf("Keep_Alive_Header: %d\n", st->Keep_Alive_Header);
	printf("Keep_Alive_ID: %d\n", st->Keep_Alive_ID);

	
	char ID[12];
	if (st->Keep_Alive_Header == 55248) {
		puts("si");

		
		//sprintf(ID, "%lu", st->Keep_Alive_Device_ID);
		_itoa_s(st->Keep_Alive_Device_ID, ID, sizeof(ID), 10);
		clients.insert({ ID, client});
		//clients.insert({ "esteban", 200 });
		

		send(client, buffer, valread, 0);
	} else {
		puts("no");
		send(client, buffer, valread, 0);

		
	}
	MsgToClient *msg = (MsgToClient *)buffer;

	
	char g[11] = "";
	switch (msg->token) {
	case '*':
		memcpy_s(&g,sizeof(g), msg->id, sizeof(msg->id));
		//g = (char*)msg->cmd;




		printf("[%s]", g);

		puts("=======");
		
		

		printf("%s\n", g);

		printf("cmdlength %d\n", strlen(msg->cmd));
		puts("-------");

		if (strcmp(msg->cmd, "yanny")==0) {
			puts("si es yanny");
		}
		//msg->cmd[strlen(msg->cmd) ] = '\0';
		if (strcmp(msg->cmd, "yanny")==0) {
			puts("si es yanny2");
		}


		it = clients.find("2012000413");

		// Check if element exists in map or not
		if (it != clients.end())
		{
			// Element with key 'hat' found
			std::cout << "'hat' Found" << std::endl;

			// Access the Key from iterator
			std::string key = it->first;
			// Access the Value from iterator
			SOCKET value = it->second;
			send(value, (char*)msg->cmd, strlen(msg->cmd), 0);
			//std::cout << "key = " << key << " :: Value = " << key << std::endl;
		}


		break;
		
	case '$':
		puts("borrar");
		system("cls");
		break;

			
	}
	
	return;
	
	

	if (buffer[0] == '*') {
		char buffer_aux[] = "<<responding...>>";
		send(client, buffer_aux, strlen(buffer_aux), 0);
	} else {
		//strcat((char*)buffer, "-yanny-");
		puts("send...!");
		
		//send(*client, (char*)buffer, valread, 0);
		Sleep(1000);
		//send(*client, (char *)st, sizeof(st), 0);
		char buffer4[] = "$WP+GETLOCATION=0000,?";
		send(client, (char*)buffer4,strlen(buffer4), 0);
		//send(client, buffer, valread, 0);
	}
	
	
	
}