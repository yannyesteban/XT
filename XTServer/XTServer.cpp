#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <map> 
#include <sys/timeb.h>
#include <time.h>
#include <regex>
#include <clocale>
#include "Server.h"
#include "json.h"

#include "GTTypes.h"
#include "XTTime.h"
#include "Config.h"
#include "XTDB.h"
#include "XTTool.h"


void Color(int Background, int Text); // Prototipo de función           

enum Colors { // Listado de colores (La letra "L" al inicio, indica que es un color más claro que su antecesor).
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LGREY = 7,
	DGREY = 8,
	LBLUE = 9,
	LGREEN = 10,
	LCYAN = 11,
	LRED = 12,
	LMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};
void Color(int Background, int Text) { // Función para cambiar el color del fondo y/o pantalla

	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.

	// Para cambiar el color, se utilizan números desde el 0 hasta el 255.
	// Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
	int    New_Color = Text + (Background * 16);

	SetConsoleTextAttribute(Console, New_Color); // Guardamos los cambios en la Consola.

}
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

void _CallConection(SOCKET master, SOCKET client, SOCKET clients[], int index, short int max_clients, GT::CnnInfo info);
void _CallMsgReceived(SOCKET master, SOCKET client, char* buffer, int valread, int index);
void _CallMsgReceived2(SOCKET master, SOCKET client, char* buffer, int valread, int index);

void _CallClientError(SOCKET master, SOCKET client, char* buffer, int valread, int index, int error_code);
void _CallClientError2(int index);


struct timeb start, __end;

int* versions;
int n_versions;
XT::DB db;
int getDiff() {
	return (int)(1000.0 * (__end.time - start.time) + (__end.millitm - start.millitm));
}

int main() {
	setlocale(LC_CTYPE, "Spanish");
	system("cls");

	printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");

	//Color(WHITE, RED);    
	//printf("Texto en color Rojo y fondo Negro");

	printf(ANSI_COLOR_GREEN ANSI_COLOR_RED_  "This text is GREEN!"   ANSI_COLOR_RESET "\n");

	//exit(0);


	//json myjson;
	//XTTime my_time;

	//myjson.test();

	//my_time.test();
	auto mInfo = XT::Config::load("C:\\source\\cpp\\XT\\XTServer\\config.json");
	//auto mInfo = XT::Config::getInfo();

	

printf("APP NAME: %s\n", mInfo.appname);
printf("Version: %s \n", mInfo.version);
printf("DB Name: %s\n", mInfo.db.name);
printf("Time: %s", XT::Time::now());
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

	
	db.setDebug(mInfo.debug);
	db.connect(mInfo.db);
	db.loadProtocols();
	//db.getVersions();

	if (mInfo.show_cache) {
		puts("show cache");
		system("pause");
	}
	//return 1;

	versions = db.getVersions();
	n_versions = db.getVersionsCount();
	//printf("n_versions %d\n", n_versions);
	//printf("n_versions %d\n", db.n_versions);
	//return 1;

	//return 1;
	//My.test();

	//printf("\nmi id es : %d\n\n",My.getDeviceId("2012000413"));
	
	//return 1;


	


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

	s->CallClientError = _CallClientError;
	s->init();
}

void _CallConection(SOCKET master, SOCKET client, SOCKET clients[], int index, short int max_clients, GT::CnnInfo info) {

	ftime(&start);
	//printf("START \n\n");
	if (Clients.count(client) > 0) {
		puts("Receiving...");
	} else {
		puts("New Client...");
		Clients[client].status = 1;
		Clients[client].socket = client;
		Clients[client].type = 2;
		strcpy(Clients[client].device_id, "unknow");
	}
	printf(ANSI_COLOR_GREEN "New connection , socket fd is %d , ip is : %s , port : %d, tag: %s\n" ANSI_COLOR_RESET, client, info.address, info.port, info.tag);
	//send(client, "siiiiiiii", 10, 0);
}

