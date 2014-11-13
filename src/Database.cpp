#include "Database.hpp"

Database& Database::GetInstance()
{
	static Database dbInstance;
	
	return dbInstance;
}

int Database::ConnectToDatabase()
{
	try
	{
		c_driver = get_driver_instance();
		c_conn = c_driver->connect(c_dbLoginConfig.s_hostname, c_dbLoginConfig.s_username, c_dbLoginConfig.s_password);
		c_conn->setSchema(c_dbLoginConfig.s_database);
	}
	catch(sql::SQLException &e)
	{
		std::cout << "Database::ConnectToDatabase SQLException: " << e.what() << std::endl;
		return FAIL;
	}

	return SUCCESS;
}
