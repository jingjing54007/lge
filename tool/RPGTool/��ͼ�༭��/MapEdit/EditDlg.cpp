// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapedit.h"
#include "EditDlg.h"


//////////////////////////////
#include "ToolsBar.h"
#include "MapEditDoc.h"
#include "MainFrm.h"
#include "SampleView.h"
#include <afxext.h>
#include "ZoomDlg.h"
#include "QieHuanCode.h"
///////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDlgSingleContent *m_pDlgSingleState=NULL; //某个NPC的某种状态的记录链
CDlgContent *m_pDlgContent=NULL; //某个NPC某个状态的对话
CDlg *m_pDlg=NULL;//某个NPC的全部状态
CDlgList * m_pDlgList=NULL;// 全部NPC的全部对话纪录

CConditionList *m_pConditionList=NULL;
CEventList *m_pEventList=NULL;


int m_nNum;
extern CNpcFace m_NpcFace[20]; //20为人物的数量
extern CNpcFace m_MainFace;

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDlg)
	m_strDlg = _T("");
	m_nNpcDlg = -1;
	//}}AFX_DATA_INIT
}


void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
	DDX_Control(pDX, IDC_LIST_DLG, m_ListDlg);
	DDX_Control(pDX, IDC_LIST_FACE, m_FaceList);
	DDX_Control(pDX, IDC_LIST_STATION, m_StationCtrl);
	DDX_Control(pDX, IDC_RADIO_MAIN, m_CtrlSpeaker);
	DDX_Control(pDX, IDC_RADIO_NPC, m_SpeakerCtrl);
	DDX_Text(pDX, IDC_EDIT_DLG, m_strDlg);
	DDV_MaxChars(pDX, m_strDlg, 200);
	DDX_Radio(pDX, IDC_RADIO_NPC, m_nNpcDlg);
	//}}AFX_DATA_MAP
}

BOOL CEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_nNum=0;
	UpdateData(FALSE);
	
	CDlg *p=m_pDlgList->m_head;
	for(int i=0;i<m_pDlgList->m_nNpcNum && strcmp(p->m_name,m_name);i++,p=p->lpNext);
	m_pDlg=p;

	for(i=0;i<m_pDlg->m_nCountState;i++)
	{
		CString s;
		s.Format("状态%d",i);
		m_StationCtrl.AddString(s);
	}
	CString s;
	s=m_name;
	s+="和主角的对话";
	m_SpeakerCtrl.SetCheck(1);
	m_CtrlSpeaker.SetCheck(0);
    FillCombo();
	SetWindowText(s);
	GetDlgItem(IDC_EDIT_DLG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_INSERT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STAEDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STADELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(FALSE);


	m_nConItem=m_ListDlg.InsertColumn(0,"说话者",LVCFMT_CENTER,60);
	m_ListDlg.InsertColumn(1,"说话表情",LVCFMT_CENTER,70);
	m_ListDlg.InsertColumn(2,"说话内容",LVCFMT_CENTER,280);

//	MyPaint();
	






	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_STATION, OnButtonStation)
	ON_BN_CLICKED(IDC_BUTTON_STADELETE, OnButtonStadelete)
	ON_LBN_SELCHANGE(IDC_LIST_STATION, OnSelchangeListStation)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_STAEDIT, OnButtonStaedit)
	ON_LBN_SELCHANGE(IDC_LIST_FACE, OnSelchangeListFace)
	ON_BN_CLICKED(IDC_RADIO_NPC, OnRadioNpc)
	ON_BN_CLICKED(IDC_RADIO_MAIN, OnRadioMain)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_LIST_DLG, OnClickListDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers

void CEditDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	if(strlen(m_strDlg)>0)
	{


	if(m_nNpcDlg==0)
			m_ListDlg.InsertItem(m_nConItem+m_nNum,m_name);
	else
			m_ListDlg.InsertItem(m_nConItem+m_nNum,"主角");

	m_ListDlg.SetItemText(m_nConItem+m_nNum,2,m_strDlg);



	int n=(m_FaceList.GetCurSel()<0)?0:m_FaceList.GetCurSel();
	if(m_SpeakerCtrl.GetCheck())//选中NPC
	{
		for(int i=0;i<20 && strcmp(m_NpcFace[i].m_name,m_name)!=0;i++);
		m_ListDlg.SetItemText(m_nConItem+m_nNum,1,m_NpcFace[i].m_face[n].m_strDescribe);

			
	}
	else
	{
		m_ListDlg.SetItemText(m_nConItem+m_nNum,1,m_MainFace.m_face[n].m_strDescribe);
	}

	m_nNum++;

	m_strDlg="";
	UpdateData(FALSE);

	int i=m_SpeakerCtrl.GetCheck();
	m_SpeakerCtrl.SetCheck((i==0)?1:0);
	i=m_CtrlSpeaker.GetCheck();
	m_CtrlSpeaker.SetCheck((i==0)?1:0);
	FillCombo();
	GetDlgItem(IDC_EDIT_DLG)->SetFocus();
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(TRUE);



	}
}

void CEditDlg::OnButtonInsert() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(strlen(m_strDlg)>0 && m_nConSelect>=0)
	{
		if(m_nNpcDlg==0)
			m_ListDlg.InsertItem(m_nConSelect,m_name);
		else
			m_ListDlg.InsertItem(m_nConSelect,"主角");
		m_ListDlg.SetItemText(m_nConSelect,2,m_strDlg);

	int n=(m_FaceList.GetCurSel()<0)?0:m_FaceList.GetCurSel();
	if(m_SpeakerCtrl.GetCheck())//选中NPC
	{
		for(int i=0;i<20 && strcmp(m_NpcFace[i].m_name,m_name)!=0;i++);
		
		m_ListDlg.SetItemText(m_nConSelect,1,m_NpcFace[i].m_face[n].m_strDescribe);
			
	}
	else
	{
		m_ListDlg.SetItemText(m_nConSelect,1,m_MainFace.m_face[n].m_strDescribe);
	}
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(TRUE);
		m_nConSelect=-1;
		m_nNum++;




	}

}

void CEditDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here

	if(m_nConSelect>=0)
	{
		GetDlgItem(IDC_BUTTON_OK)->EnableWindow(TRUE);
		m_ListDlg.DeleteItem(m_nConSelect);
		m_nConSelect=-1;
		m_nNum--;
	}
	
}

void CEditDlg::OnButtonEdit() 
{
	// TODO: Add your control notification handler code here

	if(m_nConSelect>=0)
	{

		m_strDlg=m_ListDlg.GetItemText(m_nConSelect,2);

		if(strlen(m_strDlg)>0)
		{				
			UpdateData(FALSE);
			GetDlgItem(IDC_BUTTON_OK)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DLG)->SetFocus();
		}
		m_nConSelect=-1;
	}

	
}

