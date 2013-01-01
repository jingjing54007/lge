// ConditionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mapedit.h"
#include "ConditionDlg.h"
#include "scene.h"
#include "EditConditionDlg.h"
#include "EditEventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CConditionList *m_pConditionList;
extern CEventList *m_pEventList;

/////////////////////////////////////////////////////////////////////////////
// CConditionDlg dialog


CConditionDlg::CConditionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConditionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConditionDlg)
	m_ConditionDescribe = _T("");
	m_EventDescribe = _T("");
	m_Expression = _T("");
	//}}AFX_DATA_INIT
}


void CConditionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConditionDlg)
	DDX_Control(pDX, IDC_LIST_EVENT, m_ListEvent);
	DDX_Control(pDX, IDC_LIST_CONDITION, m_ListCondition);
	DDX_Text(pDX, IDC_EDIT_CONDESCRIBE, m_ConditionDescribe);
	DDV_MaxChars(pDX, m_ConditionDescribe, 50);
	DDX_Text(pDX, IDC_EDIT_EVENTDESCRIBE, m_EventDescribe);
	DDV_MaxChars(pDX, m_EventDescribe, 50);
	DDX_Text(pDX, IDC_EDIT_EXPRESSION, m_Expression);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConditionDlg, CDialog)
	//{{AFX_MSG_MAP(CConditionDlg)
	ON_BN_CLICKED(IDC_BUTTON_CONOK, OnButtonConok)
	ON_BN_CLICKED(IDC_BUTTON_EVENTOK, OnButtonEventok)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CONDITION, OnClickListCondition)
	ON_BN_CLICKED(IDC_BUTTON_CONDEL, OnButtonCondel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_EVENT, OnClickListEvent)
	ON_BN_CLICKED(IDC_BUTTON_EVENTDEL, OnButtonEventdel)
	ON_BN_CLICKED(IDC_BUTTON_EVENTEDIT, OnButtonEventedit)
	ON_BN_CLICKED(IDC_BUTTON_CONEDIT, OnButtonConedit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConditionDlg message handlers

BOOL CConditionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText("条件事件编辑");

	m_nConItem=m_ListCondition.InsertColumn(0,"条件ID",LVCFMT_CENTER,50);
	m_ListCondition.InsertColumn(1,"条件描述",LVCFMT_CENTER,120);
	m_ListCondition.InsertColumn(2,"使用否",LVCFMT_CENTER,60);

	m_nEventItem=m_ListEvent.InsertColumn(0,"事件ID",LVCFMT_CENTER,50);
	m_ListEvent.InsertColumn(1,"事件描述",LVCFMT_CENTER,120);
	m_ListEvent.InsertColumn(2,"事件的条件逻辑",LVCFMT_CENTER,120);
	m_ListEvent.InsertColumn(3,"备注",LVCFMT_CENTER,40);

	m_nConSelect=-1;
	m_nEventSelect=-1;


	if(m_pConditionList!=NULL)
	{
		CCondition *lp=m_pConditionList->m_head;
		for(int i=0;i<m_pConditionList->m_nConditionNum ;i++,lp=lp->lpNext)
		{
			CString s;
			s.Empty();
			if(lp->m_nID>9)
			{			
				s+=char(int(lp->m_nID/10)+48);
				s+=char(lp->m_nID%10+48);
			}
			else
				s+=char(lp->m_nID+48);
			m_ListCondition.InsertItem(m_nConItem,s);
			m_ListCondition.SetItemText(m_nConItem,1,lp->m_Describe);
			if(lp->m_nUsed)
				m_ListCondition.SetItemText(m_nConItem,2,"使用过");
			else
				m_ListCondition.SetItemText(m_nConItem,2,"未被使用过");
		}
	}
	if(m_pEventList!=NULL)
	{
		CEvent *lp=m_pEventList->m_head;
		for(int i=0;i<m_pEventList->m_nEventNum ;i++,lp=lp->lpNext)
		{
			CString s;
			s.Empty();
			if(lp->m_nID>9)
			{			
				s+=char(int(lp->m_nID/10)+48);
				s+=char(lp->m_nID%10+48);
			}
			else
				s+=char(lp->m_nID+48);

			m_ListEvent.InsertItem(m_nEventItem,s);
			m_ListEvent.SetItemText(m_nEventItem,1,lp->m_Describe);
			m_ListEvent.SetItemText(m_nEventItem,2,lp->m_Expression);
			if(strlen(CheckCondition(lp->m_Expression,0))==0)
				m_ListEvent.SetItemText(m_nEventItem,3,"无效");
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConditionDlg::OnButtonConok() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if(strlen(m_ConditionDescribe)>0)
	{
		CString s;
		s.Empty();
		if(m_pConditionList->m_nConditionNum>9)
		{			
			s+=char(int(m_pConditionList->m_nConditionNum/10)+48);
			s+=char(m_pConditionList->m_nConditionNum%10+48);
		}
		else
			s+=char(m_pConditionList->m_nConditionNum+48);
		m_nConItem=m_ListCondition.GetItemCount();
		
		m_ListCondition.InsertItem(m_nConItem,s);
		m_ListCondition.SetItemText(m_nConItem,1,m_ConditionDescribe);
		m_ListCondition.SetItemText(m_nConItem,2,"未被使用过");


    	//改变控件显示
		m_pConditionList->m_nConditionNum++;

		CCondition *lp;
		lp=m_pConditionList->m_head;
		m_pConditionList->m_head=new CCondition;
		m_pConditionList->m_head->m_nID=m_pConditionList->m_nConditionNum-1;
		strcpy(m_pConditionList->m_head->m_Describe,m_ConditionDescribe);
		m_pConditionList->m_head->lpNext=lp;
	
		//改变结构
		m_ConditionDescribe.Empty();
		UpdateData(FALSE);
	}
	GetDlgItem(IDC_EDIT_CONDESCRIBE)->SetFocus();
}

BOOL CheckCharacer(CString s)
{
	for(UINT i=0;i<strlen(s);i++)
	{
		char c=s.GetAt(i);
		if(!( (c==')') || (c=='(') || (c=='&') || (c=='|') || (c>='0' && c<='9')))
			return FALSE;
	}
	return TRUE;
}

CString CheckCondition(CString s,int f)//f=1,改变状态的Used值
{
	int n;char c1,c2;
	CString dd=s;
	CString t;
	t.Empty();
	for(UINT i=0;i<strlen(dd);i++)
	{
		char c=dd.GetAt(i);
		if(c>='0' && c<='9')
		{
			if ( (i+1<strlen(dd)) && (c1=dd.GetAt(i+1)) &&(c1>='0' && c1<='9'))
			{	
				if((i+2<strlen(dd)) && (c2=dd.GetAt(i+2)) &&(c2>='0' && c2<='9'))
					return t;
				dd.Delete(i+1);
				n=((int)c-48)*10+((int)c1-48);
			}			
			else
				n=(int)c-48;
		CCondition *lp=m_pConditionList->m_head;
		int flag=0;
		lp=m_pConditionList->m_head;
		for(int j=0;j<m_pConditionList->m_nConditionNum && flag==0;j++)
		{
			if(lp->m_nID==n)				
				flag=1;
			else
				lp=lp->lpNext;
		}
		if(flag==0)
			return t;
		dd.Delete(i);
		dd.Insert(i,char(lp->m_nDone+48));
		if(f==1)
			lp->m_nUsed=1;
		}
	}
	return dd;
}

int nPos;
int nLeft;
int nRight;
BOOL MeetLeft(CString dd);
BOOL MeetRight(CString dd);
BOOL MeetNum(CString dd);
BOOL MeetOper(CString dd);


BOOL MeetLeft(CString dd)
{
	nPos++;
	nLeft++;
	switch(dd.GetAt(nPos))
	{
		case ('0'):
			if(!MeetNum(dd))
				return FALSE;
			break;
		case ('1'):
			if(!MeetNum(dd))
				return FALSE;
			break;
		case ('('):
			if(!MeetLeft(dd))
				return FALSE;
			break;
		default:
			return FALSE;
	}
	return TRUE;

}
BOOL MeetRight(CString dd)
{
	nPos++;
	nRight++;
	switch(dd.GetAt(nPos))
	{
	case ('#'):
		break;
	case ('&'):
		if(!MeetOper(dd))
			return FALSE;
		break;
	case ('|'):
		if(!MeetOper(dd))
			return FALSE;
		break;
	case ')':
		if(!MeetRight(dd))
			return FALSE;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL MeetNum(CString dd)
{
	nPos++;
	switch(dd.GetAt(nPos))
	{
	case (')'):
		if(!MeetRight(dd))
			return FALSE;
		break;
	case ('&'):
		if(!MeetOper(dd))
			return FALSE;
		break;
	case ('|'):
		if(!MeetOper(dd))
			return FALSE;
		break;
	case ('#'):
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL MeetOper(CString dd)
{
	nPos++;
	switch(dd.GetAt(nPos))
	{
	case ('0'):
		if(!MeetNum(dd))
			return FALSE;
		break;
	case ('1'):
		if(!MeetNum(dd))
			return FALSE;
		break;
	case '(':
		if(!MeetLeft(dd))
			return FALSE;
		break;

	default:
		return FALSE;
	}
	return TRUE;
}

BOOL GrammarCheck(CString s)
{
	nPos=0;	
	nLeft=0;
	nRight=0;
	CString dd=s+'#';
	switch(dd.GetAt(nPos))
	{
	case '(':
		if(MeetLeft(dd)==FALSE)
			return FALSE;
		break;
	case ')':
		if(MeetRight(dd)==FALSE)
			return FALSE;
		break;
	case '0':
		if(MeetNum(dd)==FALSE)
			return FALSE;
		break;
	case '1':
		if(MeetNum(dd)==FALSE)
			return FALSE;
		break;

	default:
		return FALSE;
	}
	if(nLeft==nRight)	return TRUE;
	else return FALSE;
}





int Calculate(CString s)
{
	int n[2];
	BOOL b_And;
	int j=0;
	AfxMessageBox(s);
	for(UINT i=0;i<strlen(s);i++)
	{
	switch (s.GetAt(i))
	{
	case '0':
	n[j]=0;
	if(j==1)
	{
	if(b_And)	n[0]=n[0]&&n[1];
	else	n[0]=n[0]||n[1];
	}
	j=1;
	break;
	case '1':
	n[j]=1;
	if(j==1)
	{						
	if(b_And)	n[0]=n[0]&&n[1];
	else	n[0]=n[0]||n[1];
	}
	j=1;
	break;	
	case '&':
	b_And=TRUE;
	break;		
	case '|':
	b_And=FALSE;
	break;
	}
	}
	return n[0];
	}


	int result(CString s)
	{
		CString dd=s;
		int nLeft,nRight;
		CString cal;
		int temp;
		for(UINT i=0;i<strlen(dd);i++)
		{
			if(dd.GetAt(i)=='(')
				nLeft=i;
			if(dd.GetAt(i)==')')
			{
				nRight=i;
				cal.Empty();
				for(int j=1;j<nRight-nLeft;j++)
				cal+=dd.GetAt(nLeft+j);
				temp=Calculate(cal);
				dd.Insert(nLeft,char(temp+48));
				dd.Delete(nLeft+1,nRight-nLeft+1);
				i=nLeft;
				AfxMessageBox(dd);
			}

		}
		return Calculate(dd);


	}







void CConditionDlg::OnButtonEventok() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nEventItem=m_ListEvent.GetItemCount();

	if( (strlen(m_EventDescribe)>0) && (strlen(m_Expression)>0))
	{
		if(CheckCharacer(m_Expression) && strlen(CheckCondition(m_Expression,0))>0)
		{	CString t;
		    t=CheckCondition(m_Expression,0);
			if(GrammarCheck(t)) 
			{
				CheckCondition(m_Expression,1);
				int n=m_pEventList->m_nEventNum-1;
				CString dd;
				int flag;
                do
				{
					flag=0;
					n++;
					CEvent *lp=m_pEventList->m_head;
					for(int i=0;i<m_pEventList->m_nEventNum && flag==0;i++,lp=lp->lpNext)
					{
						if(n==lp->m_nID)	
							flag=1;
					}

				}while(flag==1 && n<100 );

				CString s;
				s.Empty();
				if(n>9)
				{			
				s+=char(int(n/10)+48);
				s+=char(n%10+48);
				}
				else
					s+=char(n+48);
				m_ListEvent.InsertItem(m_nEventItem,s);
				m_ListEvent.SetItemText(m_nEventItem,1,m_EventDescribe);
				m_ListEvent.SetItemText(m_nEventItem,2,m_Expression);
				m_pEventList->m_nEventNum++;
				CEvent *lp;
				lp=m_pEventList->m_head;
				m_pEventList->m_head=new CEvent;
				m_pEventList->m_head->m_nID=n;
				strcpy(m_pEventList->m_head->m_Describe,m_EventDescribe);
				strcpy(m_pEventList->m_head->m_Expression,m_Expression);
				m_pEventList->m_head->lpNext=lp;
				m_EventDescribe.Empty();
				m_Expression.Empty();
				UpdateData(FALSE);
				Refresh();


			}
			else  AfxMessageBox("表达式语法错误!");
		}
		else
			MessageBox("        表达式中存在\n\n非法字符或者错误条件ID!");
	}
	GetDlgItem(IDC_EDIT_EVENTDESCRIBE)->SetFocus();
}



void CConditionDlg::OnClickListCondition(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_LIST_CONDITION);
	ASSERT(pListCtrl != NULL);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	m_nConSelect= pListCtrl->GetNextSelectedItem(pos);
	*pResult = 0;
}

void CConditionDlg::OnButtonCondel() 
{
	// TODO: Add your control notification handler code here
if(m_nConSelect>=0)
{
	m_ListCondition.DeleteItem(m_nConSelect);
	CCondition *lp=m_pConditionList->m_head;
	CCondition *p;
	if(m_nConSelect==m_ListCondition.GetItemCount())
	{
		m_pConditionList->m_head=lp->lpNext;
		delete lp;
	}
	else
	{	
	for(int i=0;i<m_pConditionList->m_nConditionNum-m_nConSelect-2;i++,lp=lp->lpNext);
	p=lp->lpNext;
	lp->lpNext=lp->lpNext->lpNext;
	delete p;
	}
		
	m_pConditionList->m_nConditionNum--;
	m_nConSelect=-1;

	Refresh();




}
	
}

void CConditionDlg::OnClickListEvent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_LIST_EVENT);
	ASSERT(pListCtrl != NULL);
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	m_nEventSelect= pListCtrl->GetNextSelectedItem(pos);
	*pResult = 0;
}

void CConditionDlg::OnButtonEventdel() 
{
	// TODO: Add your control notification handler code here

	if(m_nEventSelect>=0)
{
	m_ListEvent.DeleteItem(m_nEventSelect);
	CEvent *lp=m_pEventList->m_head;
	CEvent *p;
	if(m_nEventSelect==m_ListEvent.GetItemCount())
	{
		m_pEventList->m_head=lp->lpNext;
		delete lp;
	}
	else
	{	
	for(int i=0;i<m_pEventList->m_nEventNum-m_nEventSelect-2;i++,lp=lp->lpNext);
	p=lp->lpNext;
	lp->lpNext=lp->lpNext->lpNext;
	delete p;
	}
	m_pEventList->m_nEventNum--;
	m_nEventSelect=-1;
	CCondition *p1=m_pConditionList->m_head;
	for(int j=0;j<m_pConditionList->m_nConditionNum ;j++,p1=p1->lpNext)
		p1->m_nUsed=0;

	Refresh();
}
	
}







void CConditionDlg::OnButtonEventedit() 
{
	// TODO: Add your control notification handler code here
/*	
    CString t;
	t="1&(0|1)|(1&0)&(0|1&1|0)";

	int i=result(t);
	CString s;

	s.Format("最终结果为%d",i);
	AfxMessageBox(s);
*/

	if(m_nEventSelect>=0)
	{

	CEvent *lp=m_pEventList->m_head;
	for(int i=0;i<m_pEventList->m_nEventNum-m_nEventSelect-1;i++,lp=lp->lpNext);
	CEditEventDlg dlg;
	dlg.m_strEventDescribe=lp->m_Describe;
	dlg.m_nEventID=lp->m_nID;
	dlg.m_nOld=lp->m_nID;
	dlg.m_strExpression=lp->m_Expression;

	if(dlg.DoModal()==IDOK)
	{
		CheckCondition(lp->m_Expression,1);
	
	strcpy(lp->m_Describe,dlg.m_strEventDescribe);
	strcpy(lp->m_Expression,dlg.m_strExpression);
	lp->m_nID=dlg.m_nEventID;
	m_ListEvent.DeleteItem(m_nEventSelect);
	

	CString s;
	s.Empty();
	if(lp->m_nID>9)
	{
		s+=char(int(lp->m_nID/10)+48);
		s+=char(lp->m_nID%10+48);
	}
	else
		s+=char(lp->m_nID+48);


	m_ListEvent.InsertItem(m_nEventSelect,s);
	m_ListEvent.SetItemText(m_nEventSelect,1,lp->m_Describe);
	m_ListEvent.SetItemText(m_nEventSelect,2,lp->m_Expression);
	
	Refresh();
	}
	m_nEventSelect=-1;
	}

}

void CConditionDlg::OnButtonConedit() 
{
	// TODO: Add your control notification handler code here
	if(m_nConSelect>=0)
	{
	CCondition *lp=m_pConditionList->m_head;
	for(int i=0;i<m_pConditionList->m_nConditionNum-m_nConSelect-1;i++,lp=lp->lpNext);
	CEditConditionDlg dlg;
	dlg.m_strConDescribe=lp->m_Describe;
	dlg.m_nConID=lp->m_nID;
	dlg.m_nOld=lp->m_nID;

	if(dlg.DoModal()==IDOK)
	{
	strcpy(lp->m_Describe,dlg.m_strConDescribe);
	lp->m_nID=dlg.m_nConID;
	m_ListCondition.DeleteItem(m_nConSelect);
	

	CString s;
	s.Empty();
	if(lp->m_nID>9)
	{
		s+=char(int(lp->m_nID/10)+48);
		s+=char(lp->m_nID%10+48);
	}
	else
		s+=char(lp->m_nID+48);
	m_ListCondition.InsertItem(m_nConSelect,s);
	m_ListCondition.SetItemText(m_nConSelect,1,lp->m_Describe);

	Refresh();
	}
	m_nConSelect=-1;
	}
}

void CConditionDlg::Refresh()
{
	CEvent *lp=m_pEventList->m_head;
	for(int i=0;i<m_pEventList->m_nEventNum;i++,lp=lp->lpNext)
		CheckCondition(lp->m_Expression,1);

	m_ListCondition.DeleteAllItems();
	m_ListEvent.DeleteAllItems();
	m_ListCondition.DeleteColumn(0);
	m_ListCondition.DeleteColumn(0);
	m_ListCondition.DeleteColumn(0);
	m_ListEvent.DeleteColumn(0);
	m_ListEvent.DeleteColumn(0);
	m_ListEvent.DeleteColumn(0);
	m_ListEvent.DeleteColumn(0);

	OnInitDialog() ;
}

void CConditionDlg::clear()
{

}
