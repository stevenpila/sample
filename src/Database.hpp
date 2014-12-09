#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "Logger.hpp"
#include "Destroyer.hpp"

#include <memory>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

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
		static Database* GetInstance();

		/**
		    @description - establish a connection to database
		    @return SUCCESS if connection is open and FAIL if not
		 */
		int ConnectToDatabase();

		/**
		    @description - execute the given sql query string
		    @param sqlQuery - sql query string
		    @param res - container of the sql query result
		    @return container with the result from the sql query
		 */
		int ExecuteQuery(std::string const sqlQuery, p_resultSet& res);

		int Close();

	// private member functions
	protected:
		Database(){}
		virtual ~Database(){}
		friend class Destroyer<Database>;

	// private member functions (dont modify)
	private:
		//Database(Database const&);
		//Database& operator=(Database const&);

	// private member variables
	private:
		static Database* c_pDatabase;
		static Destroyer<Database> c_destroyer;

		boost::mutex c_mutexDb;

		p_connection c_conn;
};

#endif
