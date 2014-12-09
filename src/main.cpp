#include "Database.hpp"

int main(int argc, char* argv[])
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	Logger::GetInstance()->OpenFile(); // open log file
	
	std::string sql = "SELECT * FROM names";
	std::string strErrorMsg;
	p_resultSet res;

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
			LOG_INFO("ResultSet not empty! Rows = %d", rows);

			while(res->next())
			{
				LOG_INFO("ID: %d", res->getInt(1)); // 1 = 1st column
					LOG_INFO("%s", res->getString("firstname").c_str()); // "firstname" = column name
				
				res->getString("middlename");
				if(!res->wasNull()) // check if last column called was null
				{
					LOG_INFO("%s", res->getString("middlename").c_str());
				}

				LOG_INFO("%s", res->getString("lastname").c_str()); 
			}
		}
		else
		{
			LOG_INFO("ResultSet empty!");
		}
	}

	if(SUCCESS != Database::GetInstance()->Close())
	{
		return FAIL;
	}

	return status;
}
