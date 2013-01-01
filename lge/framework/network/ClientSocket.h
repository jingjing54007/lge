/********************************************************************

                Copyright (c) 2012 天盟数码研发中心                
                         All rights reserved           
       
    创建日期：  2012年7月17日 9时59分
    文件名称：  ClientSocket.h
    说    明：  网络连接
    
    当前版本：  1.00
    作    者：  qiukun
    概    述：  创建

********************************************************************/
#ifndef ClientSocket_H
#define ClientSocket_H
#include "XNet.h"

#define USE_NEW_SOCKET 1

class CGameSocket;
class ISocketConnectEvent;

class CClientSocket : public INetCallback
{
	enum
	{
		kDataStreamBufferLen = 65536,
	};
public:
	CClientSocket(void);
	~CClientSocket(void);
	//连接成功
	virtual void connectionSucceed();
	//连接失败
	virtual void connectionFailed();
	//收到信息
	virtual void reciveMessage(const char* lpMsgBuf, int nLen);
	//请求失败
	virtual void requestFailed(ERROR_RES errorRes);
	//远程连接断开
	virtual void onConnectionAbort();

	//连接
	bool Connect(std::string szServerIP,  int wPort);
	//发送函数
	bool SendData(char* buf, int nLen, bool bPushQueue = false);
	//关闭连接
	void CloseSocket(bool bNotify = false);
	void AddEventListener(ISocketConnectEvent* value);
	bool getIsConnect();

private:
	void pushStream2Buffer(const char* pStream, int nLen);
	void popStreamFromBuffer(int nLen);
protected:
	ISocketConnectEvent* m_iSocketConnectEvent;
	CXNet	m_Socket;//连接句柄

	//数据流缓冲
	char	m_dataStreamBuffer[kDataStreamBufferLen];
	//当前数据流长度
	int		m_nCurDataStreamLen;


public:
	void processNetMsg();
private:
	CGameSocket* m_pSocket;
	bool			m_bReady;
	int				m_nConnectServerFlag;
};
#endif
