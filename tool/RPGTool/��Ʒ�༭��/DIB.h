// DIB.h: interface for the DIB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__47BF00E4_B78E_4F0D_8772_9B58DC28D395__INCLUDED_)
#define AFX_DIB_H__47BF00E4_B78E_4F0D_8772_9B58DC28D395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DIB :public CObject 
{
public:
	DIB();
	virtual ~DIB();
	BITMAPINFO* m_pBMI;
	BYTE*       m_pDIBData;
	virtual BOOL LoadFromFile(LPCTSTR lpszFileName);
	virtual void ShowDIB(CDC* pDC,int nLeft,int nTop,int nWildth,int nHeight);
	int GetDIBWidth()
	{
		return m_pBMI->bmiHeader.biWidth;
	}
	int GetDIBHeight()
	{
		return m_pBMI->bmiHeader.biHeight;
	}



};

#endif // !defined(AFX_DIB_H__47BF00E4_B78E_4F0D_8772_9B58DC28D395__INCLUDED_)
