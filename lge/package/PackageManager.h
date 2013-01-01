#pragma once
#include <vector>
#include "MySingleton.h"

class Package;
class PackageManager : public MySingleton<PackageManager>
{
public:
	PackageManager();
	Package* openPackage(const char* packageName);
	void closePackage(const char* packageName);
	void closeAllPackage();

	unsigned char* getFileData(const char* fileName, unsigned long* dataSize);
	unsigned char* getFileText(const char* fileName, unsigned long* dataSize);
	
public:
	void archiveFile(const char* fileName, const char* pathName);
	void archivePath(const char * pFilePath);
	void createMpqPackage(const char* pathName, const char* pszMpqName = NULL);
private:
	Package* m_currentPackage;
	std::vector<Package*> m_allPackages;

};

#ifdef WIN32
#pragma comment(lib, "libpackage")
#endif