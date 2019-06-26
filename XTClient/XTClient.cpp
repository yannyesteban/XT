// XTClient.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Client.h"

int main()
{
	system("cls");
	std::cout << "XT Client v1.0 !!!\n";
	ClientInfo info;
	info.host = (char*)"127.0.0.1";
	info.port = "12345";
	//info.max_clients = 30;
	Client* s = new Client(info);
	s->init();
}

