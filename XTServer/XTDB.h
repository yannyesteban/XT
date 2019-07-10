#pragma once

#include <stdlib.h>
#include <iostream>
#include <mysql/jdbc.h>

namespace XT {

	

	struct InfoDB {

		const char* host;
		const char* port;
		const char* name;
		const char* user;
		const char* pass;

	};
	struct InfoDB2 {

		char host[30];
		char port[5];
		char name[30];
		char user[30];
		char pass[30];

	};
	typedef struct {
		unsigned short Keep_Alive_Header;
		unsigned short Keep_Alive_ID;
		unsigned long Keep_Alive_Device_ID;
	} SyncStrcut;

	struct InfoProto {
		int id_device;
		short tag_length;
		const char* pass_default;
		const char* protocol_pre;
		const char* sync_header;
	};

	struct ConfigTrack {
		int id_device;
		char* track[30];
	};

	class DB {
	public:
		int connect(InfoDB pInfo);
		int test();

		int loadProtocols();
		int loadConfigTrack();

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



