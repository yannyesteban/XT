#include "XTDB.h"
using namespace std;
int XTDB::test() {
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "123456");

		cout << "es correcta " << con->isValid() << endl;
		/* Connect to the MySQL test database */
		con->setSchema("geocota");

		stmt = con->createStatement();

		/*

		stmt->execute("USE " EXAMPLE_DB);
stmt->execute("DROP TABLE IF EXISTS test");
stmt->execute("CREATE TABLE test(id INT, label CHAR(1))");
stmt->execute("INSERT INTO test(id, label) VALUES (1, 'a')");
		*/
		res = stmt->executeQuery("SELECT * FROM devices_commands WHERE version_id=40");
		std::cout << "WHAT " << std::endl;
		while (res->next()) {
			cout << "\t... MySQL replies: ";
			/* Access column data by alias or column name */
			//cout << res->getString("_message") << endl;
			cout << "\t... MySQL says it again: ";
			/* Access column data by numeric offset, 1 is the first column */
			cout << res->getString(1).c_str() << " -> " << res->getInt(1) << " -> " << res->getString("command").c_str() << endl;
		}
		delete res;
		delete stmt;
		delete con;

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
