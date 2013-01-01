#include "PackageTest.h"

#if kEnableTest
#include "PackageManager.h"
#include <cassert>
#ifdef WIN32
#include <windows.h>
#endif

#include "rapidxml.hpp"

void printXml(const char* pBuffer)
{
#ifdef WIN32
	OutputDebugStringA(pBuffer);
#else
	printf(pBuffer);
#endif
}


void testParseXml(const char* fileName)
{
	int dataSize = 0;
	unsigned char* pBuffer = PackageManager::getSingleton().getFileData(fileName, &dataSize);
	char* xmldata = new char[dataSize + 1];
	xmldata[dataSize] = 0;
	memcpy(xmldata, pBuffer, dataSize);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmldata);

	printXml(xmldata);
}

void doTestSpeed()
{
}

void doTest()
{
	assert(PackageManager::getSingleton().openPackage("e:/MPQs/wing.mpq"));
	
	int dataSize = 0;
	unsigned char* pBuffer = PackageManager::getSingleton().getFileData("version.xml", &dataSize);
	assert(pBuffer != NULL);
	assert(dataSize != 0);

	testParseXml("version.xml");
	testParseXml("assets/script/npc/NPCs.xml");
	testParseXml("assets/script/mission/NPCs.xml");
	testParseXml("assets/script/mission/BasicTask.xml");
	testParseXml("assets/script/mission/Dialogue.xml");
	testParseXml("assets/script/mission/Search.xml");
	testParseXml("assets/script/mission/TaskAction.xml");
}


#endif