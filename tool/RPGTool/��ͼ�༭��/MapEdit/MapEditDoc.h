// MapEditDoc.h : interface of the CMapEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPEDITDOC_H__DDF278C6_6486_4B5C_991A_3DED14B9F440__INCLUDED_)
#define AFX_MAPEDITDOC_H__DDF278C6_6486_4B5C_991A_3DED14B9F440__INCLUDED_

#if _MSC_VER > 1000
#pragma once

#endif // _MSC_VER > 1000

#include "Bmp.h"
#include "scene.h"
#include "Thing.h"
#include "SYSDLG.h"
#include "piclib.h"

extern float m_zoomin,m_zoomout;
extern int m_save;
class CMapEditDoc : public CDocument
{
protected: // create from serialization only
	CMapEditDoc();
	DECLARE_DYNCREATE(CMapEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapEditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SaveScene(char path[256]);
	void InitData();
	void TransDCtoDC(CDC* pDestDC, int dX, int dY, CDC* pSrcDC, int Width, int Height, int tp);
	void TransDraw(CDC* tempDC,int left,int top,byte bit[],int wide,int height,COLORREF cr);
	void DrawSceneInDC(CDC* tempDC);
	HBITMAP SampleHb;
	BITMAP  SampleBm;

	HBITMAP modelbh;
	BITMAP modelbm;
	bool CreateDC(CDC* tempDC,int width,int height);
	COLORREF transcolor;
	COLORREF m_linecr;
	
	void LoadSysFile();
	void GetExeFilePath(char *filepath);
	int m_addstate;//������״̬
	int m_state;      //�ֿ�״̬
	int m_mstate;      //�ܿ�״̬

	int m_daonei;
	int m_daowai;
	int m_npautopos;

	BOOL m_mapbmpin;   //��ͼλͼ���룻
	BOOL m_scenein;      //������Ϣ���룻
	BOOL m_firsthit;     
	BOOL m_qiehuanstart;
	BOOL m_picwulibin;      //��ƷͼƬ������
	BOOL m_picrenlibin;
	BOOL m_newwupic;
	BOOL m_modelin;
	BOOL m_modeltest;
	CBmp m_bmp;           //��ͼλͼ����
	CBmp m_sample;       //���ͼƬ����
	COLORREF m_color;   
	
	
	POINT m_oldpoint;        
	POINT m_firstpoint;
	
     
	BOOL m_starta;     //��ʼ��������
	BOOL m_startp;
	BOOL m_startth;    //��ʼ�����������
	BOOL m_startcover;   //��ʼ�������ڵ�����
	BOOL m_sysfilein;
	BOOL m_scenechange;

	CMyScene m_myscene;   //��ͼ��Ϣ����
	
    CSceneNpc  m_npcnode;           //
	CThing     m_thing;       
	CSceneThing m_tempthing;   //������Ʒ����
	CSceneNpc   m_tempnpc;     //npc�ڵ�
	CNameLib m_picthlib,m_picnpclib;        //ͼƬ�����
	
	CNpcLib  m_npclib;        //�����

	CItemList  m_attriblist;    //������������

	CThingList    m_thlist;		//��Ʒ��
	
	CArea*	m_acurp;           //�ƶ���ʱ��������ǰָ��
	
	CMyPoint*  m_pcurp;       //�ƶ���ʱ���������ǰָ��


	CDC BakDC,MaskDC,SampleDC,memDC,CurDC,InvertDC,modelDC;
	CSize m_mapSize,m_samSize;

	CString bmppath,samplepath;
	
	char m_WorkingPath[256],mapfilename[256];     //Ӧ�ó���·��
	BOOL m_execute;
	BOOL m_zoomtest;
	BOOL m_postest;

//	CDlgList m_DlgList;
	
	virtual ~CMapEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	
	//{{AFX_MSG(CMapEditDoc)
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSavescene();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnSysfileCreate();
	afx_msg void OnUpdateSysfileCreate(CCmdUI* pCmdUI);
	afx_msg void OnSysfileChange();
	afx_msg void OnUpdateSysfileChange(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModelZoom(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPEDITDOC_H__DDF278C6_6486_4B5C_991A_3DED14B9F440__INCLUDED_)
