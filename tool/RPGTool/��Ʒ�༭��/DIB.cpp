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
	//�ͷ��ڴ�
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
	// ��ָ���ļ�
	if(!file.Open(lpszFileName,CFile::modeRead|CFile::typeBinary))
	{
		AfxMessageBox("�򲻿��ļ�");
		return FALSE;
	}
	BITMAPFILEHEADER bfh;

	if(file.Read(&bfh,sizeof(bfh))!=sizeof(bfh))
	{
		AfxMessageBox("���ļ�����!");
		return FALSE;
	}
	//������λͼ��,���账��
	if(bfh.bfType!=0x4d42)
	{
		AfxMessageBox("����BMP�ļ�");
		return FALSE;
	}
	//����λͼ��Ϣͷ
	BITMAPINFOHEADER bih;
	if(file.Read(&bih,sizeof(bih))!=sizeof(bih))
	{
		AfxMessageBox("���ļ�����!");
		return FALSE;
	}
	//������24λ���ɫλͼ,���账��
	if(bih.biBitCount!=24)
	{
		AfxMessageBox("����24λ���ɫλͼ!");
		return FALSE;
	}
	// ΪBITMAPINFO�ṹָ�������ڴ���Ϊ���ɫλͼû����ɫ��,������
    // BITMAPINFO=BITMAPINFOHEADER
	pBMI=(BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
    if(!pBMI)
	{
		AfxMessageBox("�����ڴ����!");
		return FALSE;
	}
	//����ǰ���ѽ�BITMAPINFOHEADER�����ڴ�,��������ֻ��Ҫ����һ��
	memcpy(pBMI,&bih,sizeof(BITMAPINFOHEADER));
	//ΪBMPͼ������ָ�������ڴ�;
	DWORD dataBytes=bfh.bfSize-bfh.bfOffBits;//ͼ�����ݵ��ֽ���;
	pDIBData=(BYTE*)new char[dataBytes];
	if(!pDIBData)
	{
		AfxMessageBox("�����ڴ����!");
		delete pBMI;
        return FALSE;
	}
	//����λͼ��ͼ������
	if(file.Read(pDIBData,dataBytes)!=dataBytes)
    {
		AfxMessageBox("���ļ�����!");
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
	pDC->SetStretchBltMode(COLORONCOLOR); //������������ģʽ
	StretchDIBits(pDC->GetSafeHdc(),      //DC���
		                  nLeft,          //Ŀ��������Ͻǵ�X����
						  nTop,           //Ŀ��������Ͻǵ�Y����
						  nWidth,         //Ŀ����εĿ��
						  nHeight,        //Ŀ����εĸ߶�
						  0,              //Դ���ε����ϻ��ǵ�X����
						  0,              //Դ���ε����ϻ��ǵ�Y����
						  GetDIBWidth(),  //Դ���εĿ��
                          GetDIBHeight(), //Դ���εĸ߶�
						 m_pDIBData,      //λͼͼ�����ݵĵ�ַ
						  m_pBMI,         //λͼ��Ϣ�ṹ��ַ
						  DIB_RGB_COLORS, //��־ѡ��
						  SRCCOPY);       //��դ������
}
