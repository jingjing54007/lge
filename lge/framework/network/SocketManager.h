/********************************************************************

                Copyright (c) 2012 天盟数码研发中心                
                         All rights reserved           
       
    创建日期：  2012年7月17日 9时59分
    文件名称：  ISocketConnectEvent.h
    说    明：  网络连接管理类
    
    当前版本：  1.00
    作    者：  qiukun
    概    述：  创建

********************************************************************/
#ifndef SocketManager_H
#define SocketManager_H
#include "ClientSocket.h"
#include "Singleton.h"
struct MsgHead;

class CSocketManager// : public Singleton<SocketManager>
{
	_NO_COPY_CLASS_(CSocketManager);
private:
	CSocketManager(void);
	~CSocketManager(void);

public:
	static CSocketManager* instance();

	//監測網絡是否正常
	bool checkNetwork();

	void addEventListener(ISocketConnectEvent* value);

	void connect(std::string szServerIP, int wPort);

	void reConnect(std::string szServerIP, int wPort);

	void sendData(MsgHead* pMsgHead, bool bPushQueue = false);

	void closeSocket(bool bNotify = false);

	bool getIsConnect();

	void processNetMsg();
private:
	//通讯
	CClientSocket m_clientSocket;
};
#endif

