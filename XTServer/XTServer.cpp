#include <iostream>
#include "Server.h"

int main()
{
	
	system("cls");
	std::cout << "XT Server v1.0 !!!\n";
	ServerInfo info;
	info.host = (char*)"127.0.0.1";
	info.port = 12345;
	info.max_clients = 30;
	Server* s = new Server(info);
	s->init();
}