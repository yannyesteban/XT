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
			cn->setSchema(pInfo.dbname);
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
		std::map<int, std::string> myId2;

		std::map<char *, int> myId3;

		int ID = 0;
		try {
			//sql::Driver* driver;
			//sql::Connection* con;
			sql::Statement* stmt;
			sql::ResultSet* result;

			stmt = cn->createStatement();
			
			char* query = (char*)malloc(512);
			
			sprintf(query, "SELECT id,unitid FROM devices WHERE unitid='%s'", unitid);

			result = stmt->executeQuery(query);
			
			while (result->next()) {

				ID = result->getInt("id");
				myId[result->getString("unitid").c_str()] = result->getInt("id");
				myId2[result->getInt("id")] = result->getString("unitid").c_str();
				myId3.insert(std::pair<char *, int>((char *)result->getString("unitid").c_str(), 4554));
				//myId3[(const char *)result->getString("unitid").c_str()] = result->getInt("id");
				cout << endl << result->getString("unitid").c_str() <<  endl;
				cout << result->getInt("id") << "=>" << myId2[result->getInt("id")] << endl;
			}
			delete result;
			delete stmt;
			cout << "........." << myId3[(char *)"2012000413"] << "====" << myId["2012000413"]<<endl;
			//printf("....%d....%s...", myId["2012000413"], myId2[1]);

			free(query);

		} catch (sql::SQLException& e) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}

		

		return ID;
	}

	DB::~DB() {
		delete cn;
	}


}
