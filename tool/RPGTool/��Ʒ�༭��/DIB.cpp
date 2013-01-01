// DIB.cpp: implementation of the DIB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyEditor.h"
#include "DIB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 DIB::DIB()
{
	m_pBMI=NULL;
	m_pDIBData=NULL;

}

DIB::~DIB()
{
	//释放内存
	if(m_pBMI!=NULL)
		delete m_pBMI;
	if(m_pDIBData!=NULL)
		delete m_pDIBData;
}

BOOL  DIB::LoadFromFile(LPCTSTR lpszFileName) 
{
	CFile file;
	BITMAPINFO* pBMI=NULL;
	BYTE* pDIBData=NULL;
	// 打开指定文件
	if(!file.Open(lpszFileName,CFile::modeRead|CFile::typeBinary))
	{
		AfxMessageBox("打不开文件");
		return FALSE;
	}
	BITMAPFILEHEADER bfh;

	if(file.Read(&bfh,sizeof(bfh))!=sizeof(bfh))
	{
		AfxMessageBox("读文件出错!");
		return FALSE;
	}
	//若不是位图案,不予处理
	if(bfh.bfType!=0x4d42)
	{
		AfxMessageBox("不是BMP文件");
		return FALSE;
	}
	//读入位图信息头
	BITMAPINFOHEADER bih;
	if(file.Read(&bih,sizeof(bih))!=sizeof(bih))
	{
		AfxMessageBox("读文件出错!");
		return FALSE;
	}
	//若不是24位真彩色位图,则不予处理
	if(bih.biBitCount!=24)
	{
		AfxMessageBox("不是24位真彩色位图!");
		return FALSE;
	}
	// 为BITMAPINFO结构指针申请内存因为真彩色位图没有颜色表,所以其
    // BITMAPINFO=BITMAPINFOHEADER
	pBMI=(BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
    if(!pBMI)
	{
		AfxMessageBox("分配内存出错!");
		return FALSE;
	}
	//由于前面已将BITMAPINFOHEADER读入内存,所以这里只需要拷贝一下
	memcpy(pBMI,&bih,sizeof(BITMAPINFOHEADER));
	//为BMP图像数据指针申请内存;
	DWORD dataBytes=bfh.bfSize-bfh.bfOffBits;//图像数据的字节数;
	pDIBData=(BYTE*)new char[dataBytes];
	if(!pDIBData)
	{
		AfxMessageBox("分配内存出错!");
		delete pBMI;
        return FALSE;
	}
	//读入位图的图像数据
	if(file.Read(pDIBData,dataBytes)!=dataBytes)
    {
		AfxMessageBox("读文件出错!");
		delete pBMI;
		delete pDIBData;
		return FALSE;
	}
	file.Close();
	if(m_pBMI!=NULL)
	delete pBMI;
    m_pBMI=pBMI;
	if(m_pDIBData!=NULL)
		delete m_pDIBData;
	m_pDIBData=pDIBData;
	return TRUE;


}

void DIB::ShowDIB(CDC* pDC,int nLeft,int nTop,int nWidth,int nHeight)
{
	pDC->SetStretchBltMode(COLORONCOLOR); //设置伸缩拷贝模式
	StretchDIBits(pDC->GetSafeHdc(),      //DC句柄
		                  nLeft,          //目标矩形左上角的X坐标
						  nTop,           //目标矩形左上角的Y坐标
						  nWidth,         //目标矩形的宽度
						  nHeight,        //目标矩形的高度
						  0,              //源矩形的左上积角的X坐标
						  0,              //源矩形的左上积角的Y坐标
						  GetDIBWidth(),  //源矩形的宽度
                          GetDIBHeight(), //源矩形的高度
						 m_pDIBData,      //位图图像数据的地址
						  m_pBMI,         //位图信息结构地址
						  DIB_RGB_COLORS, //标志选项
						  SRCCOPY);       //光栅操作码
}
