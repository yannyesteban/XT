#include "Client.h"

Client::Client(ClientInfo _info):Info(_info) {
}

void Client::init() {
	_startUp();
	_createSocket();

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
	Sleep(1000);
	char sendbuf[50];
	
	char MM[] = "===Client ONE===";
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

	Sleep(5000);
	char msg[50];
	int msg_length = 0;

	int i;

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
	return 0;
}
