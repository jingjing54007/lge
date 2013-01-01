#if !defined(__Bmp_H__)
#define __Bmp_H__

#if _MSC_VER>=1000
#pragma once
#endif //_MSC_VER>=1000

//Bmp.h:header file

////////////////////////////////////////
//CBmp class


class CBmp:public CObject
{
	public:
		CBmp();
		virtual ~CBmp();
		
		BITMAPINFO *m_pBMI;
		BYTE *m_pBmpData;
		
		
		virtual BOOL LoadFromFile(LPCTSTR lpszFileName);   //读入位图文件
		virtual void ShowBmp(CDC *pDC,int nLeft,int nTop,int nWidth,int nHeight,int tp,DWORD mode);
		virtual void DrawInDC(CDC *tempDC,int x,int y,int tp);
		int GetBmpWidth()        //得到位图的宽度
        {
			return m_pBMI->bmiHeader.biWidth;
		}
		int GetBmpHeight()       //得到位图的高度
		{
			return m_pBMI->bmiHeader.biHeight;
		}
};

///////////////////////////////////////////
#endif //!defined(__CBmp_H__)