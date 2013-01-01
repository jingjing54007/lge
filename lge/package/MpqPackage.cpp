#include "MpqPackage.h"
#include <string>
#include <algorithm>
#include "PackageUtil.h"

MpqPackage::MpqPackage()
{
	m_mpqHandle = NULL;
}

MpqPackage::~MpqPackage()
{
}

bool MpqPackage::open(const char* fileName)
{
	if (!fileName || fileName[0] == 0) {
		return false;
	}

	// 已打开
	if (m_mpqHandle) {
		return true;
	}

#ifdef WIN32
	wchar_t szFileName[256] = {0};
	MultiByteToWideChar (CP_ACP, 0, fileName, strlen(fileName), szFileName, 255);
    //打开一个mpq包
	if (!SFileOpenArchive(szFileName,0,0,&m_mpqHandle)) {
		m_mpqHandle = NULL;
		return false;
	}
#else
    //打开一个mpq包
	if (!SFileOpenArchive(fileName,0,0,&m_mpqHandle)) {
		m_mpqHandle = NULL;
		return false;
	}
#endif

	return true;
}

void MpqPackage::close()
{
	if (m_mpqHandle) {
		 SFileCloseArchive(m_mpqHandle);
		 m_mpqHandle = NULL;
	}
}

bool MpqPackage::fileExist(const char* fileName)
{
	if (!m_mpqHandle) {
		return false;
	}

	return SFileHasFile(m_mpqHandle, fileName);
}

unsigned char* MpqPackage::getFileData(const char* fileName, unsigned long* dataSize)
{
	if (!fileName || fileName[0] == 0) {
		return NULL;
	}

 	std::string tempStr = fileName;
 	std::replace(tempStr.begin(), tempStr.end(), '\\', '/');

	//打开MPQ中指定的文件名的文件(第3个参数是从指定从MPQ文件中找)  
	HANDLE hFile;  
	if(!SFileOpenFileEx(m_mpqHandle, fileName, SFILE_OPEN_FROM_MPQ, &hFile)) {
		//如果打开失败则输出到LOG，且返回个空指针
        PackageUtil::logMsg("Unable to open file: %s  in package:%s", fileName, "");
		return NULL;
	}  

	//得到文件解压缩之后的SIZE
	DWORD sizeHigh = 0;
	DWORD size = SFileGetFileSize(hFile, &sizeHigh);
	if (SFILE_INVALID_SIZE ==size) {
		PackageUtil::logMsg("File size error: %s  in package:%s", fileName, "");
		SFileCloseFile(hFile);  
		return NULL;  
	}  

	unsigned char* outputData = new unsigned char[size];
	
	DWORD readCount = 0;
	LPOVERLAPPED tempValue = NULL;
	if(!SFileReadFile(hFile, outputData, static_cast<DWORD>(size), &readCount, tempValue)) {
		return NULL;
	}

	if (dataSize) {
		*dataSize = size;
	}

	SFileCloseFile(hFile);

	return outputData;
}

unsigned char* MpqPackage::getFileText(const char* fileName, unsigned long* dataSize)
{
	if (!fileName || fileName[0] == 0) {
		return NULL;
	}
    
    // 	std::string tempStr = fileName;
    // 	std::replace(tempStr.begin(), tempStr.end(), '\\', '/');
    
	//打开MPQ中指定的文件名的文件(第3个参数是从指定从MPQ文件中找)
	HANDLE hFile;
	if(!SFileOpenFileEx(m_mpqHandle, fileName, SFILE_OPEN_FROM_MPQ, &hFile)) {
		//如果打开失败则输出到LOG，且返回个空指针
        PackageUtil::logMsg("Unable to open file: %s  in package:%s", fileName, "");
		return NULL;
	}
    
	//得到文件解压缩之后的SIZE
	DWORD sizeHigh = 0;
	DWORD size = SFileGetFileSize(hFile, &sizeHigh);
	if (SFILE_INVALID_SIZE ==size) {
		PackageUtil::logMsg("File size error: %s  in package:%s", fileName, "");
		SFileCloseFile(hFile);
		return NULL;
	}
    
	unsigned char* outputData = new unsigned char[size + 1];
	
	DWORD readCount = 0;
	LPOVERLAPPED tempValue = NULL;
	if(!SFileReadFile(hFile, outputData, static_cast<DWORD>(size), &readCount, tempValue)) {
        delete outputData;
        outputData = NULL;
		return NULL;
	}
    
    outputData[size] = 0;
    
	if (dataSize) {
		*dataSize = size + 1;
	}
    
	SFileCloseFile(hFile);
    
	return outputData;
}


