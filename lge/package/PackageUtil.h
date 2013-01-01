#pragma once
#include <string>

class PackageUtil
{
public:
	static bool fileExists(const char* fileName);
	static std::string deletePathFromFilename(const char* filename);
	static std::string deletePathFromPath(const char* filename, int pathCount);
	static std::string flattenPathName(const char* pathName);

	static void logMsg(const char * pszFormat, ...);
};


#ifndef WIN32
#ifndef stricmp
#define stricmp strcasecmp
#endif
#endif