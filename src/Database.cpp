#include "Database.hpp"

#include <memory>
#include <boost/scoped_ptr.hpp>

Database& Database::GetInstance()
{
	static Database dbInstance;
	
	return dbInstance;
}

int Database::ExecuteQuery(std::string sqlQuery, p_resultSet& res)
{
	int status = ConnectToDatabase(); // establish connection to database

	if(SUCCESS == status)
	{
		try
		{
			boost::mutex::scoped_lock lock(c_mutexDb);

			p_statement stmt(c_conn->createStatement());

			res.reset(stmt->executeQuery(sqlQuery)); // execute sql query
		}
		catch(sql::SQLException& e)
		{
			std::cout << "Database::ExecuteQuery SQLException: " << e.what() << std::endl;

			return FAIL;
		}
	}
	else
	{
		std::cout << "Database::ExecuteQuery Database connection failure" << std::endl;
	}

	return status;
}

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
