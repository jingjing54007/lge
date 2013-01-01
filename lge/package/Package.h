#pragma once

#ifndef NULL
#define NULL 0
#endif

class Package
{
public:
	Package();
	~Package();

public:
	virtual bool open(const char* fileName);
	virtual void close();

	virtual bool fileExist(const char* fileName);
	virtual unsigned char* getFileData(const char* fileName, unsigned long* dataSize);
	virtual unsigned char* getFileText(const char* fileName, unsigned long* dataSize);
};