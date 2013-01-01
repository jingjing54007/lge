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