// ToolsBar.cpp : implementation file
//

#include "stdafx.h"
#include "MapEdit.h"
#include "ToolsBar.h"
#include "EditDlg.h"


#include "MapEditDoc.h"
#include "MainFrm.h"
#include "SampleView.h"

#include "ConditionDlg.h"


extern CDlg *m_pDlg;//ĳ��NPC��ȫ��״̬
extern CDlgList * m_pDlgList;// ȫ��NPC��ȫ���Ի���¼
extern CDlgContent *m_pDlgContent; //ĳ��NPCĳ��״̬�ĶԻ�

extern CConditionList *m_pConditionList;
extern CEventList *m_pEventList;


CNpcFace m_NpcFace[20]; //20Ϊ���������
CNpcFace m_MainFace;//���ǵ�

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolsBar

IMPLEMENT_DYNCREATE(CToolsBar, CFormView)

CToolsBar::CToolsBar()
	: CFormView(CToolsBar::IDD)
{
	//{{AFX_DATA_INIT(CToolsBar)
	m_zoom = 0.0f;
	m_pos = 0;
	m_strChoose = _T("");

	//}}AFX_DATA_INIT
}

CToolsBar::~CToolsBar()
{

}

void CToolsBar::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolsBar)
	DDX_Control(pDX, IDC_COMBO_CHOOSE, m_ChooseCtrl);
	DDX_Control(pDX, IDC_ORGPOS, m_displaypos);
	DDX_Control(pDX, IDC_NPCZOOM, m_displayzoom);
	DDX_Control(pDX, IDC_COMBO_REN, m_AddRenCtrl);
	DDX_Control(pDX, IDC_COMBO_WU, m_AddWuCtrl);
	DDX_Control(pDX, IDC_COMBO_DAOWAI, m_DaoWaiCtrl);
	DDX_Control(pDX, IDC_COMBO_DAONEI, m_DaoNeiCtrl);
	DDX_CBString(pDX, IDC_COMBO_CHOOSE, m_strChoose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolsBar, CFormView)
	//{{AFX_MSG_MAP(CToolsBar)
	ON_BN_CLICKED(IDC_RADIO_KEZOU, OnRadioKezou)
	ON_BN_CLICKED(IDC_RADIO_DAO, OnRadioDao)
	ON_BN_CLICKED(IDC_RADIO_QIEHUAN, OnRadioQiehuan)
	ON_BN_CLICKED(IDC_RADIO_MOVE, OnRadioMove)
	ON_BN_CLICKED(IDC_RADIO_DELPOINT, OnRadioDelpoint)
	ON_BN_CLICKED(IDC_RADIO_DELAREA, OnRadioDelarea)
	ON_BN_CLICKED(IDC_RADIO_ADDWU, OnRadioAddwu)
	ON_BN_CLICKED(IDC_RADIO_DELWU, OnRadioDelwu)
	ON_BN_CLICKED(IDC_RADIO_ADDREN, OnRadioAddren)
	ON_BN_CLICKED(IDC_RADIO_DELREN, OnRadioDelren)
	ON_BN_CLICKED(IDC_RADIO_CHANGE, OnRadioChange)
	ON_CBN_SELCHANGE(IDC_COMBO_WU, OnSelchangeComboWu)
	ON_CBN_SELCHANGE(IDC_COMBO_DAONEI, OnSelchangeComboDaonei)
	ON_CBN_SELCHANGE(IDC_COMBO_DAOWAI, OnSelchangeComboDaowai)
	ON_CBN_SELCHANGE(IDC_COMBO_REN, OnSelchangeComboRen)
	ON_BN_CLICKED(IDC_BUTTON_ORGPOS, OnButtonOrgpos)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM, OnButtonZoom)
	ON_BN_CLICKED(IDC_RADIO_DELRENPOINT, OnRadioDelrenpoint)
	ON_BN_CLICKED(IDC_RADIO_DELWUPOINT, OnRadioDelwupoint)
	ON_BN_CLICKED(IDC_RADIO_MOVERENPOINT, OnRadioMoverenpoint)
	ON_BN_CLICKED(IDC_RADIO_MOVEWUPOINT, OnRadioMovewupoint)
	ON_BN_CLICKED(IDC_BUTTON_DLG, OnButtonDlg)
	ON_BN_CLICKED(IDC_RADIO_DLG, OnRadioDlg)
	ON_BN_CLICKED(IDC_BUTTON_CONDITION, OnButtonCondition)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsBar diagnostics

