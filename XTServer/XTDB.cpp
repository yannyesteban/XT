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

		std::map<int, InfoProto> proto;
		

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

				while (result->next()) {
					InfoProto proto_x;
					proto_x.id_device = result->getInt("id");
					proto_x.tag_length = result->getInt("tag_length");
					proto_x.pass_default = result->getString("pass_default").c_str();
					proto_x.protocol_pre = result->getString(4).c_str();
					proto_x.sync_header = result->getString("sync_header").c_str();
					proto_x.protocol_pre = result->getString("protocol_pre").c_str();
					proto.insert(std::pair<int, InfoProto>(result->getInt("id"), proto_x));
					proto_x.protocol_pre = (const char *)result->getString(4).c_str();
					
					const char * x = result->getString("protocol_pre").c_str();
					
					cout << "..." << proto[proto_x.id_device].id_device <<" " << 
						//result->getString("protocol_pre").c_str() << ".." <<
						x << "...." <<
						proto_x.protocol_pre
						<< ".." << endl;
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

				cout << "..." << myId["2012000413"] << ".." << endl;
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

	DB::~DB() {
		delete cn;
	}


}
