#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <iostream>
#include "XTDB.h"

namespace XT {

	struct AppConfig {
		char appname[30];
		unsigned int port;
		unsigned int max_clients;
		InfoDB db;


	};
	class Config {

	public:
		static AppConfig info;

		static AppConfig load(const char* path);

	
	};

}


