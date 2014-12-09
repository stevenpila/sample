#include <constants.hpp>
#include "Destroyer.hpp"

#include <fstream>
#include <sstream>
#include <cstdarg>
#include <ios>

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
		    @return SUCCESS if successfully opened file and FAIL if not
		*/
		int OpenFile();

		/**
		    @description - writes log information to file
		    @param type - log type of the logged information
		    @param format - string format of information to be logged to file
		    @param ... - list of arguments passed
		    @return SUCCESS if successfully logged to file and FAIL if not
		*/
		int WriteLog(LogType const type, char const* format, ... );

	// private member functions
	private:
		/**
		    @description - gets the current datetime at run time
		    @return datetime string (Y-m-d H:M:S)		
		*/
		std::string GetTimeStamp();

		/**
		    @description - gets the equivalent string of the given log typ
		    @param type - log type
		    @return equivalent string of log type
		*/
		std::string GetLogType(LogType const type);

		/**
		    @description - closes the opened file
		    @return SUCCESS if successfully closed file and FAIL if not
		*/
		int CloseFile();

	protected:
		Logger(){}
		virtual ~Logger(){}
		friend class Destroyer<Logger>;

	// private member functions (dont modify)
	private:
		//Logger(Logger const&);
		//Logger& operator=(Logger const&);

	// private member variables
	private:
		static Logger* c_pLogger;
		static Destroyer<Logger> c_destroyer;
		static std::ofstream c_file;
		static std::string const c_fileName;

		boost::mutex c_mutexLog;
};

#define LOG_INFO(format, ... ) Logger::GetInstance()->WriteLog(INFO, format, ##__VA_ARGS__);
#define LOG_DEBUG(format, ... ) Logger::GetInstance()->WriteLog(DEBUG, format, ##__VA_ARGS__);
#define LOG_WARNING(format, ... ) Logger::GetInstance()->WriteLog(WARNING, format, ##__VA_ARGS__);
#define LOG_ERROR(format, ... ) Logger::GetInstance()->WriteLog(ERROR, format, ##__VA_ARGS__);

#endif