void CEditDlg::OnButtonStation() 
{
	// TODO: Add your control notification handler code here
	CString temp;
	temp.Format("状态%d",m_StationCtrl.GetCount());	
	m_StationCtrl.AddString(temp);
	GetDlgItem(IDC_EDIT_DLG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(TRUE);
	if(m_pDlg->m_head==NULL)
	{
		m_pDlgContent=new CDlgContent;
		m_pDlgContent->lpNext=NULL;
		m_pDlg->m_head=m_pDlgContent;
	}
	else
	{	
	CDlgContent *lp=m_pDlg->m_head;
	CDlgContent *p;
	for(int i=0;i<m_pDlg->m_nCountState-1;i++)
		lp=lp->lpNext;

	p=new CDlgContent;
	p->lpNext=NULL;
	lp->lpNext=p;
	}
	int i=0;
	CDlgContent *lp=m_pDlg->m_head;
	while(lp!=NULL)
	{
		lp=lp->lpNext;
		i++;
	}		
	m_pDlg->m_nCountState++;
		
}

void CEditDlg::OnButtonStadelete() 
{
	// TODO: Add your control notification handler code here
	CDlgContent *lp=m_pDlg->m_head;
	CDlgContent *p;
	int n=m_StationCtrl.GetCurSel();
	CString s;
	if(n<0)
		return;
	if(n==0)
		{
		p=m_pDlg->m_head;
		m_pDlg->m_head=p->lpNext;
		}
	else{
	for(int i=0;i<n-1;i++,lp=lp->lpNext);
	p=lp->lpNext;
	lp->lpNext=p->lpNext;

	}
	m_pDlg->m_nCountState--;
	m_StationCtrl.DeleteString(m_StationCtrl.GetCurSel());
	GetDlgItem(IDC_STATIC_USE)->SetWindowText("未选中任何状态");
	m_ListDlg.DeleteAllItems();
	GetDlgItem(IDC_EDIT_DLG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);
	m_StationCtrl.ResetContent();
	for(int i=0;i<m_pDlg->m_nCountState;i++)
	{
		s.Format("状态%d",i);
		m_StationCtrl.AddString(s);
	}

	
}

void CEditDlg::OnSelchangeListStation() 
{
	// TODO: Add your control notification handler code here

	
	CString temp;
	CDlgContent *lp=m_pDlg->m_head;
	CDlgSingleContent *p;
	temp.Format("状态%d",m_StationCtrl.GetCurSel());
	GetDlgItem(IDC_STATIC_USE)->SetWindowText(temp);
	GetDlgItem(IDC_BUTTON_STAEDIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STADELETE)->EnableWindow(TRUE);

	m_ListDlg.DeleteAllItems();

	if(m_pDlg->m_nCountState>0)
	{
		for(int i=0;i<m_StationCtrl.GetCurSel();i++)
			lp=lp->lpNext;
		int j=lp->CountSentence;
		p=lp->m_head;
		
		for(i=0;i<j;i++)
		{

			if(p->m_nwho==1)//主角
			{

				m_ListDlg.InsertItem(m_nConItem+i,"主角");
				m_ListDlg.SetItemText(m_nConItem+i,2,p->m_Content);
				m_ListDlg.SetItemText(m_nConItem+i,1,m_MainFace.m_face[p->m_nExpressionID].m_strDescribe);
			}
			else
			{
				for(int k=0;k<20 && strcmp(m_NpcFace[k].m_name,m_name)!=0;k++);

				m_ListDlg.InsertItem(m_nConItem+i,m_name);
				m_ListDlg.SetItemText(m_nConItem+i,2,p->m_Content);
				m_ListDlg.SetItemText(m_nConItem+i,1,m_NpcFace[k].m_face[p->m_nExpressionID].m_strDescribe);

			}

			p=p->lpNext;

		}
	}

	m_nNum=m_ListDlg.GetItemCount();

	
}


void CEditDlg::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	


	CDlgContent *p=m_pDlg->m_head;
	for(int i=0;i<m_StationCtrl.GetCurSel();i++,p=p->lpNext);

	m_nNum=m_ListDlg.GetItemCount();
	p->CountSentence=m_nNum;


	CDlgSingleContent *lp;
	for(i=m_nNum-1;i>=0;i--)
	{
		lp=m_pDlgSingleState;
		m_pDlgSingleState=new CDlgSingleContent;

m_pDlgSingleState->m_nwho=strcmp("主角",m_ListDlg.GetItemText(m_nConItem+i,0))+1;

strcpy(m_pDlgSingleState->m_Content,m_ListDlg.GetItemText(m_nConItem+i,2));


if(m_pDlgSingleState->m_nwho==1)//主角
{
	for(int a=0;a<m_MainFace.m_nFaceNum && 
		strcmp(m_MainFace.m_face[a].m_strDescribe,m_ListDlg.GetItemText(m_nConItem+i,1))!=0;a++);
	m_pDlgSingleState->m_nExpressionID=a;

}
else
{
	for(int x=0;x<20 && strcmp(m_NpcFace[x].m_name,m_name)!=0;x++);
	for(int a=0;a<m_NpcFace[x].m_nFaceNum && 
		strcmp(m_NpcFace[x].m_face[a].m_strDescribe,m_ListDlg.GetItemText(m_nConItem+i,1))!=0;a++);
	m_pDlgSingleState->m_nExpressionID=a;

}

		m_pDlgSingleState->lpNext=lp;
	}
	p->m_head=m_pDlgSingleState;
	GetDlgItem(IDC_BUTTON_OK)->EnableWindow(FALSE);		


}




