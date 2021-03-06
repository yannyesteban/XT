#include <stdio.h>
#include "XTDB.h"
using namespace std;


namespace XT {
	int DB::connect(InfoDB pInfo) {
		try {
			driver = get_driver_instance();

			char str_host[100]="tcp://";
			strcat_s(str_host, pInfo.host);
			strcat_s(str_host, ":");
			strcat_s(str_host, pInfo.port);
		
			cn = driver->connect(str_host, pInfo.user, pInfo.pass);
			//cout << "es correcta " << cn->isValid() << endl;
			/* Connect to the MySQL test database */
			cn->setSchema(pInfo.name);
			return 1;
			
		} catch (sql::SQLException& e) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			//cout << ", SQLState: " << e.getSQLState() << " )" << endl;
			return 0;
		}
		
		
	}
	int DB::test() {
		try {
			/*sql::Driver* driver;
			sql::Connection* con;
			sql::Statement* stmt;
			sql::ResultSet* res;
			*/
			/* Create a connection */
			driver = get_driver_instance();
			cn = driver->connect("tcp://127.0.0.1:3306", "root", "123456");

			cout << "es correcta " << cn->isValid() << endl;
			/* Connect to the MySQL test database */
			cn->setSchema("geocota");

			stmt = cn->createStatement();

			/*

			stmt->execute("USE " EXAMPLE_DB);
	stmt->execute("DROP TABLE IF EXISTS test");
	stmt->execute("CREATE TABLE test(id INT, label CHAR(1))");
	stmt->execute("INSERT INTO test(id, label) VALUES (1, 'a')");
			*/
			result = stmt->executeQuery("SELECT * FROM devices_commands WHERE version_id=40");
			std::cout << "WHAT " << std::endl;
			while (result->next()) {
				cout << "\t... MySQL replies: ";
				/* Access column data by alias or column name */
				//cout << res->getString("_message") << endl;
				cout << "\t... MySQL says it again: ";
				/* Access column data by numeric offset, 1 is the first column */
				cout << result->getString(1).c_str() << " -> " << result->getInt(1) << " -> " << result->getString("command").c_str() << endl;
			}
			delete result;
			delete stmt;
			delete cn;

		} catch (sql::SQLException& e) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}

		cout << endl;

		return EXIT_SUCCESS;

	}

	int DB::loadProtocols() {

		
		

		int ID = 0;
		try {
			sql::Statement* stmt;
			sql::ResultSet* result;
			sql::PreparedStatement* p_stmt;

			stmt = cn->createStatement();

			p_stmt = cn->prepareStatement(
				"SELECT id, tag_length, pass_default, protocol_pre,sync_header "
				"FROM devices_versions as d "
			);
			

			if (p_stmt->execute()) {
				result = p_stmt->getResultSet();
				string protocol_pre;
				string str;
				while (result->next()) {



					InfoProto* proto_z = new InfoProto({
							result->getInt("id"),
							result->getInt("tag_length"),
							(char*)malloc(strlen(result->getString("pass_default").c_str())),
							(char*)malloc(strlen(result->getString("protocol_pre").c_str())),
							(char*)malloc(strlen(result->getString("sync_header").c_str()))

						});
					//proto_z->pass_default = (char *)result->getString("pass_default").c_str();
					strcpy(proto_z->protocol_pre, result->getString("protocol_pre").c_str());
					strcpy(proto_z->pass_default, result->getString("pass_default").c_str());
					strcpy(proto_z->sync_header, result->getString("sync_header").c_str());

					//proto_z->protocol_pre = result->getString("protocol_pre").c_str();
					//proto_z->sync_header = result->getString("sync_header").c_str();

					
					proto.insert(std::pair<int, InfoProto*>(result->getInt("id"), proto_z));

				}
				if (debug) {

					printf("\n*** Cache for Devices Version ***\n\n");

					printf("%8s", "Id");
					printf("%8s", "TabLen");
					printf("%10s", "Pass");
					printf("%10s", "Pre");
					printf("%12s\n", "Sync");

					printf("%8s", "/=====");
					printf("%8s", "/=====");
					printf("%10s", "/=======");
					printf("%10s", "/========");
					printf("%12s\n", "/=========");
					
					for (std::map<int, InfoProto*>::iterator it = proto.begin(); it != proto.end(); ++it) {

						printf("%8d", it->second->id_device);
						printf("%8d", it->second->tag_length);
						printf("%10s", it->second->pass_default);
						printf("%10s", it->second->protocol_pre);
						printf("%12s\n", it->second->sync_header);
						
					}
				}
				
				delete result;
			}

			p_stmt = cn->prepareStatement(
				"SELECT sync_dec FROM devices_versions d GROUP BY sync_dec; "
			);
			n_versions = 0;
			if (p_stmt->execute()) {
				result = p_stmt->getResultSet();
				
				while (result->next()) {
					versions[n_versions++] = result->getInt("sync_dec");
				}

				if (debug) {
					printf("\n*** Cache for Sync Versions ***\n\n");
					printf("%10s", "Id");
					printf("%10s\n", "Sync");
					printf("%10s", "/========");
					printf("%10s\n", "/=========");

					for (int i = 0; i < n_versions; i++) {
						printf("%10d", i);
						printf("%10d\n", versions[i]);
					}
				}

				delete result;
			}


			p_stmt = cn->prepareStatement(
				"SELECT id, unitid, id_version FROM devices as d; "
			);
			
			if (p_stmt->execute()) {
				result = p_stmt->getResultSet();

				while (result->next()) {
					InfoClient* client_x = new InfoClient({
						result->getInt("id"),
						result->getInt("id_version")});
					
					clients.insert(std::pair<string, InfoClient*>(result->getString("unitid").c_str(), client_x));
				}
				if (debug) {

					printf("\n*** Cache for Sync Versions ***\n\n");
					printf("%12s", "UnitId");
					printf("%10s", "Id");
					printf("%10s\n", "Version");
					printf("%12s", "/==========");
					printf("%10s", "/========");
					printf("%10s\n", "/=========");
					for (std::map<std::string, InfoClient*>::iterator it = clients.begin(); it != clients.end(); ++it) {
						printf("%12s", it->first.c_str());
						printf("%10d", it->second->id);
						printf("%10d\n", it->second->id_version);
					}
				}

				delete result;
			}

			
			
			p_stmt = cn->prepareStatement(
				"SELECT id_version, parameter FROM devices_format as d ORDER BY id_version, `order`; "
			);

			if (p_stmt->execute()) {
				result = p_stmt->getResultSet();
				char M[30][25] = {};
				//puts("ONE");
				//M[0] = "yanny";
				//M[1] = "esteban";
				
				//strcpy((char*) M[1], "esteban");
				//strcpy((char*) M[2], "nu�ez");
				//strcpy((char*) M[3], "jimenez");

				int j = 0;
				int lastVersion = 0;
				int version;
				while (result->next()) {
					version = result->getInt("id_version");
					
					if (version != lastVersion) {
						lastVersion = version;
						j = 0;
						Format * M = new Format;
						
						//format[lastVersion] = M;
						format.insert(std::pair<int, Format*>(lastVersion, M));
					}
					
					strcpy(format[lastVersion]->s[format[lastVersion]->n++], result->getString("parameter").c_str());
					
					//M[j++] = result->getString("parameter").c_str();
					
					//puts(M[j]);
					//j++;
					/*
					InfoClient* client_x = new InfoClient({
						result->getInt("id"),
						result->getInt("id_version") });

					clients.insert(std::pair<string, InfoClient*>(result->getString("unitid").c_str(), client_x));
				*/
				}
				
				if (debug) {

					printf("\n*** Cache for Format Tracks ***\n\n");
					printf("%12s", "Id Version");
					printf("%16s\n", "Param");
					
					
					int aux = 0;

					for (std::map<int, Format*>::iterator it = format.begin(); it != format.end(); ++it) {
						//puts("que");
						//printf("%12d\n", it->first);
						if (aux != it->first) {
							printf("%12s", "/==========");
							printf("%16s\n", "/=============");
							aux = it->first;
						}
						for (int j = 0; j < it->second->n; j++) {
							printf("%12d", it->first);
							printf("%16s\n", it->second->s[j]);
						}
						
					}
				}

				delete result;
			}
			
			//result = stmt->executeQuery(query);

			delete stmt;
			delete p_stmt;

			//free(query);

		} catch (sql::SQLException& e) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			//cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}

		return 0;
	}

	int DB::loadConfigTrack() {
		return 0;
	}

	int DB::loadFormat() {


		try {
			sql::Driver* driver;
			sql::Connection* con;
			sql::Statement* stmt;
			sql::ResultSet* res;
			
			

			stmt = cn->createStatement();

			/*

			stmt->execute("USE " EXAMPLE_DB);
	stmt->execute("DROP TABLE IF EXISTS test");
	stmt->execute("CREATE TABLE test(id INT, label CHAR(1))");
	stmt->execute("INSERT INTO test(id, label) VALUES (1, 'a')");
			*/

			const char* query = "\
				SELECT id, id_version, parameter, `order`		\
				FROM devices_format as d		\
				ORDER BY `order`			\
				";

			result = stmt->executeQuery(query);
			std::cout << "WHAT " << std::endl;
			while (result->next()) {
				cout << "\t... MySQL replies: ";
				/* Access column data by alias or column name */
				//cout << res->getString("_message") << endl;
				cout << "\t... MySQL says it again: ";
				/* Access column data by numeric offset, 1 is the first column */
				cout << result->getString(1).c_str() << " -> " << result->getInt(1) << " -> " << result->getString("command").c_str() << endl;
			}
			delete result;
			delete stmt;
			delete cn;

		} catch (sql::SQLException& e) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}

		return 0;
	}

	int DB::getDeviceId(const char* unitid) {

		std::map<std::string, int> myId;
		

		int ID = 0;
		try {
			//sql::Driver* driver;
			//sql::Connection* con;
			sql::Statement* stmt;
			sql::ResultSet* result;

			sql::PreparedStatement* p_stmt;

			stmt = cn->createStatement();
			
			//char* query = (char*)malloc(512);
			
			//sprintf(query, "SELECT id,unitid FROM devices WHERE unitid='%s'", unitid);

			p_stmt = cn->prepareStatement("SELECT id,unitid FROM devices WHERE unitid=?");
			p_stmt->setString(1, unitid);

			
			
			if (p_stmt->execute()) {
				result = p_stmt->getResultSet();
				
				while (result->next()) {
					myId.insert(std::pair<std::string, int>(result->getString("unitid").c_str(), result->getInt("id")));
				}

				//cout << "..." << myId["2012000413"] << ".." << endl;
				delete result;
			}
			
			
			//result = stmt->executeQuery(query);
			
			


			
			delete stmt;
			delete p_stmt;

			//free(query);

		} catch (sql::SQLException& e) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			//cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}

		

		return ID;
	}

	void DB::setDebug(bool pDebug) {
		debug = pDebug;
	
	}

	bool DB::getDebug() {
		return debug;
	}

	int DB::saveTracking(const char* unitid, const char* buffer) {
		//return 1;

		//printf("....%d...=%s..\n\n\n", clients[unitid]->id_version, unitid);
		//system("color 0B");//ejemplo 

		//std::istringstream iss;
		std::string   string = ((char*)buffer);
		std::stringstream ss((char*)buffer);
		//std::istringstream stream(string);
		std::string to;
					
		//std::string to;

		if (buffer != NULL)
		{
			while (std::getline(ss, to)) {//, '\n'
				saveTrack(unitid, clients[unitid]->id, clients[unitid]->id_version, to.c_str());
				//cout << "x: " << to << endl;
			}
		}


		return 0;
	}

	int DB::saveTrack(const char* unitid, int id, int version, const char* buffer) {
		//std::string s(buffer);

		//s = "2012000413,20190717161915,-66.845906,10.500806,1,279,983.0,4,2,0.0,1,12.27,0.01,0,0,0,1";

		
		//list<string> field = XT::Tool::split(s, ',');

		std::string  mm[30];
		int n;
		XT::Tool::getItem(mm,n, buffer);
		int j = format[version]->n;
		std::string query = "INSERT INTO tracking ";
		std::string qfields = "device_cod";
		//std::string qvalues = std::to_string(n);

		
		char aux[10];
		sprintf(aux, "'%d'", id);
		std::string qvalues(aux);
		
		for (int x=0; x < j; x++) {

			if (qfields != "") {
				qfields += ",";
				qvalues += ",";
			}
			qfields = qfields +"`"+ format[version]->s[x] +"`";
			qvalues = qvalues + "'" + mm[x] + "'";
			//cout << (x + 1) << ".- " << format[version]->s[x] << " = " << mm[x] << endl;
			
		}
		query = query + "(" + qfields + ") VALUES (" + qvalues + ");";
		
		try {
			//std::cout << query;
			sql::Statement* stmt;
			sql::ResultSet* res;
			stmt = cn->createStatement();
			res =  stmt->executeQuery(query.c_str());
			delete res;
			delete stmt;
	
		} catch (sql::SQLException& e) {

			if (1 == 0) {
				cout << endl << endl << "# ERR: SQLException in " << __FILE__;
				cout << endl << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
				cout << endl << "# ERR: " << e.what();
				cout << endl << " (MySQL error code: " << e.getErrorCode();
				cout << ", SQLState: " << e.getSQLState() << " )" << endl;
				printf("\n\n\n\n");
			}
			
		}

		return 1;

		/*
		std::map<int, XT::Format*>::iterator it;
		it = format.find(version);
		for (it = format.begin(); it != format.end(); ++it) {
			cout << it->first <<

				"  . " <<
				it->second->n <<
				
				endl;
		}
*/

		for (int a = 0; a < n; a++) {

			printf("{.(%s).}", mm[a].c_str());
		}
		
		//cout << s << endl;
		j = 0;
		for (auto const& z : mm) {
			std::cout << "["<< z << "] --" << 
				format[version]->s[j++]  <<
				"\n";

			

		}
		/*return 1;
		printf("N�%d \n\n", j);
		
		list<string> ::iterator it;
		cout << s << endl;
		for (it = field.begin(); it != field.end(); ++it) {
			cout << *it << endl;
		}

		cout << "/****************** /" << endl;
		*/
		return 0;
	}

	DB::~DB() {
		delete cn;
	}

	bool DB::isSyncMsg(const char* buffer, char* id) {
		

		SyncMsg* sync_msg = (SyncMsg*)buffer;
		printf(ANSI_COLOR_CYAN "---> verification of sync (%lu)..." ANSI_COLOR_RESET, sync_msg->Keep_Alive_Device_ID);
		//puts(sync_msg->Keep_Alive_Device_ID));
		for (int i = 0; i < n_versions; i++) {
			if (sync_msg->Keep_Alive_Header == versions[i]) {
				sprintf(id, "%lu", sync_msg->Keep_Alive_Device_ID);
				return true;
			}
		}
		return false;
	}

	int* DB::getVersions() {
		return versions;
		
	}

	int DB::getVersionsCount() {
		return n_versions;
	}


}