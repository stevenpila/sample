#include <constants.hpp>

#include <fstream>
#include <sstream>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#ifndef _LOGGER_H_
#define _LOGGER_H_

class Logger
{
	// public member functions
	public:
		/**
		    @description - get instance of Logger object
		    @return instance of Logger object
		 */
		static Logger* GetInstance();

		/**
		    @description - opens the given file
		    @param fileName - file name to be open
		    @return SUCCESS if successfully opened file and FAIL if not
		*/
		int OpenFile(std::string const& fileName);

		/**
		    @description - writes log information to file
		    @param type - log type of the logged information
		    @param log - string information to be logged to file
		    @return SUCCESS if successfully logged to file and FAIL if not
		*/
		int WriteLog(LogType const type, std::string const& log);

		/**
		    @description - closes the opened file
		    @return SUCCESS if successfully closed file and FAIL if not
		*/
		int CloseFile();

	// private member functions
	private:
		std::string GetTimeStamp();

		/**
		    @description - gets the equivalent string of the given log typ
		    @param type - log type
		    @return equivalent string of log type
		*/
		std::string GetLogType(LogType const type);

	// private member functions (dont modify)
	private:
		Logger(){};
		Logger(Logger const&);
		Logger& operator=(Logger const&);

	// private member variables
	private:
		static Logger* c_pLogger;

		boost::mutex c_mutexLog;

		std::ofstream c_file;
};

#define LOG_INFO(string) Logger::GetInstance()->WriteLog(INFO, string);
#define LOG_DEBUG(string) Logger::GetInstance()->WriteLog(DEBUG, string);
#define LOG_WARNING(string) Logger::GetInstance()->WriteLog(WARNING, string);
#define LOG_ERROR(string) Logger::GetInstance()->WriteLog(ERROR, string);

#endif
