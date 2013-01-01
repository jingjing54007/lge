#pragma once

#include "rapidxml/rapidxml.hpp"

class XmlUtil
{
public:

	// 从一个root节点查找key节点的数据节点，plist格式
	static rapidxml::xml_node<>* getXmlNode(rapidxml::xml_node<>* root, const char* key);

	// 同上，二级查找
	static rapidxml::xml_node<>* getXmlNode(rapidxml::xml_node<>* root, const char* key, const char* key2);

	// 获取一个root节点中key节点的数据节点的值，plist格式
	static const char* getXmlNodeValue(rapidxml::xml_node<>* root, const char* key);
	static int getXmlNodeIntValue(rapidxml::xml_node<>* root, const char* key);
	static float getXmlNodeFloatValue(rapidxml::xml_node<>* root, const char* key);
	static bool getXmlNodeBoolValue(rapidxml::xml_node<>* root, const char* key);

	// 同上，二级查找
	static const char* getXmlNodeValue(rapidxml::xml_node<>* root, const char* key, const char* key2);
};