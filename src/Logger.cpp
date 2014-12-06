#include "Logger.hpp"

#include <boost/lexical_cast.hpp>

Logger* Logger::c_pLogger = NULL;

Logger* Logger::GetInstance()
{
	if(!c_pLogger)
	{
		c_pLogger = new Logger;
	}

	return c_pLogger;
}

int Logger::OpenFile(std::string const fileName)
{
	boost::mutex::scoped_lock lock(c_mutexLog);
	
	c_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		c_file.open(fileName.c_str(), std::ofstream::app); // open the file

		if(!c_file.is_open()) // check if file is successfully opened
		{
			std::cout << "Logger::OpenFile File not opened successfully" << std::endl;

			return FAIL;
		}
	}
	catch(std::ofstream::failure e)
	{
		std::cerr << "Logger::OpenFile Opening file exception: " << e.what() << std::endl;

		return FAIL;
	}
	catch(...)
	{
		std::cout << "Logger::OpenFile Unknown exception" << std::endl;
		
		return FAIL;
	}

	std::cout << "Logger::OpenFile File opened successfully" << std::endl;

	return SUCCESS;
}

int Logger::WriteLog(LogType const type, std::string const log)
{
	boost::mutex::scoped_lock lock(c_mutexLog);

	c_file.exceptions(std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		std::stringstream strLog;
		std::string strType = GetLogType(type);
		std::string strTimestamp = GetTimeStamp();

		strLog << strTimestamp << " - " << strType << " - " << __FILE__ << ":" << __LINE__ << " - " << log << std::endl;

		std::cout << strLog.str();
		c_file << strLog.str();
		
	}
	catch(std::ofstream::failure e)
	{
		std::cerr << "Logger::WriteLog Logging to file exception: " << e.what() << std::endl;

		return FAIL;
	}
	catch(...)
	{
		std::cout << "Logger::WriteLog Unknown exception" << std::endl;

		return FAIL;
	}

	std::cout << "Logger::WriteLog Successfully wrote to log file" << std::endl;

	return SUCCESS;
}

int Logger::CloseFile()
{
	boost::mutex::scoped_lock lock(c_mutexLog);

	c_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	try
	{
		c_file.close(); // close the file
	}
	catch(std::ofstream::failure e)
	{
		std::cerr << "Logger::CloseFile Closing file exception: " << e.what() << std::endl;

		return FAIL;
	}
	catch(...)
	{
		std::cout << "Logger::CloseFile Unknown exception" << std::endl;

		return FAIL;
	}

	std::cout << "Logger::CloseFile File closed successfully" << std::endl;

	return SUCCESS;
}

std::string Logger::GetTimeStamp()
{
	std::string timeStamp = "TIMESTAMP";

	return timeStamp;
}

std::string Logger::GetLogType(LogType const type)
{
	std::string strType;

	switch(type)
	{
		case INFO: strType = "INFO"; break;
		case DEBUG: strType = "DEBUG"; break;
		case WARNING: strType = "WARNING"; break;
		case ERROR: strType = "ERROR"; break;
		default: strType = "UNKOWN"; break;
	};

	return strType;
}
