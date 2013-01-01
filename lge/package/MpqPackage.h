#pragma once

#include "Package.h"
#include "StormLib.h"

class MpqPackage : public Package
{
public:
	MpqPackage();
	~MpqPackage();

public:
	virtual bool open(const char* fileName);
	virtual void close();

	virtual bool fileExist(const char* fileName);
	virtual unsigned char* getFileData(const char* fileName, unsigned long* dataSize);
    virtual unsigned char* getFileText(const char* fileName, unsigned long* dataSize);
private:
	HANDLE m_mpqHandle;
};