#include "stdafx.h"
#include "ClientSocket.h"
#include "ISocketConnectEvent.h"
#include "MessageDispatchPolicy/MessageSubject.h"
#include "Game/login/LoginManager.h"
#include "Socket.h"
//#ifndef _UNUSE_MEMPOOL_
#include "MemManager.h"
//#endif

CClientSocket::CClientSocket(void)
{
	m_iSocketConnectEvent = NULL;
	memset(m_dataStreamBuffer, 0, kDataStreamBufferLen);
	m_nCurDataStreamLen = 0;


	m_bReady		= false;
	m_pSocket		= NULL;
	m_nConnectServerFlag = 0;
}


CClientSocket::~CClientSocket(void)
{
	if(NULL != m_pSocket)
	{
		CloseSocket(false);
	}
}

//连接
bool CClientSocket::Connect(std::string szServerIP,  int wPort)
{
#if USE_NEW_SOCKET
	if(szServerIP.empty() || wPort<0) {
		return false;
	}

	m_pSocket = new CGameSocket;
	if (!m_pSocket) {
		return false;
	}

	if(m_pSocket->Create(szServerIP.c_str(), wPort, 30)) {
		this->m_bReady	=true;
		connectionSucceed();
		return true;
	}
	else
	{
		this->m_bReady	=false;
		connectionFailed();
		return false;
	}
#else
	//char szTmp[5] = {1,2,3,4,5};
	//pushStream2Buffer(szTmp, 5);
	//pushStream2Buffer(szTmp, 5);
	//popStreamFromBuffer(3);
	//popStreamFromBuffer(3);
	//popStreamFromBuffer(3);
	//popStreamFromBuffer(1);
	m_Socket.setCallBack(this);
	bool bFlag = m_Socket.connect(szServerIP.c_str(), wPort);
	return bFlag;
#endif
	return false;
}
//发送函数
bool CClientSocket::SendData(char* buf, int nLen, bool bPushQueue /*= false*/)
{
#if USE_NEW_SOCKET
	if(!m_bReady || !buf) {
		return false;
	}

	bool bSucSend;
	try {
		//bSucSend	=::ClientSocketSendMsg(pbufMsg, dwSize);
		if (m_pSocket) {
			bSucSend = m_pSocket->SendMsg(buf, nLen);
		}
	}
	catch(...)
	{
		LogMsg("catch error in send msg.");		
	}
#else
	m_Socket.sendMessage(buf, nLen, bPushQueue);
#endif
	return true;
}
//关闭连接
void CClientSocket::CloseSocket(bool bNotify)
{
	if(NULL != m_iSocketConnectEvent && bNotify)
	{
		m_iSocketConnectEvent->closeSocket();
	}

#if USE_NEW_SOCKET
	if (m_bReady && m_pSocket)
	{
		// ::ClientSocketDestroy();
		m_pSocket->Flush();
		m_pSocket->Destroy();
		m_bReady	=false;
	}

	delete m_pSocket;
	m_pSocket = NULL;
#else
	m_Socket.close();
#endif
}

void CClientSocket::AddEventListener(ISocketConnectEvent* value)
{
	m_iSocketConnectEvent = value;
}


void CClientSocket::pushStream2Buffer(const char* pStream, int nLen)
{
	if(m_nCurDataStreamLen + nLen >= kDataStreamBufferLen)
	{
//		CCLOG("<<<<<<<<<<<<<<<< ERROR: data stream buffer is full! >>>>>>>>>>>>>>>>>>");
		return;
	}

	memcpy(m_dataStreamBuffer+m_nCurDataStreamLen, pStream, nLen);
	m_nCurDataStreamLen += nLen;
}

