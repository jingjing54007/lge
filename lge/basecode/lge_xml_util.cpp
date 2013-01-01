#include "XmlUtil.h"
#include "PlatformDefine.h"

rapidxml::xml_node<>* XmlUtil::getXmlNode(rapidxml::xml_node<>* root, const char* key)
{
	if (!root || !key) {
		return NULL;
	}

	rapidxml::xml_node<>* nodeToFind = root->first_node("key");
	while (nodeToFind != NULL) {
		const char* keyValue = nodeToFind->value();
		if (stricmp(keyValue, key) == 0) {
			rapidxml::xml_node<>* dictNode = nodeToFind->next_sibling();
			if (dictNode) {
				return dictNode;
			}
		}

		nodeToFind = nodeToFind->next_sibling("key");
	}

	return NULL;
}

rapidxml::xml_node<>* XmlUtil::getXmlNode(rapidxml::xml_node<>* root, const char* key, const char* key2)
{
	if (!root || !key || !key2) {
		return NULL;
	}

	rapidxml::xml_node<>* nodeToFind = getXmlNode(root, key);
	return getXmlNode(nodeToFind, key2);
}

const char* XmlUtil::getXmlNodeValue(rapidxml::xml_node<>* root, const char* key)
{
	rapidxml::xml_node<>* keyNode = getXmlNode(root, key);
	if (!keyNode) {
		return NULL;
	}

	return keyNode->value();
}

const char* XmlUtil::getXmlNodeValue(rapidxml::xml_node<>* root, const char* key, const char* key2)
{
	rapidxml::xml_node<>* keyNode = getXmlNode(root, key, key2);
	if (!keyNode) {
		return NULL;
	}

	return keyNode->value();
}


int XmlUtil::getXmlNodeIntValue(rapidxml::xml_node<>* root, const char* key)
{
	const char* value = getXmlNodeValue(root, key);
	if (value) {
		return atoi(value);
	}

	return 0;
}

float XmlUtil::getXmlNodeFloatValue(rapidxml::xml_node<>* root, const char* key)
{
	const char* value = getXmlNodeValue(root, key);
	if (value) {
		return (float)atof(value);
	}

	return 0;
}

bool XmlUtil::getXmlNodeBoolValue(rapidxml::xml_node<>* root, const char* key)
{
	rapidxml::xml_node<>* keyNode = getXmlNode(root, key);
	if (!keyNode) {
		return false;
	}

	const char* name = keyNode->name();
	if (!name) {
		return false;
	}

	return stricmp(name, "true") == 0;
}