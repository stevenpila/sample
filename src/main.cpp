#include <cstdlib>

#include "Database.hpp"

int main(int argc, char* argv[])
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	std::string sql = "SELECT * FROM names";
	std::string strFile = "Logs.txt";
	std::string strErrorMsg;
	p_resultSet res;

	remove(strFile.c_str()); // remove existing log file first

	if(SUCCESS != Logger::GetInstance()->OpenFile(strFile)) // creating and opening log file
	{
		return FAIL;
	}

	if(SUCCESS != Database::GetInstance()->ConnectToDatabase()) // establish connection to database
	{
		return FAIL;
	}
	
	int status = Database::GetInstance()->ExecuteQuery(sql, res); // executing mysql query

	if(SUCCESS == status)
	{
		LOG_INFO("Database query success!");
		
		size_t rows = res->rowsCount(); // get rows count

		if(rows)
		{
			//LOG_INFO("ResultSet not empty! Rows = " + static_cast<std::string>(rows));

			while(res->next())
			{
				//LOG_INFO("ID: " + static_cast<std::string>(res->getInt(1)); // 1 = 1st column
				//LOG_INFO(static_cast<std::string>(res->getString("firstname"))); // "firstname" = column name
				
				res->getString("middlename");
				if(!res->wasNull()) // check if last column called was null
				{
					//LOG_INFO(static_cast<std::string>(res->getString("middlename")));
				}

				//LOG_INFO(static_cast<std::string>(res->getString("lastname"))); 
			}
		}
		else
		{
			//LOG_INFO("ResultSet empty!");
		}
	}
	
	if(SUCCESS != Logger::GetInstance()->CloseFile()) // closing log file
	{
		return FAIL;
	}

	return status;
}
