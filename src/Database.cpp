#include "Database.hpp"

#include <memory>
#include <boost/scoped_ptr.hpp>

Database* Database::c_pDatabase = NULL;

/* Public Member Functions */
Database* Database::GetInstance()
{
	if(!c_pDatabase)
	{
		c_pDatabase = new Database;
	}
	
	return c_pDatabase;
}

int Database::ExecuteQuery(std::string sqlQuery, p_resultSet& res)
{
	int status = ConnectToDatabase(); // establish connection to database

	if(SUCCESS == status)
	{
		p_statement stmt;

		try
		{
			boost::mutex::scoped_lock lock(c_mutexDb);

			stmt.reset(c_conn->createStatement());

			res.reset(stmt->executeQuery(sqlQuery)); // execute sql query
		}
		catch(sql::SQLException& e)
		{
			std::cout << "Database::ExecuteQuery SQLException: " << e.what() << ", sqlQuery = " << sqlQuery << std::endl;

			return FAIL;
		}
	}
	else
	{
		std::cout << "Database::ExecuteQuery Database connection failure" << std::endl;
	}

	return status;
}

/* Private Member Functions */
int Database::ConnectToDatabase()
{
	try
	{
		boost::mutex::scoped_lock lock(c_mutexDb);		
		
		sql::Driver* driver;

		driver = get_driver_instance();
		c_conn.reset(driver->connect(HOSTNAME, USERNAME, PASSWORD)); // connects to database
		c_conn->setSchema(DATABASE); // use database

		std::cout << "Database::ConnectToDatabase Connection established" << std::endl;
	}
	catch(sql::SQLException& e)
	{
		std::cout << "Database::ConnectToDatabase SQLException: " << e.what() << std::endl;
		
		return FAIL;
	}
	catch(...)
	{
		std::cout << "Database::ConnectToDatabase Unknown exception" << std::endl;
		
		return FAIL;
	}

	return SUCCESS;
}

Database::~Database()
{
	std::cout << "Database::~Database Database instance destroyed" << std::endl;
}
