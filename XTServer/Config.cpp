#include "Config.h"
using namespace rapidjson;
namespace XT {
	AppConfig Config::info = {};// { 0, 0, { "","","",0 } };
	AppConfig Config::load(const char * path) {
		//"C:\\source\\cpp\\XT\\XTServer\\config.json"
		FILE* fp = fopen(path, "rb"); // non-Windows use "r"

		if (fp == NULL)
		{
			perror("Error while opening the file.\n");
			exit(EXIT_FAILURE);
		}
		
		char* readBuffer;
		
		readBuffer = (char*)malloc(1500);
		FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		Document d;
		d.ParseStream(is);
		fclose(fp);
		
		strcpy_s(info.appname, sizeof(info.appname), d["appname"].GetString());
		info.port = d["port"].GetInt();
		info.max_clients = d["max_clients"].GetInt();
		strcpy_s(info.db.dbname, sizeof(info.db.dbname), d["db"]["dbname"].GetString());
		strcpy_s(info.db.host, sizeof(info.db.host), d["db"]["host"].GetString());
		strcpy_s(info.db.user, sizeof(info.db.user), d["db"]["user"].GetString());
		strcpy_s(info.db.pass, sizeof(info.db.pass), d["db"]["pass"].GetString());
		strcpy_s(info.db.port, sizeof(info.db.port), d["db"]["port"].GetString());

		if (readBuffer != NULL)	{
			readBuffer[0] = '\0';
			free(readBuffer);
		}

		return info;
	}



}