void CClientSocket::popStreamFromBuffer(int nLen)
{
	if(m_nCurDataStreamLen - nLen <= 0)
	{
		m_nCurDataStreamLen = 0;
		memset(m_dataStreamBuffer, 0, kDataStreamBufferLen);
        
 //       CCLOG(">>>>>>>>>>>>>>>>>>>>>>>  ClientSocket::popStreamFromBuffer popBufLen:%d Message Buffer stream is null!", nLen);
        
		return;
	}

	int nResidueLen = m_nCurDataStreamLen - nLen;

 //   CCLOG(">>>>>>>>>>>>>>>>>>>>>>>  ClientSocket::popStreamFromBuffer curBufLen:%d popBufLen:%d residueBufLen:%d ",
//          m_nCurDataStreamLen, nLen, nResidueLen);
    
//#ifndef _UNUSE_MEMPOOL_
//	char *pTmpBuf = static_cast<char*>(CMemPool::getInstance().GetMemory(nResidueLen));
//#else
	char *pTmpBuf = new char[nResidueLen];
//#endif

	memset(pTmpBuf, 0, nResidueLen);
	memcpy(pTmpBuf, m_dataStreamBuffer + nLen, nResidueLen);
	memset(m_dataStreamBuffer, 0, kDataStreamBufferLen);
	memcpy(m_dataStreamBuffer, pTmpBuf, nResidueLen);
	m_nCurDataStreamLen = nResidueLen;

//	CMemPool::getInstance().FreeMemory(pTmpBuf, nResidueLen);
	if(NULL != pTmpBuf)
	{
		delete[] pTmpBuf;
		pTmpBuf = NULL;
	}
	//if(m_nCurDataStreamLen - nLen >= 0)
	//	m_nCurDataStreamLen -= nLen;
	//else
	//	m_nCurDataStreamLen = 0;
}

void CClientSocket::processNetMsg()
{
#if USE_NEW_SOCKET
	if (!m_pSocket) {
		return;
	}

	if (!m_pSocket->Check()) {
		m_pSocket = NULL;
		// 掉线了
		onConnectionAbort();
		return;
	}

	// 发送数据（向服务器发送消息）
	m_pSocket->Flush();

	// 接收数据（取得缓冲区中的所有消息，直到缓冲区为空）
	while (true)
	{
		char buffer[_MAX_MSGSIZE] = { 0 };
		int nSize = sizeof(buffer);
		char* pbufMsg = buffer;
		if(m_pSocket == NULL)
		{
			break;
		}
		if (!m_pSocket->ReceiveMsg(pbufMsg, nSize)) {
			break;
		}
		
		while (true)
		{
			MsgHead* pReceiveMsg = (MsgHead*)(pbufMsg);
			uint16	dwCurMsgSize = pReceiveMsg->usSize;
//			CCLOG("msgsize: %d", dwCurMsgSize);

			if((int)dwCurMsgSize > nSize || dwCurMsgSize <= 0) {	// broken msg
				break;
			}

			CMessageSubject::instance().OnMessage((const char*)pReceiveMsg, pReceiveMsg->usSize);

			pbufMsg	+= dwCurMsgSize;
			nSize	-= dwCurMsgSize;
			if(nSize <= 0) {
				break;
			}
		}
	}
#else
//	while (true) {
		m_Socket.processNetMsg();

		if(m_nCurDataStreamLen <= 0)
			return;


		MsgHead* pReceiveMsg = (MsgHead*)(m_dataStreamBuffer);

		if(m_nCurDataStreamLen < pReceiveMsg->usSize)
			return;

		CMessageSubject::instance().OnMessage((const char*)pReceiveMsg, pReceiveMsg->usSize);
		popStreamFromBuffer(pReceiveMsg->usSize);
//	}
#endif
}

//连接成功
void CClientSocket::connectionSucceed()
{
	if(NULL != m_iSocketConnectEvent)
	{
		m_iSocketConnectEvent->onHandlerConnected();
	}

}
//连接失败
 void CClientSocket::connectionFailed()
 {
	// CCMessageBox("连接服务器失败!", "Error!");
	/*CLoginModule::getInstance().connectFaild();*/
	 //LoginManager::getInstance().onConnectFaild();
      m_bReady = false;
	 if(NULL != m_iSocketConnectEvent)
	 {
		 m_iSocketConnectEvent->onConnectFaild();
	 }
 }
//收到信息
 void CClientSocket::reciveMessage(const char* lpMsgBuf, int nLen)
 {
	 //MessageSubject::instance().OnMessage(lpMsgBuf, nLen);
	 // CC_SAFE_DELETE(buf);
     
     CCLOG("ClientSocket::reciveMessage dataStramSize:%d", nLen);
     
	 pushStream2Buffer(lpMsgBuf, nLen);
 }
 //请求失败
 void CClientSocket::requestFailed(ERROR_RES errorRes)
 {

 }
//远程连接断开
 void CClientSocket::onConnectionAbort()
 {
	 std::string strMessageInfo = "与服务器连接中断!";
	 //CCMessageBox("与服务器连接中断!", "ERROR!!");
	 m_bReady = false;
	 if(NULL != m_iSocketConnectEvent)
	 {
		 m_iSocketConnectEvent->onConnectionAbort();
	 }
 }


 bool CClientSocket::getIsConnect()
 {
	 return m_bReady;
 }