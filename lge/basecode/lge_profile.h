#ifndef __SIMPLE_PROFILE_HH__
#define __SIMPLE_PROFILE_HH__

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef ANDROID
#include <android/log.h>
#endif

// 一般情况下undef ENABLE_PROFILE 则不会对代码有任何影响
#if defined DEBUG || defined _DEBUG
	#define ENABLE_PROFILE
#else
	#undef ENABLE_PROFILE
#endif

void ProfileInit(void);					// 初始化性能分析模块

int ProfileBegin(const char* pszName);	// 开启一个分析器
void ProfileEnd(const char* pszName);	// 结束一个分析器
void ProfileDumpOutputToBuffer(void);	// 将分析信息结果输出（每帧调用一次）
void ProfileDraw(void);					// 将分析结果绘制到屏幕上


// c++形式封装 
// eg:在欲进行分析的函数内执行
// PROFILE("this is a test");
// 如果只有函数内部分代码段需要分析，可以加上 { }

#ifdef ENABLE_PROFILE
	#define PROFILE(r) CSimpleProfiler simpleProfiler(r);
#else
	#define PROFILE(r)
#endif

#define MAX_PROFILE_NAME_LEN 32
class CSimpleProfiler
{
public:
	CSimpleProfiler(const char* pszName);
	~CSimpleProfiler();
private:
	int m_idProfiler;
};

// 在调试代码时，可以用这两个函数开关性能分析
void BeginProfile();
void EndProfile();

class TimeLogger
{
public:
    TimeLogger(const char* name);
    ~TimeLogger();
private:
    unsigned int m_startTime;
    std::string m_name;
};

class DebugTimeLogger
{
public:
	DebugTimeLogger(const char* name, const char* data)
	{
		memset(m_name, 0, sizeof(m_name));
		memset(m_data, 0, sizeof(m_data));
#ifdef WIN32
		m_startTime = GetTickCount();
#else
        struct timeval start;
        gettimeofday(&start, NULL);
        m_startTime = start.tv_sec * 1000 + start.tv_usec / 1000;
#endif
		strncpy(m_name, name, sizeof(m_name) - 1);
		strncpy(m_data, data, sizeof(m_data) - 1);
	}

	~DebugTimeLogger()
	{
        unsigned int curTime = 0;
#ifdef WIN32
		curTime = GetTickCount();
#else
        struct timeval start;
        gettimeofday(&start, NULL);
        curTime = start.tv_sec * 1000 + start.tv_usec / 1000;
#endif
		unsigned int time = curTime - m_startTime;
		char buffer[256] = {0};
		snprintf(buffer, sizeof(buffer), "%s   %d    %s\n", m_name, time, m_data);
        
#ifdef WIN32
		OutputDebugStringA(buffer);
#elif defined __APPLE__
		printf("%s", buffer);
#elif defined ANDROID
        __android_log_print(ANDROID_LOG_DEBUG, "wing debug info",  buffer);
#endif
	}
private:
	unsigned int m_startTime;
	char m_name[256];
	char m_data[256];
};

#include "SysInfo.h"
class MemoryLogger
{
public:
    MemoryLogger(const char* tag)
    {
        memset(m_tag, 0, sizeof(m_tag));
        strncpy(m_tag, tag, sizeof(m_tag) - 1);

        m_beginMemory = GetProcessMemory() / 1024.0f;
        char text[256] = {0};
        snprintf(text, sizeof(text), "%s  ---begin  proess:%.1fmb   free:%.1fmb\n", m_tag,  m_beginMemory, GetAvailableMemory() / 1024.0f);
        
#ifdef WIN32
//		OutputDebugStringA(text);
#else
//        printf("%s", text);
#endif
    }
    
    ~MemoryLogger()
    {
        char text[256] = {0};
        float endMemory = GetProcessMemory() / 1024.0f;
        float delta = endMemory - m_beginMemory;
        snprintf(text, sizeof(text), "%s  ---over   proess:%.1fmb (%.1fmb)   free:%.1fmb\n", m_tag, endMemory, delta, GetAvailableMemory() / 1024.0f);
        
#ifdef WIN32
		OutputDebugStringA(text);
#elif defined __APPLE__
		printf("%s", text);
#elif defined ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "wing debug info",  text);
#endif
    }
private:
    char m_tag[256];
    float m_beginMemory;
};

#if defined DEBUG || defined _DEBUG || defined COCOS2D_DEBUG
#define DEBUG_TIME(x, d) DebugTimeLogger  debugTimeLogger(x, d)
#define DEBUG_MEM(x) MemoryLogger memoryLogger(x)
#else
#define DEBUG_TIME(x, d)
#define DEBUG_MEM(x) 
#endif

#ifdef ENABLE_PROFILE
#if defined DEBUG || defined _DEBUG
#define LOGTIME(r) TimeLogger timeLogger(r);
#else
#define LOGTIME(r)
#endif
#else
#define LOGTIME(r)
#endif

#endif