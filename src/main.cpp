#include <cstdlib>

#include "Database.hpp"

int main(int argc, char* argv[])
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	std::string sql = "SELECT * FROM names";
	p_resultSet res;
	
	int status = Database::GetInstance().ExecuteQuery(sql, res);

	if(SUCCESS != status)
	{
		std::cout << "Database query failure!" << std::endl;
	}
	else
	{
		std::cout << "Database query success!" << std::endl;
		
		size_t rows = res->rowsCount(); // get rows count

		if(rows)
		{
			std::cout << "ResultSet not empty! Rows = " << rows << std::endl;

			while(res->next())
			{
				std::cout << "ID: " << res->getInt(1) << std::endl; // 1 = 1st column
				std::cout << res->getString("firstname") << " "; // "firstname" = column name
				
				res->getString("middlename");
				if(!res->wasNull()) // check if last column called was null
				{
					std::cout << res->getString("middlename") << " ";
				}

				std::cout << res->getString("lastname") << std::endl; 
			}
		}
		else
		{
			std::cout << "ResultSet empty!" << std::endl;
		}
	}
}