void _CallMsgReceived(SOCKET master, SOCKET client, char* buffer, int valread, int index) {


	//printf(ANSI_COLOR_RESET ANSI_COLOR_YELLOW "\n\n%s\n\n" ANSI_COLOR_RESET, buffer);

	if (Clients.count(client) > 0) {
		printf("Receiving from Client HAND %d, index: %d\n", client, index);
		//puts("Receiving...");
	} else {
		puts("New Client...");
		Clients[client].status = 1;
		Clients[client].socket = client;
		Clients[client].type = 2;
	}
	char id[12];
	if (db.isSyncMsg(buffer, id)) {
		
		//puts("sync.....................");
		if (Devices.count(id) > 0 && Devices[id].type == 1) {
			printf(ANSI_COLOR_CYAN "---> Receiving sync FROM %s\n" ANSI_COLOR_RESET, id);
		} else {
			/*
			puts("New Device");
			printf("Device_ID: %d\n", sync_msg->Keep_Alive_Device_ID);
			printf("Header: %d\n", sync_msg->Keep_Alive_Header);
			printf("ID: %d\n", sync_msg->Keep_Alive_ID);
			*/
			printf(ANSI_COLOR_GREEN "New Connection ---> Receiving sync FROM %s\n" ANSI_COLOR_RESET, id);
			
			
			//sprintf((char *)Clients[client].device_id, "%lu", sync_msg->Keep_Alive_Device_ID);
		}


		Devices[id].status = 1;
		Devices[id].socket = client;
		Devices[id].type = 1;
		Clients[client].type = 1;
		strcpy(Clients[client].device_id, (const char*)id);
		//puts(buffer);
		
		printf(ANSI_COLOR_CYAN "return sync message...!\n[%s]\n" ANSI_COLOR_RESET, buffer);
		
		send(client, buffer, valread, 0);// return the sycm message
		
		return;
	}

	std::string string = (char*) buffer;
	std::stringstream ss((char*) buffer);
	std::string to;
	int i = 0;

	

	
	if (buffer != NULL) {
		while (std::getline(ss, to)) {//, '\n'

			printf("%d .- line", i++);

			_CallMsgReceived2(master, client, (char*)to.c_str(), valread, index);
		}
	}


	
}
void _CallClientError2(int i) {

}
void _CallClientError(SOCKET master, SOCKET client, char* buffer, int valread, int index, int error_code) {
	printf(ANSI_COLOR_GREEN "error\n" ANSI_COLOR_RESET);
	for (std::map<std::string, InfoClient>::iterator it = Devices.begin(); it != Devices.end(); ++it) {
	
		if (it->second.socket == client) {
			
			printf(ANSI_COLOR_RED "error device ID %s\n" ANSI_COLOR_RESET, it->second.device_id);
			printf(ANSI_COLOR_RED "error Client %d\n" ANSI_COLOR_RESET, client);
		}

	}
	
	return;

}

void _CallMsgReceived2(SOCKET master, SOCKET client, char* buffer, int valread, int index) {
	
	
	
	//puts(buffer);
	//buffer[valread] = '\0';
	//send(client, buffer, valread, 0);
	CmdMsg* msg = (CmdMsg*)buffer;
	//printf("valread %d, msgcmd: len %d\n\n", valread, strlen(msg->cmd));


	char g[11] = "";
	switch (msg->token) {
	case '*':

		send(client, buffer, valread, 0);

		memcpy_s(&g, sizeof(g), msg->id, sizeof(msg->id));

		puts(g);
		if (Devices.count(g) > 0) {

			printf(ANSI_COLOR_YELLOW "enviando to {%s}...\nSocket {%d}\nClient {%d}" ANSI_COLOR_RESET,
				g, Devices[g].socket, client);
			int tbytes = send(Devices[g].socket, (char*)msg->cmd, strlen(msg->cmd), 0);
			if (tbytes > 0) {
				printf(ANSI_COLOR_BLUE "\n\tsend bytes %d\n" ANSI_COLOR_RESET, tbytes);
			} else {
				printf(ANSI_COLOR_RED "error sending bytes %d\n" ANSI_COLOR_RESET, tbytes);
			}
			break;
		} else {
			puts("Devices not found...!");
		}
		break;


	case '$':
		printf(ANSI_COLOR_YELLOW ANSI_COLOR_BLUE_ "\nreceiving data from device: %s\n" ANSI_COLOR_RESET, Clients[client].device_id);
		puts(buffer);
		for (cliIT = Clients.begin(); cliIT != Clients.end(); ++cliIT) {

			send(cliIT->first, buffer, valread, 0);// return the sycm message

		}

		break;
	case '#':
	{
		send(client, buffer, valread, 0);
		GenMsg* gen_msg = (GenMsg*)buffer;

		puts(gen_msg->msg);
		if (strcmp(gen_msg->msg, "cls") == 0) {
			system("cls");
			puts("CLS");
		}
		if (strcmp(gen_msg->msg, "cli") == 0) {

			//Clients[client]
			for (cliIT = Clients.begin(); cliIT != Clients.end(); ++cliIT) {
				printf(ANSI_COLOR_GREEN "Clients %d\n" ANSI_COLOR_RESET, cliIT->first);
				//send(cliIT->first, buffer, valread, 0);// return the sycm message

			}
			//for (std::map<SOCKET, InfoClient>::iterator it = Clients.begin; it != Clients.end(); it++) {
				//printf(ANSI_COLOR_GREEN "Clients %d\n" ANSI_COLOR_RESET, it->first);
			//}

		}
	}


	break;

	default:
		char* pch;
		//puts("device ID es:");
		puts((const char*)Clients[client].device_id);
		pch = strstr(buffer, (const char*)Clients[client].device_id);
		if (pch) {
			printf("Saving track from %s" ANSI_COLOR_RED "...." ANSI_COLOR_RESET, Clients[client].device_id);
			db.saveTracking((const char*)Clients[client].device_id, buffer);
		} else {

			puts("---- nada !!!!");
			//puts(buffer);
			puts("--------------");
		}
		break;

	}
	puts(buffer);
	return;
	
	

	
	
	
	
}