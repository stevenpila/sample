#include "Logger.hpp"

#include <boost/lexical_cast.hpp>

Logger* Logger::c_pLogger = NULL;
const std::string Logger::c_fileName = "Logs.txt";
std::ofstream Logger::c_file;
Destroyer<Logger> Logger::c_destroyer;

/* Public Member Functions */
Logger* Logger::GetInstance()
{
	if(!c_pLogger)
	{
		c_pLogger = new Logger;
		c_destroyer.SetSingleton(c_pLogger);
	}

	return c_pLogger;
}

int Logger::OpenFile()
{
	try
	{
		boost::mutex::scoped_lock lock(c_mutexLog);

		c_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);

		c_file.open(c_fileName.c_str(), std::ios::out | std::ios::app); // open the file

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

	//std::cout << "Logger::OpenFile File opened successfully" << std::endl;

	return SUCCESS;
}

int Logger::WriteLog(LogType const type, char const* format, ... )
{
	if(c_file.is_open())
	{
		try
		{
			boost::mutex::scoped_lock lock(c_mutexLog);

			c_file.exceptions(std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit);

			char logMessage[256];
			va_list args;
			va_start(args, format);
			vsprintf(logMessage, format, args);

			std::string strType = GetLogType(type);
			std::string strTimestamp = GetTimeStamp();

			c_file << strTimestamp << " - " << strType << " - " << __FILE__ << ":" << __LINE__ << " - " << logMessage << std::endl;

			//std::cout << strTimestamp << " - " << strType << " - " << __FILE__ << ":" << __LINE__ << " - " << logMessage << std::endl;	
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
	}
	else
	{
		std::cout << "Logger::WriteLog File is not opened logString = " << format << std::endl;
	}

	//std::cout << "Logger::WriteLog Successfully wrote to log file" << std::endl;

	return SUCCESS;
}

/* Private Member Functions */
std::string Logger::GetTimeStamp()
{
	std::ostringstream timeStamp;

	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	boost::posix_time::time_facet* facet = new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S");

	timeStamp.imbue(std::locale(timeStamp.getloc(), facet));
	timeStamp << now;

	return timeStamp.str();
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

int Logger::CloseFile()
{
	try
	{
		boost::mutex::scoped_lock lock(c_mutexLog);

		c_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);

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

	//std::cout << "Logger::CloseFile File closed successfully" << std::endl;

	return SUCCESS;
}
