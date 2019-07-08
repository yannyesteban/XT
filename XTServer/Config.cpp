#include "Config.h"
using namespace rapidjson;

AppConfig Config::info = { 0,0,{"","","",0} };
void Config::load() {
	
	FILE* fp = fopen("C:\\source\\cpp\\XT\\XTServer\\config.json", "rb"); // non-Windows use "r"

	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
		
	char* readBuffer;
		
	readBuffer = (char*)malloc(65536);
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(is);
	fclose(fp);
		
	info.port = d["port"].GetInt();
	info.max_clients = d["max_clients"].GetInt();
	
	info.db.dbname = d["db"]["dbname"].GetString();
	info.db.user = d["db"]["user"].GetString();
	info.db.pass = d["db"]["pass"].GetString();
	info.db.port = d["db"]["port"].GetInt();


	if (readBuffer != NULL)	{
		readBuffer[0] = '\0';
		free(readBuffer);
	}


}
