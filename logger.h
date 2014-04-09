#ifndef _LOGGER_H_
#define _LOGGER_H_

namespace gentech
{

class CLogger
{
public:
	CLogger();
	
	virtual ~CLogger();

	void startSystem(const char* properties_filename);

	void stopSystem();
public:
	void Debug(const char* filename, const int fileline, const char* pFormat, ...);

	void Error(const char* filename, const int fileline, const char* pFormat, ...);

	void Fatal(const char* filename, const int fileline, const char* pFormat, ...);

	void Info(const char* filename, const int fileline, const char* pFormat, ...);

	void Warn(const char* filename, const int fileline, const char* pFormat, ...);

	void Trace(const char* filename, const int fileline, const char* pFormat, ...);
public:
	static inline CLogger* getSingletonPtr()
	{
		return &getSingleton();
	}
	static inline CLogger& getSingleton()
	{
		static CLogger _instance; 
		return _instance;
	}
};

#define g_Logger  gentech::CLogger::getSingleton()
#define g_pLogger gentech::CLogger::getSingletonPtr()

#define ASSERT_LOG(expr)\
    if ((expr)) {;} else g_Logger.Error(__FILE__, __LINE__, #expr);

}

#endif /* _LOGGER_H_ */