#ifdef _DEBUG
void CToolsBar::AssertValid() const
{
	CFormView::AssertValid();
}

void CToolsBar::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolsBar message handlers

void CToolsBar::OnRadioKezou() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_mapbmpin || pDoc->m_scenein)
	{
		pDoc->m_linecr=RGB(0,0,255);
		
		pDoc->m_mstate=1;
		pDoc->m_state=11;
		pDoc->m_starta=true;
		pDoc->BakDC.DeleteDC();
		pDoc->CreateDC(&pDoc->BakDC,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy);
		pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
	}
	else
		AfxMessageBox("û�������ͼλͼ�ļ������ܴ����κγ�����Ϣ!");
	
}

void CToolsBar::OnRadioDao() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_mapbmpin || pDoc->m_scenein)
	{
		pDoc->m_linecr=RGB(0,0,0);
		pDoc->m_mstate=1;
		pDoc->m_state=12;
		pDoc->m_starta=true;
		pDoc->BakDC.DeleteDC();
		pDoc->CreateDC(&pDoc->BakDC,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy);
		pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
	}
	else
		AfxMessageBox("û�������ͼλͼ�ļ������ܴ����κγ�����Ϣ!");
}

void CToolsBar::OnRadioQiehuan() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_mapbmpin || pDoc->m_scenein)
	{
	//	if(pDoc->m_myscene.m_arealist.m_head->m_statein>10000)
			pDoc->m_linecr=pDoc->m_attriblist.SearchID(10000);
	//	else
	//		pDoc->m_linecr=pDoc->m_attriblist.SearchID(pDoc->m_myscene.m_arealist.m_head->m_statein);
		pDoc->m_mstate=1;
		pDoc->m_state=13;
		pDoc->m_starta=true;	
		pDoc->BakDC.DeleteDC();
		pDoc->CreateDC(&pDoc->BakDC,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy);
		pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
	}
	else
		AfxMessageBox("û�������ͼλͼ�ļ������ܴ����κγ�����Ϣ!");
}

void CToolsBar::OnRadioMove() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_scenein && pDoc->m_myscene.m_arealist.m_head!=NULL)
	{
		pDoc->m_mstate=2;
		pDoc->m_state=21;  
	}
	else
		AfxMessageBox("��û�����볡����Ϣ�ļ����߳����ļ���û��������Ϣ�����ܽ����ƶ���Ĳ���!!");	
}

void CToolsBar::OnRadioDelpoint() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_scenein && pDoc->m_myscene.m_arealist.m_head!=NULL)
	{
		pDoc->m_mstate=2;
		pDoc->m_state=22; 

	}
	else
		AfxMessageBox("��û�����볡����Ϣ�ļ����߳����ļ���û��������Ϣ�����ܽ���ɾ�������!!");	
}