void CEditDlg::OnButtonStaedit() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_EDIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_INSERT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DLG)->EnableWindow(TRUE);
	
}




void CEditDlg::OnSelchangeListFace() 
{
	// TODO: Add your control notification handler code here
//	MyPaint();

	
}

void CEditDlg::OnRadioNpc() 
{
	// TODO: Add your control notification handler code here
		FillCombo();
	
}

void CEditDlg::OnRadioMain() 
{
	// TODO: Add your control notification handler code here
		FillCombo();
	
}

int CEditDlg::FillCombo()
{

	if(!m_CtrlSpeaker.GetCheck()) //选中NPC
	{

		m_FaceList.ResetContent();
		for(int i=0;i<20 && strcmp(m_NpcFace[i].m_name,m_name)!=0;i++);
		if(i<20) //找到了
			for(int j=0;j<m_NpcFace[i].m_nFaceNum;j++)

            m_FaceList.InsertString(j,m_NpcFace[i].m_face[j].m_strDescribe);
		return i;
	}
	else
	{
		m_FaceList.ResetContent();
		for(int j=0;j<m_MainFace.m_nFaceNum;j++)

            m_FaceList.InsertString(j,m_MainFace.m_face[j].m_strDescribe);
		return -1;
	}
	
	


}

void CEditDlg::MyPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_nSelFace=m_FaceList.GetCurSel();
	if(m_nSelFace<0) m_nSelFace=0;

if(m_nSelFace>=0)
{

	CBrush NewBrush((COLORREF)0x0000FF00);
	CBrush *pOldBrush=dc.SelectObject(&NewBrush);
	dc.Rectangle(230,20,300,140);
	dc.SelectObject(pOldBrush);

	char filepath[256],temp[256];

	strcpy(filepath, m_WorkingPath);
	strcpy(temp,filepath);
	strcat(temp, "\\Expression\\");
	int j;

	if(!m_CtrlSpeaker.GetCheck()) //选中NPC
	{
		for(j=0;j<20 && strcmp(m_NpcFace[j].m_name,m_name)!=0;j++);
		
	
	strcat(temp,m_NpcFace[j].m_face[m_nSelFace].m_FileName);
	}
	else
	strcat(temp,m_MainFace.m_face[m_nSelFace].m_FileName);



	CBitmap bmp;
	CBitmap *oldBmp;
	CDC dcMemory;
	HBITMAP hBitmap;
	

	hBitmap=(HBITMAP)::LoadImage(NULL,temp,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	MessageBox(temp);
	if(hBitmap)
	{
		bmp.Attach(hBitmap);
		MessageBox("Get it");
	}

	else
	{
		MessageBox("打开人物表情图片失败");
		return;
	}

	dcMemory.CreateCompatibleDC(&dc);
	oldBmp=dcMemory.SelectObject(&bmp);

//	dc.BitBlt(230,20,144,180,&dcMemory,0,0,SRCCOPY);
	dc.StretchBlt(230,20,400,300,&dcMemory,0,0,800,600,SRCCOPY);
	dcMemory.SelectObject(oldBmp);

}



}



void CEditDlg::OnSelchangeListShow() 
{
	// TODO: Add your control notification handler code here
		
}

void CEditDlg::OnClickListDlg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_LIST_DLG);
	ASSERT(pListCtrl != NULL);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	m_nConSelect= pListCtrl->GetNextSelectedItem(pos);
	*pResult = 0;
/*

		m_SpeakerCtrl.SetCheck(strcmp(m_ListDlg.GetItemText(m_nConSelect,0),m_name)==0);
		m_CtrlSpeaker.SetCheck(strcmp(m_ListDlg.GetItemText(m_nConSelect,0),m_name)!=0);

		FillCombo();
*/
		
}
