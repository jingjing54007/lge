
#include "Package.h"

Package::Package()
{

}

Package::~Package()
{
}

bool Package::open(const char* fileName)
{
	return false;
}

void Package::close()
{

}

bool Package::fileExist(const char* fileName)
{
	return false;
}


unsigned char* Package::getFileData(const char* fileName, unsigned long* dataSize)
{
	return NULL;
}


unsigned char* Package::getFileText(const char* fileName, unsigned long* dataSize)
{
    return NULL;
}
