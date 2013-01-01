#include "stdafx.h"
#include "SocketManager.h"
#include "MessageDefine/ClientMsgDefine.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "iOSUtil.h"
#endif

 DECLARE_SINGLETON_MEMBER(CSocketManager)

CSocketManager::CSocketManager(void)
{
}

CSocketManager::~CSocketManager(void)
{
}

CSocketManager* CSocketManager::instance()
{
	static CSocketManager _instance;

	return &_instance;
}

void CSocketManager::processNetMsg()
{
	m_clientSocket.processNetMsg();
}

void  CSocketManager::addEventListener(ISocketConnectEvent* value)
{
	m_clientSocket.AddEventListener(value);
}


void CSocketManager::connect(std::string szServerIP, int wPort)
{

 //   CCLOG("===============================   SocketManager::Connect[%s:%d]", szServerIP.c_str(), wPort);
	m_clientSocket.Connect(szServerIP, wPort);
}

void CSocketManager::reConnect(std::string szServerIP, int wPort)
{
    CCLOG("===============================   SocketManager::ReConnect[%s:%d]", szServerIP.c_str(), wPort);
	m_clientSocket.CloseSocket(true);
	connect(szServerIP, wPort);
}

void CSocketManager::sendData(MsgHead* pMsgHead, bool bPushQueue /*= false*/)
{
//	CCLOG("================>>>>>>>>>>   SocketManager::SendData[MsgId:%d  MsgSize:%d]", pMsgHead->usType, pMsgHead->usSize);
	m_clientSocket.SendData((char*)pMsgHead, pMsgHead->usSize, bPushQueue);
}

void CSocketManager::closeSocket(bool bNotify)
{
	m_clientSocket.CloseSocket(bNotify);
}


bool CSocketManager::getIsConnect()
{
	return m_clientSocket.getIsConnect();
}

bool CSocketManager::checkNetwork()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return iOSUtil::checkNetwork();
#else
	return true;
#endif
}