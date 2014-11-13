#include <cstdlib>

#include "Database.hpp"

int main(int argc, char* argv[])
{
	static_cast<void>(argc);
	static_cast<void>(argv);

	int status = Database::GetInstance().ConnectToDatabase();

	if(status)
	{
		std::cout << "Database connection failure!!!" << std::endl;
	}
}
