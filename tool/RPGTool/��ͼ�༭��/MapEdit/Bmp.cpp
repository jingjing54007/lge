// Bmp.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "Bmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmp
CBmp::CBmp()
{
	m_pBMI=NULL;
	m_pBmpData=NULL;
}

CBmp::~CBmp()
{
	if(m_pBMI!=NULL)
		delete m_pBMI;
	if(m_pBmpData!=NULL)
		delete m_pBmpData;
}

BOOL CBmp::LoadFromFile(LPCTSTR lpszFileName)    
{
	CFile file;

	BITMAPINFO *pBMI=NULL;
	BYTE *pBmpData=NULL;
	if(!file.Open(lpszFileName,CFile::modeRead|CFile::typeBinary))
	{
		AfxMessageBox("Open file Failed!");
		return false;
	}

	BITMAPFILEHEADER  bfh;
	if(file.Read(&bfh,sizeof(bfh))!=sizeof(bfh))
	{
		AfxMessageBox("Read file ERROR!");
		return false;
	}
	if(bfh.bfType!=0x4d42)
	{
		AfxMessageBox("File NOT a bmpfile!");
		return false;

	}
	
	BITMAPINFOHEADER  bih;
	if(file.Read(&bih,sizeof(bih))!=sizeof(bih))
	{
		AfxMessageBox("Read file ERROR!");
		return false;
	}
	if(bih.biBitCount!=24)
	{
        AfxMessageBox("NOT a 24 Bit picture!");
		return false;
	}
	pBMI=(BITMAPINFO*) new char[sizeof(BITMAPINFOHEADER)];
	if(!pBMI)
	{
		AfxMessageBox("Memery ERROR!");
		return false;
	}
	memcpy(pBMI,&bih,sizeof(BITMAPINFOHEADER));
	DWORD dataBytes=bfh.bfSize-bfh.bfOffBits;
	pBmpData=(BYTE *)new char[dataBytes];
	if(!pBmpData)
	{
		AfxMessageBox("Memery ERROR!");
		delete pBMI;
		return false;
	}
	if(file.Read(pBmpData,dataBytes)!=dataBytes)
	{
		AfxMessageBox("Read file ERROR!");
		delete pBMI;
		delete pBmpData;
		return false;
	}
	file.Close();

	if(m_pBMI!=NULL)
		delete m_pBMI;
	m_pBMI=pBMI;

	if(m_pBmpData!=NULL)
		delete m_pBmpData;
	m_pBmpData=pBmpData;

	return true;
}
/*CSize GetBmpSize()
{

}*/

void CBmp::ShowBmp(CDC *pDC,int nLeft,int nTop,int nWidth,int nHeight,int tp,DWORD mode)
{
	if (tp=0)
		pDC->SetStretchBltMode(COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(),           //DC句柄
		                    nLeft,            //目标矩形左上角的 X坐标
							nTop,             //目标矩形左上角的 Y坐标 
							nWidth,    //目标矩形宽度
							nHeight,   //目标矩形高度 
							0,                 //源矩形左上角的 X坐标
							0,                 //源矩形左上角的 Y坐标
							GetBmpWidth(),      //源矩形的宽度
							GetBmpHeight(),    //源矩形的高度
							m_pBmpData,          //位图图像数据的地址
							m_pBMI,             //位图信息结构的地址
							DIB_RGB_COLORS,      //标志选项
							mode);            //光栅操作码  SRCINVERT  (XOR) 
}
////////////////////////////////////////////

void CBmp::DrawInDC(CDC *tempDC,int x,int y,int tp)
{
	
	if(m_pBMI==NULL)
		return;
	DWORD biw;
	int i,j,w,h,blank,r,g,b;
	byte color[3],*data;
	biw=m_pBMI->bmiHeader.biWidth;
	w=GetBmpWidth()+x;
	h=GetBmpHeight()+y;
	blank=(GetBmpWidth()*3%4);
	data=m_pBmpData+((GetBmpHeight()-1)*((GetBmpWidth()+blank)*3))+6;

	r=*data++;
	g=*data++;
	b=*data++;
/*	CString ss;
	ss.Format("%d,%d,%d",r,g,b);
	AfxMessageBox(ss);
	*/
	
	data=m_pBmpData;
	for(i=h;i>y;i--)
	{
		for(j=x;j<w;j++)
		{
			color[0]=*data++;
			color[1]=*data++;
			color[2]=*data++;
				
			
			if(tp==0)
				tempDC->SetPixel(j,i,RGB(color[2],color[1],color[0]));
			else
			{
				if(!(int(color[2])<r+2 && int(color[2])>r-2) && !(int(color[1])<g+2 && int(color[1])>g-2) && !(int(color[0])<b+2 && int(color[0])>b-2))
					tempDC->SetPixel(j,i,RGB(color[2],color[1],color[0]));

			}
		}
		blank=(GetBmpWidth()*3%4);
		if(blank!=0) blank=4-blank;
		data+=blank;
	}
}
