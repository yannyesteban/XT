#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filereadstream.h"
#include <cstdio>


struct AppConfig{
	unsigned int port;
	unsigned int max_clients;
	struct {
		const char* dbname;
		const char* user;
		const char* pass;
		int port;

	}db;


};
class Config {

public:
	static AppConfig info;

	static void load();
};

