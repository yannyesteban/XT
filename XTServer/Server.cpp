#include "Server.h"

Server::Server(ServerInfo _info): Info(_info) {
	
	max_clients = Info.max_clients;
	
}

void Server::init() {
	_startUp();
	_createSocket();
	_bing();
	_listen();
}

void Server::setOptions() {
}

void Server::start() {
}

void Server::end() {
}

void Server::_startUp() {
	//puts("startUp");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}

void Server::_createSocket() {
	//puts("createSocket");
	if ((master = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}

void Server::_bing() {
	//puts("Bing");
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(Info.port);


	//Bind
	if (bind(master, (struct sockaddr*) & server, sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}

void Server::_listen() {
	puts("Listen");
	int h = listen(master, 3);
	printf("es error %d\n\n\n", h);

	//Accept and incoming connection
	//puts("Waiting for incoming connections...");

	const char* message = "ECHO Daemon v1.0 \r\n";

	int addrlen = sizeof(struct sockaddr_in);
	int activity;
	int valread;
	int i;
	fd_set readfds;
	//fd_set writefds;
	SOCKET s;

	int MAXRECV = 1024;
	
	char* buffer = (char*)malloc((MAXRECV + 1) * sizeof(char));
	
	
	for (i = 0; i < max_clients; i++) {
		clients[i] = 0;
	}

	while (TRUE) {
		FD_ZERO(&readfds);//clear the socket fd set
		FD_SET(master, &readfds);//add master socket to fd set
		//memset(&buffer, 0, MAXRECV);//clear the buffer
		
		//add child sockets to fd set
		for (i = 0; i < max_clients; i++) {
			s = clients[i];
			if (s > 0) {
				FD_SET(s, &readfds);
			}
		}
		
		//puts("Beging to Wait.....");
		//wait for an activity on any of the sockets, timeout is NULL , so wait indefinitely
		activity = select(0, &readfds, NULL, NULL, NULL);
		//printf("\n\nconected........");
		//system("cls");
		if (activity == SOCKET_ERROR) {
			printf("select call failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//If something happened on the master socket , then its an incoming connection
		if (FD_ISSET(master, &readfds)) {
			//system("cls");
			//printf("\nSTEP=(%d)\n", step);
			//puts("Master OK");
			if ((new_socket = accept(master, (struct sockaddr*) & address, (int*)& addrlen)) < 0) {
				perror("accept");
				exit(EXIT_FAILURE);
			}
			//puts("D");
			//inform user of socket number - used in send and receive commands
			printf("New connection , socket fd is %d , ip is : %s , port : %d (?)\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
			//message = "START\0";

			//strcpy(message, "START");
			//send new connection greeting message

			CallConection(master, new_socket);
/*

			struct mydata a;
			strcpy(a.msg, "Hi !!!");
			send(new_socket, a.msg, sizeof(a.msg), 0);
			//Sleep(10000);
			
			if (send(new_socket, message, strlen(message), 0) != strlen(message)) {
				perror("send failed");
			}
*/
			//exit(0);
			//puts("Welcome message sent successfully");
			//puts("********************");
			//printf("[%s]", message);
			//puts("********************");
			//add new socket to array of sockets
			for (i = 0; i < max_clients; i++) {
				if (clients[i] == 0) {
					clients[i] = new_socket;
					printf("Adding to list of sockets at index %d \n", i);
					break;
				}
			}
		}

		//else its some IO operation on some other socket :)
		for (i = 0; i < max_clients; i++) {
			//puts("Step TWO");
			s = clients[i];
			//if client presend in read sockets             
			if (FD_ISSET(s, &readfds)) {
				//get details of the client
				getpeername(s, (struct sockaddr*) & address, (int*)& addrlen);

				//Check if it was for closing , and also read the incoming message
				//recv does not place a null terminator at the end of the string (whilst printf %s assumes there is one).
				valread = recv(s, buffer, MAXRECV, 0);
				//puts(buffer);
				if (valread == SOCKET_ERROR) {
					int error_code = WSAGetLastError();
					if (error_code == WSAECONNRESET) {
						//Somebody disconnected , get his details and print
						printf("Host disconnected unexpectedly , ip %s , port %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

						//Close the socket and mark as 0 in list for reuse
						closesocket(s);
						clients[i] = 0;
					} else {
						printf("recv failed with error code : %d", error_code);
					}
				}
				if (valread == 0) {
					//Somebody disconnected , get his details and print
					printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

					//Close the socket and mark as 0 in list for reuse
					closesocket(s);
					clients[i] = 0;
				} else {//Echo back the message that came in
					//add null character, if you want to use with printf/puts or other string handling functions
					buffer[valread] = '\0';

					//void (*CallConection)(SOCKET master, SOCKET client);
					CallMsgReceived(master, s, buffer, valread);
					//send(s, buffer, valread, 0);
					//message = "-QUE-\n\n";
					//Sleep(15000);
					//mydata msg2;
					//strcpy(msg2.msg, buffer);
					//send(s, msg2.msg, sizeof(msg2.msg), 0);
					//send(s, buffer, valread, 0);
					printf("%s:%d - [%s] \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port), buffer);
					//send(s, "QUE", sizeof(msg2.msg), 0);
				}
			}
		}
	}
	//CloseHandle(hClientThread);
	closesocket(s);
	WSACleanup();


	
}
