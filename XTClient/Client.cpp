#include "Client.h"

Client::Client(ClientInfo _info):Info(_info) {
}

void Client::init() {
	_startUp();
	_createSocket();
	_listen();
	closesocket(master);
	WSACleanup();
}

int Client::_startUp() {
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 0;
	}
	return 1;
}

int Client::_createSocket() {
	
	struct addrinfo* result = NULL;
	struct addrinfo*ptr = NULL;
	struct addrinfo hints;


	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	// Resolve the server address and port
	int iResult = getaddrinfo(Info.host, Info.port, &hints, &result);
	if (iResult != 0) {
	
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	
	
	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
	
		// Create a SOCKET for connecting to server
		master = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (master == INVALID_SOCKET) {
			printf("CLIENTE socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}


		// Connect to server.
		iResult = connect(master, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(master);
			master = INVALID_SOCKET;
			continue;
		}
		break;
	}
	
	freeaddrinfo(result);
	

	if (master == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	//return 1;

	

	Info2.socket = master;
	//Info.tag = (char[10])"WHAT";
	_thread(Info2);

	return 1;
	//Sleep(1000);
	char sendbuf[50];
	
	char MM[] = "===Client Test I (Thread)===";
	memset(&sendbuf, 0, sizeof(sendbuf));//clear the buffer
	strcpy(sendbuf, MM);
	//iResult = send(ConnectSocket,  mensajes[i], 10, 0);
	iResult = send(master, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(master);
		WSACleanup();
		return 1;
	}
	const char* mensajes[] = {
		"ONE I", "TWO II", "tres III", "cuatro IV", "cinco V"
	};

	//InfoSocket Info;

	Info2.socket = master;
	//Info.tag = (char[10])"WHAT";
	_thread(Info2);
	//Sleep(20000);
	char msg[50];
	int msg_length = 0;
	int i;
	for (i = 0; i < 15; i++) {
		Sleep(1000);
		// Send an initial buffer

		memset(&sendbuf, 0, sizeof(sendbuf));//clear the buffer
		strcpy(sendbuf, mensajes[i%5]);
		//iResult = send(ConnectSocket,  mensajes[i], 10, 0);
		iResult = send(master, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(master);
			WSACleanup();
			return 1;
		}
		//iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

		/*
		iResult = recv(ConnectSocket, k.msg, sizeof(k.msg), 0);
		puts("\nBegin:");
		//strcpy(k.msg, msg);
		puts(k.msg);
		puts(":END\n");
		*/
	}

	
	int n = 0;

	char recvbuf[100];
	int recvbuflen = 100;
	do {
		printf("Times: (%d)\n\n", ++n);
		//puts("BYE.............");
		memset(&recvbuf, 0, sizeof(recvbuf));//clear the buffer
		iResult = recv(master, recvbuf, recvbuflen, 0);

		puts(recvbuf);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());
		Sleep(500);
	} while (iResult > 0);



	//Sleep(120000);
	mydata k;
	for (i = 0; i < 5; i++) {
		Sleep(1000);
		// Send an initial buffer

		memset(&sendbuf, 0, sizeof(sendbuf));//clear the buffer
		strcpy(sendbuf, mensajes[i]);
		//iResult = send(ConnectSocket,  mensajes[i], 10, 0);
		iResult = send(master, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(master);
			WSACleanup();
			return 1;
		}
		//iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

		/*
		iResult = recv(ConnectSocket, k.msg, sizeof(k.msg), 0);
		puts("\nBegin:");
		//strcpy(k.msg, msg);
		puts(k.msg);
		puts(":END\n");
		*/
	}

	
	puts("cool");
	//Sleep(20000);
	return 0;
}

int Client::_listen() {

	char recvbuf[100];
	int recvbuflen = 100;
	int iResult;
	do {
		
		//puts("BYE.............");
		memset(&recvbuf, 0, sizeof(recvbuf));//clear the buffer
		iResult = recv(master, recvbuf, recvbuflen, 0);

		puts(recvbuf);
		if (iResult > 0)
			printf("Bytes received: %d\n> ", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());
		
	} while (iResult > 0);
	return 1;
}

BOOL WINAPI keyboard(LPVOID param) {
	InfoSocket* Info = (InfoSocket*)param;
	
	char message[255]="";
	int iResult;
	//printf("que %s", Info->tag2);
	while (strcmp(message, "*exit")) {
		printf("> ");
		scanf("%s", message);

		printf("mensaje enviado %s\n", message);



		//char MM[] = "*===Multi Hilo===";
		//memset(&sendbuf, 0, sizeof(sendbuf));//clear the buffer
		//strcpy(sendbuf, buffer);
		//iResult = send(ConnectSocket,  mensajes[i], 10, 0);
		iResult = send(Info->socket, message, (int)strlen(message), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error-> %d\n", WSAGetLastError());
			closesocket(Info->socket);
			WSACleanup();
			exit(0);
			return 1;
		}

	}
	system("cls");
	printf("**************\n\n");

	closesocket(Info->socket);
	WSACleanup();
	exit(0);
	return true;
}


int Client::_thread(InfoSocket& INFO) {
	
	//printf("que %s", INFO.tag2);
	//send(INFO.socket, "P1", 3, 0);
	hClientThread = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)keyboard,
		&INFO,
		0,
		&dwThreadId);
	
	return 0;



}
