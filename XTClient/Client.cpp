#include "Client.h"

Client::Client(ClientInfo _info):Info(_info) {
}

int Client::_startUp() {
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 0;
	}
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
	int iResult = getaddrinfo(Info.host, (PCSTR)Info.port, &hints, &result);
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
	return 0;
}
