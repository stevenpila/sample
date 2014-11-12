#include <iostream>
#include <cstdlib>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

int main(int argc, char* argv[])
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	try
	{
		sql::Driver* driver;
		//sql::Connection* con;
		//sql::Statement* stmt;
		//sql::ResultSet* res;
		
		//! create a connection to mysql
		driver = get_driver_instance();
		driver->connect("127.0.0.1", "root", "nekkapajigar");
	}catch(sql::SQLException &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
