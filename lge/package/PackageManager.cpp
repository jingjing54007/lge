#include "PackageManager.h"
#include "Package.h"
#include "MpqPackage.h"
#include "ZipPackage.h"
#include "PackageUtil.h"

#include <string>
#include <algorithm>

// 打包文件时使用
#define WORK_PATH "e:/MPQs/"

PackageManager::PackageManager()
{
	m_currentPackage = NULL;
}

Package* PackageManager::openPackage(const char* packageName)
{
	if (!packageName || packageName[0] == 0) {
		return NULL;
	}

	if (!PackageUtil::fileExists(packageName)) {
		return NULL;
	}

	std::string fileName = packageName;
	int extPos = fileName.find_last_of('.');
	std::string ext = fileName.substr(extPos + 1);
	if (stricmp(ext.c_str(), "mpq") == 0) {
		MpqPackage* package = new MpqPackage;
		if (package && package->open(packageName)) {
			m_allPackages.push_back(package);
			m_currentPackage = package;
			return package;
		}
	} else if (stricmp(ext.c_str(), "zip") == 0) {
	}

	return NULL;
}

void PackageManager::closePackage(const char* packageName)
{

}

void PackageManager::closeAllPackage()
{

}


unsigned char* PackageManager::getFileText(const char* fileName, unsigned long* dataSize)
{
	if (m_currentPackage && m_currentPackage->fileExist(fileName)) {
		unsigned char* buffer = m_currentPackage->getFileText(fileName, dataSize);
		if (buffer) {
			return buffer;
		}
	}

	for (std::vector<Package*>::iterator itr = m_allPackages.begin(); itr != m_allPackages.end(); ++itr) {
		Package* package = *itr;
		if (!package) {
			continue;
		}
        
		if (!package->fileExist(fileName)) {
			continue;
		}
        
		unsigned char* buffer = package->getFileText(fileName, dataSize);
		if (buffer) {
			return buffer;
		}
	}
    
	return NULL;
}

unsigned char* PackageManager::getFileData(const char* fileName, unsigned long* dataSize)
{
	if (m_currentPackage && m_currentPackage->fileExist(fileName)) {
		unsigned char* buffer = m_currentPackage->getFileData(fileName, dataSize);
		if (buffer) {
			return buffer;
		}
	}

	for (std::vector<Package*>::iterator itr = m_allPackages.begin(); itr != m_allPackages.end(); ++itr) {
		Package* package = *itr;
		if (!package) {
			continue;
		}

		if (!package->fileExist(fileName)) {
			continue;
		}

		unsigned char* buffer = package->getFileData(fileName, dataSize);
		if (buffer) {
			return buffer;
		}
	}

	return NULL;
}


// 创建mpq包
static HANDLE s_currentMpqHandle = NULL;
static std::string s_rootDir;
static FILE* s_fpListFile = NULL;

void PackageManager::createMpqPackage(const char* pathName, const char* pszMpqName)
{
#ifdef WIN32
	if (!pathName || pathName[0] == 0) {
		return;
	}

	PackageUtil::logMsg("createPackage begin");

	std::string realPath = PackageUtil::flattenPathName(pathName);
	s_rootDir = realPath;

	std::replace(s_rootDir.begin(), s_rootDir.end(), '\\', '/');
	std::transform(s_rootDir.begin(), s_rootDir.end(), s_rootDir.begin(), tolower);
	if (s_rootDir.back() != '/') {
		s_rootDir += '/';
	}

	std::string fileName;
	if (realPath.back() == '/') {
		int last = realPath.find_last_of('/', realPath.size() - 2);
		fileName = realPath.substr(last + 1, realPath.size() - last - 1 - 1);
	} else {
		int last = realPath.find_last_of('/');
		fileName = realPath.substr(last, realPath.size() - last);
	}

	std::string listFileName = WORK_PATH + fileName + ".txt";
	std::string mpqName = WORK_PATH;
	mpqName += fileName;
	mpqName += ".mpq";

	if (PackageUtil::fileExists(mpqName.c_str())) {
		remove(mpqName.c_str());
	}

#ifdef WIN32
	wchar_t szMpqName[256] = {0};
	MultiByteToWideChar (CP_ACP, 0, mpqName.c_str(), mpqName.size(), szMpqName, 255);

	if (!SFileCreateArchive(szMpqName, MPQ_CREATE_ARCHIVE_V4 | MPQ_CREATE_ATTRIBUTES, 4000, &s_currentMpqHandle)) {
		s_currentMpqHandle = NULL;
		return;
	}
#else
	if (!SFileCreateArchive(mpqName.c_str(), MPQ_CREATE_ARCHIVE_V4 | MPQ_CREATE_ATTRIBUTES, 4000, &s_currentMpqHandle)) {
		s_currentMpqHandle = NULL;
		return;
	}
#endif

	if (s_fpListFile) {
		fclose(s_fpListFile);
	}

	s_fpListFile = fopen(listFileName.c_str(), "w");
	archivePath(realPath.c_str());
	fclose(s_fpListFile);
	SFileCloseArchive(s_currentMpqHandle);

	PackageUtil::logMsg("createPackage over");

	// 测试文件是否正确
#ifdef WIN32
	if(SFileOpenArchive(szMpqName, 0, 0, &s_currentMpqHandle)) {
        SFileCloseArchive(s_currentMpqHandle);
		return;
	}
#else
	if(SFileOpenArchive(mpqName.c_str(), 0, 0, &s_currentMpqHandle)) {
		SFileCloseArchive(s_currentMpqHandle);
		return;
	}
#endif

	assert(false);
#endif
}

