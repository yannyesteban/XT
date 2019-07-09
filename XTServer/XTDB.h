#pragma once

#include <stdlib.h>
#include <iostream>
#include <mysql/jdbc.h>

namespace XT {
	struct InfoDB {

		char host[30];
		char port[5];
		char dbname[30];
		char user[30];
		char pass[30];

	};
	class DB {
	public:
		int connect(InfoDB pInfo);
		int test();

		int loadFormat();
		int getDeviceId(const char * unitid);
		~DB();

	private:
		sql::Driver* driver;
		sql::Connection* cn;
		sql::Statement* stmt;
		sql::ResultSet* result;

	};
}