void CToolsBar::OnRadioDelarea() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_scenein && pDoc->m_myscene.m_arealist.m_head!=NULL)
	{
		pDoc->m_mstate=2;
		pDoc->m_state=23;   //
	}
	else
		AfxMessageBox("��û�����볡����Ϣ�ļ����߳����ļ���û��������Ϣ�����ܽ���ɾ���������!!");
	
}
void CToolsBar::OnRadioChange() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	m_DaoNeiCtrl.ResetContent();
	m_DaoWaiCtrl.ResetContent();
	if(pDoc->m_attriblist.m_head!=NULL)
	{
		pDoc->m_attriblist.m_curposi=pDoc->m_attriblist.m_head;
		for(int i=0;i<pDoc->m_attriblist.m_count;i++)
		{
			m_DaoNeiCtrl.InsertString(i,pDoc->m_attriblist.m_curposi->myitem.AttribName);
			m_DaoWaiCtrl.InsertString(i,pDoc->m_attriblist.m_curposi->myitem.AttribName);
			pDoc->m_attriblist.Next();
		}
	}
	if(pDoc->m_scenein && pDoc->m_myscene.m_arealist.m_head!=NULL)
	{
		pDoc->m_mstate=2;
		pDoc->m_state=24;
	}
	else
	{
		AfxMessageBox("��û�����볡����Ϣ�ļ����߳����ļ���û��������Ϣ�����ܽ��иı����ԵĲ���!!");	
	}
	
}
void CToolsBar::OnRadioAddwu() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	char sysfilepath[256],filepath[256];
	
	strcpy(sysfilepath, pDoc->m_WorkingPath);
	strcat(sysfilepath, "\\System.dat");

	ifstream in;
	in.open(sysfilepath,ios::nocreate|ios::in|ios::binary);
	if(in)
	{
		pDoc->m_attriblist.m_head=NULL;
		pDoc->m_attriblist.read(in);
		pDoc->m_sysfilein=true;
		in.close();
	}
	else
	{
		in.close();
		pDoc->m_sysfilein=false;
	}

	strcpy(filepath, pDoc->m_WorkingPath);
	strcat(filepath, "\\thlib\\piclib.txt");
	
	if(!pDoc->m_picthlib.read(filepath)) //������ƷͼƬ��
	{
		AfxMessageBox("û���ҵ���ƷͼƬ�⣡");
//		exit(0);
	}
	else
	{
		strcpy(filepath, pDoc->m_WorkingPath);
		strcat(filepath, "\\thlib\\object");

		in.open(filepath,ios::nocreate|ios::in|ios::binary);
		if(in)
		{
			pDoc->m_thlist.read(in);       //������Ʒ��
			in.close();
			pDoc->m_picwulibin=true;
		}
		else
		{
			pDoc->m_picwulibin=false;
			in.close();
		}
	}


	//����ͼƬ����Ϣ
	if(pDoc->m_picwulibin)
	{
		pDoc->m_thlist.m_curposi=pDoc->m_thlist.m_head;
		for(int i=0;i<pDoc->m_thlist.m_count;i++)
		{
			m_AddWuCtrl.AddString(pDoc->m_thlist.m_curposi->m_name);
			pDoc->m_thlist.Next();
		}
		pDoc->m_picwulibin=false;  //��ֹ�´μ�ʱ���¼���
	}
	pDoc->m_startth=true;
}

void CToolsBar::OnRadioDelwu() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_myscene.m_thinglist.m_head!=NULL)
	{
		pDoc->m_mstate=3;
		pDoc->m_state=32;  
	}
	else
	{
		AfxMessageBox("������Ϣ��û����Ʒ��Ϣ��");
	}
	
}