void PackageManager::archiveFile(const char* fileName, const char* pathName)
{
#ifdef WIN32
	if (!fileName || fileName[0] == 0 || !pathName || pathName[0] == 0) {
		return;
	}

	std::string tempFileName = fileName;
//	int pos = realPath.rfind('.') + 1;
	std::string ext = tempFileName.substr(tempFileName.rfind('.') + 1);

	if (stricmp(ext.c_str(), "mpq") == 0) {
		return;
	}

	std::string fullName = pathName;
	std::replace(fullName.begin(), fullName.end(), '\\', '/');
	if (fullName.back() != '/') {
		fullName += '/';
	}
	fullName += fileName;
	std::transform(fullName.begin(), fullName.end(), fullName.begin(), tolower);

	std::string indexName = fullName.substr(s_rootDir.size());
	PackageUtil::logMsg(indexName.c_str());

#ifdef WIN32
	wchar_t szFileName[256] = {0};
	MultiByteToWideChar (CP_ACP, 0, fullName.c_str(), fullName.size(), szFileName, 255);
	SFileAddFileEx(s_currentMpqHandle, szFileName, indexName.c_str(), MPQ_FILE_COMPRESS, MPQ_COMPRESSION_ZLIB, MPQ_COMPRESSION_NEXT_SAME);
#else
	SFileAddFileEx(s_currentMpqHandle, fullName.c_str(), indexName.c_str(), 0, MPQ_FILE_COMPRESS, MPQ_COMPRESSION_NEXT_SAME);
#endif

	if (s_fpListFile) {
		fputs(indexName.c_str(), s_fpListFile);
		fputs("\n", s_fpListFile);
	}
#endif
}

void PackageManager::archivePath(const char * pFilePath)
{
#ifdef WIN32
	if (!pFilePath || pFilePath[0] == 0) {
		return;
	}

    WIN32_FIND_DATAA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char DirSpec[MAX_PATH + 1];// 指定路径
    DWORD dwError;

    strncpy (DirSpec, pFilePath, strlen(pFilePath) + 1);
	if (pFilePath[strlen(pFilePath) - 1] == '/') {
		strncat(DirSpec, "*", 2);
	} else {
		strncat(DirSpec, "/*", 3);
	}

    hFind = FindFirstFileA(DirSpec, &FindFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf ("Invalid file handle. Error is %u ", GetLastError());
        return ;
    }

    if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
		archiveFile(FindFileData.cFileName, pFilePath);
	} else if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        && strcmp(FindFileData.cFileName, ".") != 0
        && strcmp(FindFileData.cFileName, "..") != 0
		&& strcmp(FindFileData.cFileName, ".svn") != 0) {   //找到目录
        char Dir[MAX_PATH + 1];
        strcpy(Dir, pFilePath);
		if (pFilePath[strlen(pFilePath) - 1] != '/') {
			 strncat(Dir, "/", 2);
		}

        strcat(Dir, FindFileData.cFileName);
        archivePath(Dir);
    }

    while (FindNextFileA(hFind, &FindFileData) != 0)
    {
        if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {   //找到文件
			archiveFile(FindFileData.cFileName, pFilePath);
        } else if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
            && strcmp(FindFileData.cFileName, ".") != 0
            && strcmp(FindFileData.cFileName, "..") != 0
			&& strcmp(FindFileData.cFileName, ".svn") != 0) { //找到目录
            char Dir[MAX_PATH + 1];
            strcpy(Dir, pFilePath);
			if (pFilePath[strlen(pFilePath) - 1] != '/') {
				 strncat(Dir, "/", 2);
			}
            strcat(Dir, FindFileData.cFileName);
            archivePath(Dir);
		}
    }

    dwError = GetLastError();
    FindClose(hFind);

    if (dwError != ERROR_NO_MORE_FILES) {
        printf ("FindNextFile error. Error is %u ", dwError);
        return;
    }
#endif
}
