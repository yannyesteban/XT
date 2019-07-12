#pragma once

#include <stdlib.h>
#include <iostream>
#include <mysql/jdbc.h>

namespace XT {

	struct InfoClient {
		int id;
		int id_version;
	};

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
		int tag_length;
		char* pass_default;
		char* protocol_pre;
		char* sync_header;

	};

	struct ConfigTrack {
		int id_device;
		char* track[30];
	};

	class DB {
	public:
		std::map<int, InfoProto*> proto;

		int connect(InfoDB pInfo);
		int test();

		int loadProtocols();
		int loadConfigTrack();

		int loadFormat();
		int getDeviceId(const char * unitid);


		void setDebug(bool);
		bool getDebug();

		~DB();

	private:
		sql::Driver* driver;
		sql::Connection* cn;
		sql::Statement* stmt;
		sql::ResultSet* result;

		int versions[50];
		int n_versions;

		std::map<std::string, InfoClient*> clients;
		std::map<std::string, InfoClient*>::iterator clients_it;

		bool debug = false;

	};
}



