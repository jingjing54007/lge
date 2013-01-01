/********************************************************************

                Copyright (c) 2012 天盟数码研发中心                
                         All rights reserved           
       
    创建日期：  2012年7月17日 9时59分
    文件名称：  ISocketConnectEvent.h
    说    明：  基于主框架信息的观察者接口
    
    当前版本：  1.00
    作    者：  qiukun
    概    述：  创建

********************************************************************/
#ifndef ISocketConnectEvent_H
#define ISocketConnectEvent_H


class ISocketConnectEvent
{
public:
	// 关闭连接回调
	virtual void closeSocket() = 0;	
	// 连接成功回调
	virtual void onHandlerConnected() = 0;	
	//远程断开连接
	virtual void onConnectionAbort() = 0;
	//连接失败
	virtual void onConnectFaild() = 0;
};


#endif