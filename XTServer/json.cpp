#include "json.h"
using namespace rapidjson;
void json::test() {

	
	FILE* fp = fopen("C:\\source\\cpp\\XT\\XTServer\\small.json", "rb"); // non-Windows use "r"

	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}


	//char readBuffer[65536];

	char* readBuffer;

	//i = 0;
	readBuffer = (char*)malloc(65536);

	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(is);
	fclose(fp);
	printf("hello = %d\n", d["port"].GetInt());

	if (d["db"].IsObject()) {
		auto& a = d["db"];
		puts(d["db"]["user"].GetString());
	}

	//printf("%s", readBuffer);

	if (readBuffer != NULL)
	{
		readBuffer[0] = '\0';
		// code...
		free(readBuffer);
	}
}
