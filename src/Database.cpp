#include "Database.hpp"

#include <memory>
#include <boost/scoped_ptr.hpp>

Database* Database::c_pDatabase = NULL;
Destroyer<Database> Database::c_destroyer;

/* Public Member Functions */
Database* Database::GetInstance()
{
	if(!c_pDatabase)
	{
		c_pDatabase = new Database;
		c_destroyer.SetSingleton(c_pDatabase);
	}
	
	return c_pDatabase;
}

int Database::ConnectToDatabase()
{
	LOG_DEBUG("Database::ConnectToDatabase");

	try
	{
		boost::mutex::scoped_lock lock(c_mutexDb);		
		
		sql::Driver* driver;

		driver = get_driver_instance();
		c_conn.reset(driver->connect(HOSTNAME, USERNAME, PASSWORD)); // connects to database
		c_conn->setSchema(DATABASE); // use database

		LOG_DEBUG("Database::ConnectToDatabase Connection established");
	}
	catch(sql::SQLException& e)
	{
		LOG_ERROR("Database::ConnectToDatabase SQLException: %s", e.what());
		return FAIL;
	}
	catch(...)
	{
		LOG_ERROR("Database::ConnectToDatabase Unknown exception");
		
		return FAIL;
	}

	return SUCCESS;
}

int Database::ExecuteQuery(std::string sqlQuery, p_resultSet& res)
{
	LOG_DEBUG("Database::ExecuteQuery sqlQuery = %s", sqlQuery.c_str());
	p_statement stmt;

	try
	{
		boost::mutex::scoped_lock lock(c_mutexDb);

		stmt.reset(c_conn->createStatement());

		res.reset(stmt->executeQuery(sqlQuery)); // execute sql query
	}
	catch(sql::SQLException& e)
	{
		LOG_ERROR("Database::ExecuteQuery SQLException: %s", e.what());

		return FAIL;
	}

	return SUCCESS;
}

int Database::Close()
{
	LOG_DEBUG("Database::Close Close database connection");
	
	try
	{
		c_conn->close();	
	}
	catch(sql::SQLException& e)
	{
		LOG_ERROR("Database::Close SQLException: %s", e.what());
		
		return FAIL;	
	}

	return SUCCESS;
}

/* Private Member Functions */
