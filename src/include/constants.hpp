#include <iostream>
#include <string>

/**
    @brief - database configuration
 */
#define HOSTNAME "tcp://127.0.0.1:3306"
#define USERNAME "nekkapajigar"
#define PASSWORD "root"
#define DATABASE "db_sample"

int const SUCCESS = 0;
int const FAIL = 1;

enum LogType
{
	INFO, 
	DEBUG, 
	WARNING, 
	ERROR
};