void CToolsBar::OnRadioAddren() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();


	char sysfilepath[256],filepath[256];
	
	strcpy(sysfilepath, pDoc->m_WorkingPath);
	strcat(sysfilepath, "\\System.dat");

	ifstream in;
	in.open(sysfilepath,ios::nocreate|ios::in|ios::binary);
	if(in)
	{
		pDoc->m_attriblist.m_head=NULL;
		pDoc->m_attriblist.read(in);
		pDoc->m_sysfilein=true;
		in.close();
	}
	else
	{
		in.close();
		pDoc->m_sysfilein=false;
	}

	
	
	strcpy(filepath, pDoc->m_WorkingPath);
	strcat(filepath, "\\npclib\\piclib.txt");
	
	if(!pDoc->m_picnpclib.read(filepath)) //��������ͼƬ��
	{
		AfxMessageBox("û���ҵ�����ͼƬ�⣡");
//		exit(0);
	}
	else
	{
		strcpy(filepath, pDoc->m_WorkingPath);
		strcat(filepath, "\\npclib\\rolelib.cha");
		
		in.open(filepath,ios::nocreate|ios::in|ios::binary);
		if(in)
		{
			pDoc->m_npclib.read(in);//���������
			in.close();
			pDoc->m_picrenlibin=true;
		}
		else
		{
			pDoc->m_picrenlibin=false;
			in.close();
		}
	}










	//����ͼƬ����Ϣ
	if(pDoc->m_picrenlibin)
	{
		for(int i=0;i<pDoc->m_npclib.m_count;i++)
		{
			m_AddRenCtrl.AddString(pDoc->m_npclib.Npc[i].m_name);
		}
		
		pDoc->m_picrenlibin=false;  //��ֹ�´μ�ʱ���¼���
	}

}

void CToolsBar::OnRadioDelren() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_myscene.m_npclist.m_head!=NULL)
	{
		pDoc->m_mstate=4;
		pDoc->m_state=42;  
	}
	else
	{
		AfxMessageBox("������Ϣ��û��������Ϣ��");
	}
	
}

void CToolsBar::OnSelchangeComboWu() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();

	if(!pDoc->m_mapbmpin && !pDoc->m_scenein)
	{
		AfxMessageBox("û�������ͼλͼ�ļ������ܽ��г����༭����");
		return;
	}
	char filepath[256];
	strcpy(filepath, pDoc->m_WorkingPath);
	strcat(filepath, "\\thlib\\");
	int id=m_AddWuCtrl.GetCurSel();
	pDoc->m_thlist.Find(id);
	strcat(filepath,pDoc->m_picthlib.m_name[pDoc->m_thlist.m_curposi->m_picid]);
//	strcat(filepath,".bmp");
	if(pDoc->SampleHb!=NULL)
		DeleteObject(pDoc->SampleHb);

	//pDoc->LoadBmpFromFile(filepath,&pDoc->SampleHb);
	pDoc->SampleHb=(HBITMAP)LoadImage(NULL,filepath,IMAGE_BITMAP,0,0,
			               LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	
	if(pDoc->SampleHb==NULL)
		AfxMessageBox("����Ʒλͼ�ļ�����");
	else
	{	//��������λͼ�ڴ�DC
		pDoc->SampleDC.DeleteDC();
		pDoc->MaskDC.DeleteDC();
		pDoc->BakDC.DeleteDC();
	
		pDoc->CreateDC(&pDoc->BakDC,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy);
		
		//���ݵ�ǰDC
		pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
		
	
		GetObject(pDoc->SampleHb,sizeof(pDoc->SampleBm),&pDoc->SampleBm);
		
		pDoc->m_samSize.cx=pDoc->SampleBm.bmWidth;
		pDoc->m_samSize.cy=pDoc->SampleBm.bmHeight;
		pDoc->CreateDC(&pDoc->SampleDC,pDoc->SampleBm.bmWidth,pDoc->SampleBm.bmHeight); 
		//������ƶ�ʵ��ʾ
		pDoc->CreateDC(&pDoc->MaskDC,pDoc->SampleBm.bmWidth,pDoc->SampleBm.bmHeight);
		
		pDoc->SampleDC.SelectObject(pDoc->SampleHb);
	
		pDoc->transcolor=pDoc->SampleDC.GetPixel(CPoint(0,0));
		pDoc->TransDCtoDC(&pDoc->MaskDC,0,0,&pDoc->SampleDC,pDoc->m_samSize.cx,pDoc->m_samSize.cy,1);
		
		//�õ���ƷID��
		pDoc->m_tempthing.m_id=m_AddWuCtrl.GetCurSel();
		pDoc->m_newwupic=true;
		CMainFrame* pMainWnd=(CMainFrame*)AfxGetMainWnd();
		CSampleView* pView = (CSampleView*)pMainWnd->m_wndSplitter2.GetPane(0,0);
		pView->Invalidate(true);
		pDoc->m_mstate=3;
		pDoc->m_state=31;
		pDoc->m_linecr=RGB(0,0,0);
	}
}

