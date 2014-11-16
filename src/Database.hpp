#include <constants.hpp>

#include <memory>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#ifndef _DATABASE_H_
#define _DATABASE_H_

typedef std::auto_ptr<sql::Connection> p_connection;
typedef std::auto_ptr<sql::ResultSet> p_resultSet;
typedef std::auto_ptr<sql::Statement> p_statement;

class Database
{
	// public member functions
 	public:
		/**
		    @description - get instance of Database object
		    @return instance of Database object
		 */
		static Database& GetInstance();

		/**
		    @description - execute the given sql query string
		    @param sqlQuery - sql query string
		    @param res - container of the sql query result
		    @return container with the result from the sql query
		 */
		int ExecuteQuery(std::string const sqlQuery, p_resultSet& res);

	// private member functions
	private:
		/**
		    @description - establish a connection to database
		    @return SUCCESS(0) if connection is open and FAIL(1) if not
		 */
		int ConnectToDatabase();
	
	// private member functions (dont modify)
	private:
		Database(){};
		Database(Database const&);
		void operator=(Database const&);

	// private member variables
	private:
		boost::mutex c_mutexDb;

		p_connection c_conn;
};

#endif
