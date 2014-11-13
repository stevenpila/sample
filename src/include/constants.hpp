#include <iostream>
#include <string>

typedef std::string dbString;
dbString const HOSTNAME = "localhost";
dbString const USERNAME = "root";
dbString const PASSWORD = "nekkapajigar";
dbString const DATABASE = "db_sample";

struct DBLoginConfiguration
{
	dbString s_hostname = HOSTNAME;
	dbString s_username = USERNAME;
	dbString s_password = PASSWORD;
	dbString s_database = DATABASE;
};

int const SUCCESS = 0;
int const FAIL = 1;