void CToolsBar::OnSelchangeComboDaonei() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	
	pDoc->m_attriblist.m_curposi=pDoc->m_attriblist.m_head;

	for(int i=0;i<m_DaoNeiCtrl.GetCurSel();i++)
	{
		pDoc->m_attriblist.Next();
	}
	if(strcmp(pDoc->m_attriblist.m_curposi->myitem.AttribName,"�л���")==0)
	{
		CQieHuanCode dlg;
		strcpy(dlg.path,pDoc->m_WorkingPath);
		dlg.m_QieHuanCode=10000;
		if(dlg.DoModal()==IDOK)
			pDoc->m_daonei=m_qiehuancode;
		else
			pDoc->m_daonei=-1;
	}
	else
		pDoc->m_daonei=pDoc->m_attriblist.m_curposi->myitem.AttribCode;
		
}

void CToolsBar::OnSelchangeComboDaowai() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	
	pDoc->m_attriblist.m_curposi=pDoc->m_attriblist.m_head;

	for(int i=0;i<m_DaoWaiCtrl.GetCurSel();i++)
	{
		pDoc->m_attriblist.Next();
	}
	pDoc->m_daowai=pDoc->m_attriblist.m_curposi->myitem.AttribCode;
}

void CToolsBar::OnSelchangeComboRen() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();

	if(!pDoc->m_mapbmpin && !pDoc->m_scenein)
	{
		AfxMessageBox("û�������ͼλͼ�ļ������ܽ��г����༭����");
		return;
	}
	char filepath[256];
	strcpy(filepath, pDoc->m_WorkingPath);
	strcat(filepath, "\\npclib\\");
	int renid=m_AddRenCtrl.GetCurSel();
	int picid=pDoc->m_npclib.Npc[renid].m_picid[0];

	strcat(filepath,pDoc->m_picnpclib.m_name[picid]);
//	strcat(filepath,".bmp");
	if(pDoc->SampleHb!=NULL)
		DeleteObject(pDoc->SampleHb);
	pDoc->SampleHb=(HBITMAP)LoadImage(NULL,filepath,IMAGE_BITMAP,0,0,
			               LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	if(pDoc->SampleHb==NULL)
		AfxMessageBox("������λͼ�ļ�����");
	else
	{	//��������λͼ�ڴ�DC
		pDoc->SampleDC.DeleteDC();
		pDoc->MaskDC.DeleteDC();
		pDoc->BakDC.DeleteDC();
	

		pDoc->CreateDC(&pDoc->BakDC,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy);
		
	
		//BakDC ���浱ǰDC
		pDoc->BakDC.BitBlt(0,0,pDoc->m_mapSize.cx,pDoc->m_mapSize.cy,&pDoc->CurDC,0,0,SRCCOPY);
	
		GetObject(pDoc->SampleHb,sizeof(pDoc->SampleBm),&pDoc->SampleBm);
		
		pDoc->m_samSize.cx=80; //pDoc->SampleBm.bmWidth;
		pDoc->m_samSize.cy=100; //pDoc->SampleBm.bmHeight;
		CDC temp;
		pDoc->CreateDC(&temp,pDoc->m_samSize.cx,pDoc->m_samSize.cy);
		
		temp.SelectObject(pDoc->SampleHb);
		
		pDoc->CreateDC(&pDoc->SampleDC,pDoc->m_samSize.cx,pDoc->m_samSize.cy); 
		pDoc->CreateDC(&pDoc->MaskDC,pDoc->m_samSize.cx,pDoc->m_samSize.cy);
		
		pDoc->transcolor=temp.GetPixel(CPoint(0,0));
		
		pDoc->TransDCtoDC(&temp,0,0,&pDoc->SampleDC,pDoc->m_samSize.cx,pDoc->m_samSize.cy,0);
		
		pDoc->TransDCtoDC(&pDoc->MaskDC,0,0,&pDoc->SampleDC,pDoc->m_samSize.cx,pDoc->m_samSize.cy,1);

		ReleaseDC(&temp);
	
	/*	pDoc->CreateDC(&pDoc->SampleDC,pDoc->SampleBm.bmWidth,pDoc->SampleBm.bmHeight);
		
		pDoc->SampleDC.SelectObject(pDoc->SampleHb);
		pDoc->m_samSize.cx=pDoc->SampleBm.bmWidth;
		pDoc->m_samSize.cy=pDoc->SampleBm.bmHeight;
	*/
		//�õ���ƷID��
		pDoc->m_tempnpc.m_id=m_AddRenCtrl.GetCurSel();
		pDoc->m_newwupic=true;
		CMainFrame* pMainWnd=(CMainFrame*)AfxGetMainWnd();
		CSampleView* pView = (CSampleView*)pMainWnd->m_wndSplitter2.GetPane(0,0);
		pView->Invalidate(true);
		pDoc->m_mstate=4;
		pDoc->m_state=41; 
		pDoc->m_addstate=0;	
		pDoc->m_linecr=RGB(0,0,0);
		pDoc->m_oldpoint.x=pDoc->m_oldpoint.y=0;
	}
}


