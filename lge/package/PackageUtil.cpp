#include "PackageUtil.h"
#include <algorithm>

#ifdef WIN32
#include <Windows.h>
#endif

#ifdef ANDROID
#include <log.h>
#endif

bool PackageUtil::fileExists(const char* fileName)
{
#ifdef WIN32
	FILE* fp = fopen(fileName, "rb");
	if (!fp) {
		return false;
	}
	fclose(fp);
#else
	int result = access(fileName, R_OK);
	if (result != 0) {
		return false;
	}
#endif

	return true;
}

std::string PackageUtil::deletePathFromFilename(const char* filename)
{
	// delete path from filename
	const char* s = filename;
	const char* p = s + strlen(filename);

	// search for path separator or beginning
	while ( *p != '/' && *p != '\\' && p != s ) {
		p--;
	}

	if (p != s ) {
		++p;
		filename = p;
	}

	return filename;
}

//! trim paths
std::string PackageUtil::deletePathFromPath(const char* filename, int pathCount)
{
	// delete path from filename
	char output[256] = {0};
	strncpy(output, filename, sizeof(output) - 1);
	int i = strlen(filename);

	// search for path separator or beginning
	while ( i>=0 ) {
		if (filename[i] == '/' || filename[i] == '\\' ) {
			if ( --pathCount <= 0 ) {
				break;
			}
		}
		--i;
	}

	if (i>0) {
		output[i + 1] = 0;
	} else {
		output[0] = 0;
	}

	return output;
}

std::string PackageUtil::flattenPathName(const char* pathName)
{
#ifdef WIN32
	if (!pathName || pathName[0] == 0) {
		return "";
	}

	std::string directory = pathName;
	std::replace(directory.begin(), directory.end(), '\\', '/');
	if (directory.back() != '/') {
		directory.append("/");
	}

	std::string dir;
	std::string subdir;

	int lastpos = 0;
	int pos = 0;
	bool lastWasRealDir=false;

	if (directory == "." || directory == "./" || directory == ".\\") {
		char szCurrent[256] = {0};
		GetCurrentDirectoryA(255, szCurrent);
		directory.replace(0, 2, szCurrent);

		std::replace(directory.begin(), directory.end(), '\\', '/');
		if (directory.back() != '/') {
			directory.append("/");
		}
	}

	while ((pos = directory.find('/', lastpos)) >= 0) {
		subdir = directory.substr(lastpos, pos - lastpos + 1);

		if (subdir == "../") {
			if (lastWasRealDir) {
				deletePathFromPath(dir.c_str(), 2);
				lastWasRealDir=(dir.size()!=0);
			} else {
				dir.append(subdir);
				lastWasRealDir=false;
			}
		} else if (subdir != "./") {
			dir.append(subdir);
			lastWasRealDir=true;
		}

		lastpos = pos + 1;
	}
	directory = dir;
	return directory;
#else
    return pathName;
#endif
}

void PackageUtil::logMsg(const char * pszFormat, ...)
{
	char szBuf[1024];

	va_list ap;
	va_start(ap, pszFormat);
#ifdef WIN32
	vsnprintf_s(szBuf, 1024, 1024, pszFormat, ap);
#else
	vsnprintf(szBuf, 1024, pszFormat, ap);
#endif
	va_end(ap);

#ifdef WIN32
	WCHAR wszBuf[1024] = {0};
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
	OutputDebugStringW(wszBuf);
	OutputDebugStringA("\n");

	WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
	printf("%s\n", szBuf);
#else
	printf("%s\n", szBuf);
#endif
}
