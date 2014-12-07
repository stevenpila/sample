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
		LOG_ERROR("Database::ConnectToDatabase SQLException: " + static_cast<std::string>(e.what()));
		
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
	LOG_DEBUG("Database::ExecuteQuery sqlQuery = " + sqlQuery);
	p_statement stmt;

	try
	{
		boost::mutex::scoped_lock lock(c_mutexDb);

		stmt.reset(c_conn->createStatement());

		res.reset(stmt->executeQuery(sqlQuery)); // execute sql query
	}
	catch(sql::SQLException& e)
	{
		LOG_ERROR("Database::ExecuteQuery SQLException: " + static_cast<std::string>(e.what()));

		return FAIL;
	}

	return SUCCESS;
}

/* Private Member Functions */
Database::~Database()
{
	LOG_DEBUG("Database::~Database Database instance destroyed");
}