void CToolsBar::OnButtonOrgpos() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(!pDoc->m_scenein && !pDoc->m_scenechange)
	{
		AfxMessageBox("û�����볡����Ϣ�����ܽ��г����༭����");
		return;
	}
	else
	{
		pDoc->m_mstate=5;
		pDoc->m_state=52;
	}
}

void CToolsBar::OnButtonZoom() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	CZoomDlg dlg;
	if(!pDoc->m_scenein && !pDoc->m_scenechange)
	{
		AfxMessageBox("û�����볡����Ϣ�����ܽ��г����༭����");
		return;
	}
	else
	{
		dlg.m_minvalue=pDoc->m_myscene.m_minsize;
		dlg.m_maxvalue=pDoc->m_myscene.m_maxsize;
		if(dlg.DoModal()==IDOK)
		{
			pDoc->m_scenechange=true;
			m_save=1;
			CString ss;
			pDoc->m_myscene.m_maxsize=m_zoomout;
			pDoc->m_myscene.m_minsize=m_zoomin;
			ss.Format("F:%f,N:%f",pDoc->m_myscene.m_minsize,pDoc->m_myscene.m_maxsize);
			m_displayzoom.SetWindowText(ss);
		}
	}
}

void CToolsBar::OnRadioDelrenpoint() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_myscene.m_npclist.m_count!=0)
	{
		pDoc->m_mstate=4;
		pDoc->m_state=44;
	}
	else
	{
		AfxMessageBox("������Ϣ��û��������Ϣ�����ܽ��д˲�����");
		pDoc->m_mstate=0;
	}
}

void CToolsBar::OnRadioDelwupoint() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_myscene.m_thinglist.m_count!=0)
	{
		pDoc->m_mstate=3;
		pDoc->m_state=34;
	}
	else
	{
		AfxMessageBox("������Ϣ��û����Ʒ��Ϣ�����ܽ��д˲�����");
		pDoc->m_mstate=0;
	}
}

void CToolsBar::OnRadioMoverenpoint() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_myscene.m_npclist.m_count!=0)
	{
		pDoc->m_mstate=4;
		pDoc->m_state=43;
	}
	else
	{
		AfxMessageBox("������Ϣ��û��������Ϣ�����ܽ��д˲�����");
		pDoc->m_mstate=0;
	}
}

