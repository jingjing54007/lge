#include "lge_platform.h"
#include "lge_util.h"

void lge_debug_log(const char * pszFormat, ...)
{
	char szBuf[1024];

    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf_s(szBuf, 1024, 1024, pszFormat, ap);
    va_end(ap);

    WCHAR wszBuf[1024] = {0};
    MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
    OutputDebugStringW(wszBuf);
    OutputDebugStringA("\n");

    WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
    printf("%s\n", szBuf);
}




#include "GlobalFunction.h"

#ifdef WIN32
#include <direct.h>
#include <windows.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#endif

#include "PlatformDefine.h"
#include "LogManager.h"
#include "StringFormat.h"

char g_document_path[1024] = {0};

#ifndef __APPLE__
const char* GetDocumentPath()
{
#ifdef WIN32
    if (g_document_path[0] == 0)
    {
        g_document_path[0] = '.';
    }

    return g_document_path;
#elif defined ANDROID
    if (g_document_path[0] == 0) {
        strlcpy(g_document_path, "/mnt/sdcard/data/iphonehd", sizeof(g_document_path));

        if (access(g_document_path, R_OK) != 0) {
            MyCreateDirectory(g_document_path);
//          LogMsg("create: %s", g_document_path);
        }
    }

//  LogMsg("document: %s", g_document_path);

    return g_document_path;
#endif
}
#endif

// =====================================================================================================================
// =======================================================================================================================
int IsFileExist(const char* lpcszPathFilename)
{
#ifdef WIN32
    FILE* fp = fopen(lpcszPathFilename, "rb");
    if (!fp) {
        return false;
    }
    fclose(fp);
    return true;
#else
    int result = access(lpcszPathFilename, R_OK);
    if (result != 0) {
        std::string path = FORMAT("%s/%s") << GetDocumentPath() << lpcszPathFilename;
        result = access(path.c_str(), R_OK);
    }

    return result == 0;
#endif
}


// 精确到毫秒
unsigned int TimeGet(void)
{
#ifdef WIN32
    return timeGetTime();
#else
    struct timeval start;
    gettimeofday(&start, NULL);
    unsigned int dwTime = start.tv_sec * 1000 + start.tv_usec / 1000;
    return dwTime;
#endif
}

#ifdef WIN32
LARGE_INTEGER g_count_start;
LARGE_INTEGER g_cpu_frequent;
#endif

// 精确到微妙
int64 TimeGetEx(void)
{
#ifdef WIN32
    int64 dida;
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    dida = end.QuadPart - g_count_start.QuadPart;
    double times = (double)dida / (double)g_cpu_frequent.QuadPart;
    int64 timen = (int64)(times * 1000000);
    return timen;
#else
    struct timeval start;
    gettimeofday(&start, NULL);
    int64 dwTime = (int64)start.tv_sec % 10000 * 1000000 + start.tv_usec;
    return dwTime;
#endif
}


// =====================================================================================================================
// =======================================================================================================================
void MyCreateDirectory(const char *pszDirectory)
{
    if (!pszDirectory || pszDirectory[0] == 0) {
        return;
    }

#ifdef WIN32
    mkdir(pszDirectory);
#else
    mkdir(pszDirectory, S_IRUSR | S_IWUSR | S_IXUSR);
#endif
    
}

// =====================================================================================================================
// =======================================================================================================================
void MyDeleteFile(const char *pszDirectory)
{
    remove(pszDirectory);
}

#if defined(WIN32)
void LogMsgError(const char* pszErrorType, const char* pszCallStacks, const char* pszExtractInfo)
{
}

void SendErrorLogToHttp(const char* pszLog)
{
}


void SendEventToAdx(const char* event, const char* data)
{
}

FILE* MyFileOpen(const char* pszFile, const char* pszMode)
{
    return fopen(pszFile, pszMode);
}
#elif defined(ANDROID)
void SendEventToAdx(const char* event, const char* data)
{
}

FILE* MyFileOpen(const char* pszFile, const char* pszMode)
{
    return fopen(pszFile, pszMode);
}
#endif