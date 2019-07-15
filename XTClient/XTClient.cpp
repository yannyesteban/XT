// XTClient.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Client.h"

int main(int argc, char** argv) {
	system("cls");
	std::cout << "XT Client v1.0 !!!\n";
	ClientInfo info;

	if (argc == 2) {
		info.host = argv[1];
	} else {
		info.host = (char*)"localhost";
	}
	
	if (argc == 3) {
		info.port = argv[2];
	} else {
		info.port = "3311";
	}
	
	Client* s = new Client(info);
	s->init();

}

