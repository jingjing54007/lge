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
	int m_addstate;//加物体状态
	int m_state;      //分控状态
	int m_mstate;      //总控状态

	int m_daonei;
	int m_daowai;
	int m_npautopos;

	BOOL m_mapbmpin;   //地图位图载入；
	BOOL m_scenein;      //场景信息载入；
	BOOL m_firsthit;     
	BOOL m_qiehuanstart;
	BOOL m_picwulibin;      //物品图片库载入
	BOOL m_picrenlibin;
	BOOL m_newwupic;
	BOOL m_modelin;
	BOOL m_modeltest;
	CBmp m_bmp;           //地图位图对象
	CBmp m_sample;       //浏览图片对象
	COLORREF m_color;   
	
	
	POINT m_oldpoint;        
	POINT m_firstpoint;
	
     
	BOOL m_starta;     //开始绘制区域
	BOOL m_startp;
	BOOL m_startth;    //开始加入物体对象
	BOOL m_startcover;   //开始画物体遮挡区域
	BOOL m_sysfilein;
	BOOL m_scenechange;

	CMyScene m_myscene;   //地图信息对象
	
    CSceneNpc  m_npcnode;           //
	CThing     m_thing;       
	CSceneThing m_tempthing;   //场景物品对象
	CSceneNpc   m_tempnpc;     //npc节点
	CNameLib m_picthlib,m_picnpclib;        //图片库对象
	
	CNpcLib  m_npclib;        //人物库

	CItemList  m_attriblist;    //区域属性链表

	CThingList    m_thlist;		//物品库
	
	CArea*	m_acurp;           //移动点时保存区域当前指针
	
	CMyPoint*  m_pcurp;       //移动点时保存点链当前指针


	CDC BakDC,MaskDC,SampleDC,memDC,CurDC,InvertDC,modelDC;
	CSize m_mapSize,m_samSize;

	CString bmppath,samplepath;
	
	char m_WorkingPath[256],mapfilename[256];     //应用程序路径
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
