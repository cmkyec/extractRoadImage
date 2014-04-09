#include "logger.h"
#include <cstdlib>
#include <stdarg.h>
#include <stdio.h>
#include <log4cplus/config.hxx>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/loggingmacros.h>
/*
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/socket.h>
#include <log4cplus/helpers/threads.h>
#include <log4cplus/spi/loggerimpl.h>
#include <log4cplus/spi/loggingevent.h>
*/

namespace gentech 
{

CLogger::CLogger() {}

CLogger::~CLogger()
{
	stopSystem();
}

#define DO_LOGGER(logLevel, filename, fileline, pFormat, bufSize)\
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();\
    	\
	if(_logger.isEnabledFor(logLevel)) {    \
		va_list args;                   \
		va_start(args, pFormat);        \
		char buf[bufSize] = {0};        \
		vsprintf(buf, pFormat, args);   \
		va_end(args);                   \
		_logger.forcedLog(logLevel, buf, filename, fileline); \
	}

void CLogger::Debug( const char* filename, const int fileline, const char* pFormat, ...)
{
	DO_LOGGER(log4cplus::DEBUG_LOG_LEVEL, filename, fileline, pFormat, 1024);
}

void CLogger::Error( const char* filename, const int fileline, const char* pFormat, ...)
{
	DO_LOGGER(log4cplus::ERROR_LOG_LEVEL, filename, fileline, pFormat, 256);
}

void CLogger::Fatal( const char* filename, const int fileline, const char* pFormat, ...)
{
	DO_LOGGER(log4cplus::FATAL_LOG_LEVEL, filename, fileline, pFormat, 256);
}

void CLogger::Info( const char* filename, const int fileline, const char* pFormat, ...)
{
	DO_LOGGER(log4cplus::INFO_LOG_LEVEL, filename, fileline, pFormat, 512);
}

void CLogger::Warn( const char* filename, const int fileline, const char* pFormat, ...)
{
	DO_LOGGER(log4cplus::WARN_LOG_LEVEL, filename, fileline, pFormat, 256);
}

void CLogger::Trace( const char* filename, const int fileline, const char* pFormat, ...)
{
	DO_LOGGER(log4cplus::TRACE_LOG_LEVEL, filename, fileline, pFormat, 1024);
}

void CLogger::startSystem(const char* properties_filename)
{
	if (properties_filename == NULL) return;

	log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(false);
	log4cplus::PropertyConfigurator::doConfigure(properties_filename);
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();
	LOG4CPLUS_INFO(_logger, "Logger System Start.");
}

void CLogger::stopSystem()
{
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();
	LOG4CPLUS_INFO(_logger, "Logger System Stop.");
}
 
}