void CToolsBar::OnRadioMovewupoint() 
{
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	if(pDoc->m_myscene.m_thinglist.m_count!=0)
	{
		pDoc->m_mstate=3;
		pDoc->m_state=33;
	}
	else
	{
		AfxMessageBox("������Ϣ��û����Ʒ��Ϣ�����ܽ��д˲�����");
		pDoc->m_mstate=0;
	}
	
}

void CToolsBar::OnButtonDlg() 
{
	// TODO: Add your control notification handler code here




	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	static BOOL bNpcin=FALSE;
	if(!bNpcin)
	{
		char filepath[256],temp[256];
		strcpy(filepath, pDoc->m_WorkingPath);
		int num=0;
		for(int k=0;k<pDoc->m_npclib.m_count;k++)
		{
		strcpy(temp,filepath);
		strcat(temp, "\\Expression\\");
		strcat(temp,pDoc->m_npclib.Npc[k].m_name);
		strcat(temp,".txt");
		if(!m_NpcFace[num].read(temp)); //��������ͼƬ��
		else
			num++;
		}
		strcpy(temp,filepath);
		strcat(temp, "\\Expression\\����.txt");
		if(!m_MainFace.read(temp))
			AfxMessageBox("û���ҵ����Ǳ���ͼƬ��");
		bNpcin=TRUE;
	}

    UpdateData(TRUE);
	CEditDlg dlg;
	strcpy(dlg.m_name,m_strChoose);
	strcpy(dlg.m_WorkingPath,pDoc->m_WorkingPath);
	if(strlen(m_strChoose)>0)
	{
	CDlg *p;
	p=m_pDlgList->m_head;
	for(int i=0;i<m_pDlgList->m_nNpcNum && strcmp(p->m_name,m_strChoose);i++,p=p->lpNext);
	if(!m_pDlgList->m_nNpcNum || p==NULL) //û���ҵ�,Ҫ�½�һ��CDlg,����CDlgList��
	{
		p=m_pDlgList->m_head;
		m_pDlg=new CDlg;
		m_pDlg->lpNext=p;
		m_pDlgList->m_head=m_pDlg; 
		strcpy(m_pDlg->m_name,m_strChoose);
		m_pDlgList->m_nNpcNum++;
	}
	else
		m_pDlgContent=p->m_head;
	
	dlg.DoModal(); //������NPC���жԻ�״̬�Ľṹ��
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	pDoc->m_scenechange=1;
	CSceneNpc *lp =pDoc->m_myscene.m_npclist.m_head;
	m_ChooseCtrl.ResetContent();
	while(lp!=NULL)
	{
		m_ChooseCtrl.AddString(pDoc->m_npclib.Npc[lp->m_id].m_name);
		lp=lp->lpNext;
	}
	}
}

void CToolsBar::OnRadioDlg() 
{
	// TODO: Add your control notification handler code here
	if(m_pDlgList==NULL)
		m_pDlgList=new CDlgList;
	CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
	CSceneNpc *lp =pDoc->m_myscene.m_npclist.m_head;
	m_ChooseCtrl.ResetContent();
	while(lp!=NULL)
	{
		m_ChooseCtrl.AddString(pDoc->m_npclib.Npc[lp->m_id].m_name);
		lp=lp->lpNext;
	}
	GetDlgItem(IDC_COMBO_CHOOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DLG)->EnableWindow(TRUE);

	
}

void CToolsBar::OnButtonCondition() 
{
	// TODO: Add your control notification handler code here
	CConditionDlg dlg;
	if(m_pConditionList==NULL)
		m_pConditionList=new CConditionList;
	if(m_pEventList==NULL)
		m_pEventList=new CEventList;
	if(dlg.DoModal()==IDOK)
	{
		CMapEditDoc * pDoc=(CMapEditDoc*)GetDocument();
		pDoc->m_scenechange=1;
	}
	
}
