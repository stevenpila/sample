#include <constants.hpp>

#include <memory>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#ifndef _DATABASE_H_
#define _DATABASE_H_

class Database
{
	// public member functions
 	public:
		static Database& GetInstance();
		int ConnectToDatabase();		

	// private member functions
	private:
		 		

	// private member functions (dont modify)
	private:
		Database(){};
		Database(Database const&);
		void operator=(Database const&);

	// private member variables
	private:
		sql::Driver* c_driver;
		sql::Connection* c_conn;
		sql::Statement* c_stmt;
		sql::ResultSet* c_res;

		DBLoginConfiguration c_dbLoginConfig;
};

#endif
