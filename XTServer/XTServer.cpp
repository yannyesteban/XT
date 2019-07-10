#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iterator>
#include <map> 
#include <sys/timeb.h>
#include <time.h>
#include <regex>
#include <clocale>
#include "Server.h"
#include "json.h"
#include "XTTime.h"
#include "Config.h"
#include "XTDB.h"
#include "XTTool.h"

struct InfoClient {
	char device_id[10];
	short int status=0;
	SOCKET socket;
	short int type = 0;

};
struct MsgToClient {
	char token;
	char id[10];
	char cmd[100];
};
std::map<std::string, InfoClient> Devices;

std::map<SOCKET, InfoClient> Clients;
std::map<SOCKET, InfoClient>::iterator cliIT;

std::map<std::string, SOCKET> clients;
std::map<std::string, SOCKET>::iterator it;

void _CallConection(SOCKET master, SOCKET client, SOCKET clients[], int index, short int max_clients);
void _CallMsgReceived(SOCKET master, SOCKET client, char* buffer, int valread);

struct timeb start, __end;
int getDiff() {
	return (int)(1000.0 * (__end.time - start.time) + (__end.millitm - start.millitm));
}

int main()
{
	setlocale(LC_CTYPE, "Spanish");
	system("cls");

	//json myjson;
	//XTTime my_time;

	//myjson.test();

	//my_time.test();
	auto mInfo = XT::Config::load("C:\\source\\cpp\\XT\\XTServer\\config.json");
	//auto mInfo = XT::Config::getInfo();

//
printf("APP NAME: %s\n", mInfo.appname);
printf("Version: %s \n", mInfo.version);
printf("DB Name: %s\n", mInfo.db.name);
	//XT::Config::test2(tt);




//printf("%s",XT::Config::info.max_clients);
	
/*
XT::InfoDB infoDB = {
		XT::Config::info.db.host,
		XT::Config::info.db.port,
		XT::Config::info.db.dbname,
		XT::Config::info.db.user,
		XT::Config::info.db.pass
	};

	*/

	XT::DB My;
	My.connect(mInfo.db);
	//return 1;
	//My.test();

	printf("\nmi id es : %d\n\n",My.getDeviceId("2012000413"));
	printf("today is %s", XT::Time::now());
	return 1;

	if (std::regex_match("yanny", std::regex("([.]+)"))) {
		std::cout << "string literal matched\n";
	}
	std::smatch m;
	std::string ss("Yanny,Esteban,Núñez,Jiménez");

	XT::Tool::split(ss, ',');
	XT::Tool::test();

	std::regex Pala("[a-zA-ZñÑáéíóúÁÉÍÓÚäëïöüÄËÏÖÜ]+");	
	while (std::regex_search(ss, m, Pala)) {
		//std::cout << "Pala\n";

		for (auto x : m) {
			std::cout << x << " ";
		}
		std::cout << std::endl;
		ss = m.suffix().str();

	}

	//exit(0);
	//return 1;
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

void _CallConection(SOCKET master, SOCKET client, SOCKET clients[], int index, short int max_clients) {

	ftime(&start);
	
	if (Clients.count(client) > 0) {
		puts("Receiving...");

	} else {
		puts("New Client...");
		Clients[client].status = 1;
		Clients[client].socket = client;
		Clients[client].type = 2;


	}
	
	/*
	for (int i = 0; i < max_clients; i++) {
		printf("cliente info: [%d]",clients[i]);

	}

	printf("\nmax: (%d) - index: (%d)\n",max_clients, index);
	*/
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


	if (Clients.count(client) > 0) {
		puts("Receiving...");
	
	} else {
		puts("New Client...");
		Clients[client].status = 1;
		Clients[client].socket = client;
		Clients[client].type = 2;


	}
	

	/*
	ftime(&end);

	printf("segundos %d\n", getDiff()/1000 );

	ftime(&start);
	*/
	/*
	char fecha[25];//ctime devuelve 26 caracteres pero tambien se podría usar un puntero de char
	time_t current_time;
	current_time = time(NULL);
	ctime(&current_time);
	strcpy(fecha, ctime(&current_time));
	printf("%s\n", fecha);
*/
	//printf("Inicio [%s]\n\n", fecha);

	//printf("Conectando ---> [%s]\n", buffer);

	Keep_Alivestruct* st =(Keep_Alivestruct*)buffer;

	

	
	char ID[12];
	if (st->Keep_Alive_Header == 55248) {// IS A SYNC MESSAGE
		puts("SYNC");
		printf("Keep_Alive_Device_ID: %d\n", st->Keep_Alive_Device_ID);
		printf("Keep_Alive_Header: %d\n", st->Keep_Alive_Header);
		printf("Keep_Alive_ID: %d\n", st->Keep_Alive_ID);
		sprintf(ID, "%lu", st->Keep_Alive_Device_ID);
		//clients[ID] = client;
		
		if (Devices.count(ID)>0) {
			puts("Device Existe");
		} else {
			puts("New Device");
			Devices[ID].status = 1;
			Devices[ID].socket = client;
			Devices[ID].type = 1;
			Clients[client].type = 1;
		}

		send(client, buffer, valread, 0);// return the sycm message
		return;
	}
	
	puts(buffer);
	send(client, buffer, valread, 0);
	MsgToClient *msg = (MsgToClient *)buffer;

	
	char g[11] = "";
	switch (msg->token) {
	case '*':
		memcpy_s(&g,sizeof(g), msg->id, sizeof(msg->id));

		puts(g);
		if (Devices.count(g)>0) {
			puts("enviando....");

			send(Devices[g].socket, (char*)msg->cmd, strlen(msg->cmd), 0);
			break;
		} else {
			puts("no es devices"); 
		}
		break;
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
		//puts("borrar");
		//system("cls");

		for (cliIT = Clients.begin(); cliIT != Clients.end(); ++cliIT) {

			send(cliIT->first, buffer, valread, 0);// return the sycm message
			
		}

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