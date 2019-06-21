#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 50
#define DEFAULT_PORT "12345"


struct mydata {
	char msg[20];

};

int __cdecl main(int argc, char** argv)
{
	system("cls");
	puts("Hello");
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo
		* result = NULL,
		* ptr = NULL,
		hints;
	char sendbuf[DEFAULT_BUFLEN];
	char recvbuf[DEFAULT_BUFLEN];
	char buffer[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;




	const char* mensajes[] = {
		"PEPSI I", "COCACOLA II", "SPRITE III", "ORANGE IV", "MR PEPPER V"
	};

	// Validate the parameters
	if (argc != 2) {
		printf("usage: %s server-name\n", argv[0]);
		return 1;
	}

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("CLIENTE socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	char MM[] = "Client THREE 3.0";
	memset(&sendbuf, 0, sizeof(sendbuf));//clear the buffer
	strcpy(sendbuf, MM);
	//iResult = send(ConnectSocket,  mensajes[i], 10, 0);
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}



	//Sleep(30000);
	//recvbuf = (char *)"Hola";

	//memset(&sendbuf, 0, sizeof(sendbuf));//clear the buffer
	//puts(recvbuf);
	//char* c;

	//Sleep(10000);
	iResult = recv(ConnectSocket, recvbuf, sizeof(recvbuf), 0);

	strcpy(buffer, recvbuf);
	puts("=:=:=:=:=:=:=");

	//mydata a;
	//strcpy(a.msg, buffer);
	puts(buffer);
	puts("============");
	Sleep(10000);
	iResult = recv(ConnectSocket, recvbuf, sizeof(recvbuf), 0);

	strcpy(buffer, recvbuf);
	puts("=:=:=:=:=:=:=");

	//mydata a;
	//strcpy(a.msg, buffer);
	puts(buffer);
	puts("============");


	printf("len = %d\n", recvbuflen);
	Sleep(2000);
	//getchar();
	char msg[50];
	int msg_length = 0;

	int i;
	for (i = 0; i < 5; i++) {
		Sleep(0);
		// Send an initial buffer

		memset(&sendbuf, 0, sizeof(sendbuf));//clear the buffer
		strcpy(sendbuf, mensajes[i]);
		//iResult = send(ConnectSocket,  mensajes[i], 10, 0);
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		//iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		iResult = recv(ConnectSocket, msg, msg_length, 0);
		puts("\nBegin:");
		puts(recvbuf);
		puts(":END\n");

	}


	printf("Bytes Sent: %ld\n", iResult);
	puts("OK");
	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	puts("XXXX");
	// Receive until the peer closes the connection
	int n = 0;
	do {
		printf("Times: (%d)\n\n", ++n);
		//puts("BYE.............");
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

		puts(recvbuf);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());
		//Sleep(5000);
	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}