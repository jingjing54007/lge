// MyEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyEditor.h"
#include "MyEditorDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEditorDlg dialog

CMyEditorDlg::CMyEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyEditorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyEditorDlg)
	m_strName = _T("");
	m_intPicID = 0;
	m_intSthID = 0;
	m_intFunction = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyEditorDlg)
	DDX_Control(pDX, IDC_FUNCTION_SPIN, m_ctrlFunSpin);
	DDX_Control(pDX, IDC_VISIBLE_CHECK, m_ctrlVisible);
	DDX_Control(pDX, IDC_ACTIVE_CHECK, m_ctrlActive);
	DDX_Control(pDX, IDC_PIC_LIST, m_ctrlPicList);
	DDX_Control(pDX, IDC_STH_LIST, m_ctrlSthList);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_PIC_ID, m_intPicID);
	DDV_MinMaxInt(pDX, m_intPicID, -1, 10000);
	DDX_Text(pDX, IDC_STH_ID, m_intSthID);
	DDV_MinMaxInt(pDX, m_intSthID, -1, 10000);
	DDX_Text(pDX, IDC_FUNCTION, m_intFunction);
	DDV_MinMaxInt(pDX, m_intFunction, 1, 10000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CMyEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_LBN_SELCHANGE(IDC_STH_LIST, OnSelchangeSthList)
	ON_BN_CLICKED(IDC_DEL_BUTTON, OnDelButton)
	ON_LBN_SELCHANGE(IDC_PIC_LIST, OnSelchangePicList)
	ON_BN_CLICKED(IDC_HELP_BUTTON, OnHelpButton)
	ON_BN_CLICKED(IDC_MODIFY_BUTTON, OnModifyButton)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SAVE, OnOK)
	ON_LBN_DBLCLK(IDC_PIC_LIST, OnDblclkPicList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEditorDlg message handlers

BOOL CMyEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	m_ctrlFunSpin.SetRange(1,10000);
	
	CThing *pt;
	CString str;
	char temp[200][20];
	int i=0,j=1,k=0;
	
	
	ifstream in;
	in.open("thlib\\object",ios::in|ios::binary);
	if (in)
	{
		m_strName="";
	    m_intPicID=-1;
	    m_intSthID=-1;
	    m_intFunction=1;
	    UpdateData(false);
		m_thingList.read(in);
		
		i=m_thingList.m_count;

	    if(i!=0)
			{
		      pt=m_thingList.m_head;
			  
		       while(j<=i)
			   {   
			
		    	k=i-j;
		    	strcpy(temp[k],pt->m_name);
				pt->m_ID=k;
			    pt=pt->lpNext;
			    j++;
			
			   }
			
		       for(k=0;k<i;k++)

	           m_ctrlSthList.InsertString(k,temp[k]);
			}
	
	}

	in.close();

	m_nameLib.read();
	
    for (i=0;i<m_nameLib.m_count;i++)
		m_ctrlPicList.InsertString(i,m_nameLib.m_name[i]);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CMyEditorDlg::OnAddButton() 
{   
	int i=0,flag;
    bool isReply=true;
	CString str;
	UpdateData();
	flag=m_ctrlSthList.GetCount();
	if(flag!=0)
	{
	while((i<flag)&&isReply)
	{   
		m_ctrlSthList.GetText(i,str);
		if(strcmp(str,m_strName)==0)
		{
			isReply=false;
			AfxMessageBox(str+"已存在!!!");
			return;
		}
		i++;
	}
	}
	if(isReply)
	{   UpdateData();
	    if(m_strName=="")
		{
			AfxMessageBox("NAME不能为空！");
			return;
		}
			strcpy(m_thing.m_name,m_strName);
		if(m_intPicID==-1)
		{
			AfxMessageBox("图片ID不能为-1,请您从图片库中选择物品图片!");
				return;
		}
		m_thing.m_picid=m_intPicID;
		m_thing.m_ID=m_thingList.m_count;
		//str.Format("%d",m_thing.m_ID);
		//AfxMessageBox(str);
		m_thing.m_function=m_intFunction;
		if(m_ctrlActive.GetCheck()==1)
		m_thing.m_active=true;
		else
			m_thing.m_active=false;
		if(m_ctrlVisible.GetCheck()==1)
         	m_thing.m_visible=true;
		else
			m_thing.m_visible=false;
		m_thingList.Add(m_thing);
		m_ctrlSthList.InsertString(-1,m_strName);
		m_strName="";
		m_intPicID=-1;
		m_intSthID=-1;
        m_intFunction=1;
		
		UpdateData(false);
	}
	
	
}





void CMyEditorDlg::OnOK() 
{if(MessageBox("是否真要保存做编辑?","警告！",
				MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON2)==IDYES)
{
	ofstream out;
	out.open("thlib\\object",ios::nocreate|ios::out|ios::binary);
	m_thingList.write(out);
	out.close();
}
if(MessageBox("是否真要退出?","警告！",
				MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON2)==IDYES)
     CDialog::OnOK();
	
}
void CMyEditorDlg::OnCancel() 
{
	if(MessageBox("是否真要放弃编辑并退出?","警告！",
				MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON2)==IDYES)
	CDialog::OnCancel();
}

void CMyEditorDlg::OnSelchangeSthList() 
{
	 CString temp;
	 int i;
	 i=m_ctrlSthList.GetCurSel(); 
	        
	   if(m_thingList.Find(i))
	   { 
         m_strName=m_thingList.m_curposi->m_name; 
		 m_intSthID=m_thingList.m_curposi->m_ID;
		 m_intPicID=m_thingList.m_curposi->m_picid;
		 if(m_thingList.m_curposi->m_active)
			 m_ctrlActive.SetCheck(1);
		 else
			 m_ctrlActive.SetCheck(0);
		 if(m_thingList.m_curposi->m_visible)
			 m_ctrlVisible.SetCheck(1);
		 else
			 m_ctrlVisible.SetCheck(0);
       
		 m_intFunction=m_thingList.m_curposi->m_function;
		 
		 char name[20]="thlib\\";
		 temp=m_nameLib.m_name[m_thingList.m_curposi->m_picid];
	strcat(name,temp);
	//strcat(name,".bmp");
	if(m_dib.m_pBMI!=NULL || m_dib.m_pDIBData!=NULL)
	{
		m_dib.m_pDIBData=NULL;
		m_dib.m_pBMI=NULL;
	}

	if(!m_dib.LoadFromFile(name))
			return;
	CDC *pDC=GetDC();
	CRect  rect;
	GetClientRect(&rect);
	m_dib.ShowDIB(pDC,10,10,rect.Width()/3-20,rect.Height()-20);
//    InvalidateRect(rect,false);
    ReleaseDC(pDC);

    UpdateData(false);
 
	 }
	   else
	   {
		   m_ctrlSthList.GetText(i,temp);
		   AfxMessageBox(temp+"未找到!!!");
	   }
}

void CMyEditorDlg::OnDelButton() 
{
	if(m_ctrlSthList.GetCurSel()==LB_ERR)
		AfxMessageBox("请选定一个你要删除的物品!!!");
	else
	{
        if(MessageBox("是否真要删除?","警告！",
				MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON2)==IDYES)
		{
       int i=0,j;
	   CThing *pt;
	   i=m_ctrlSthList.GetCurSel();
	   m_thingList.Find(i);
	   
	   m_ctrlSthList.DeleteString(i);
       
	   m_thingList.Delcur();
	   
	   j=m_thingList.m_count;
	   j=j-i;
	   if(j>0)
	   {
		pt=m_thingList.m_head;
	   for(int k=0;k<j;k++)
	   {
		   pt->m_ID=pt->m_ID-1;
		   pt=pt->lpNext;
	   }
	   }

	}
			

		   

	}


}

void CMyEditorDlg::OnSelchangePicList() 
{
	CString str;
	m_ctrlPicList.GetText(m_ctrlPicList.GetCurSel(),str);
	m_intPicID=m_ctrlPicList.GetCurSel();
	m_strName=str;
	UpdateData(false);
	char name[30]="thlib\\";
	strcat(name,str);
    //strcat(name,".bmp");
	if(m_dib.m_pBMI!=NULL || m_dib.m_pDIBData!=NULL)
	{
		m_dib.m_pDIBData=NULL;
		m_dib.m_pBMI=NULL;
	}

	if(!m_dib.LoadFromFile(name))
			return;
	CDC *pDC=GetDC();
	CRect  rect;
	GetClientRect(&rect);
	m_dib.ShowDIB(pDC,10,10,rect.Width()/3-20,rect.Height()-20);
//    InvalidateRect(rect,false);
    ReleaseDC(pDC);
    

	// TODO: Add your control notification handler code here
	
}

void CMyEditorDlg::OnHelpButton() 
{
	// TODO: Add your control notification handler code here
		CAboutDlg dlg;
		dlg.DoModal();
	
	
}



void CMyEditorDlg::OnModifyButton() 
{
      CString m_string;
      CThing *pt;
      int i;
	  if(m_ctrlSthList.GetCurSel()==LB_ERR)
	    AfxMessageBox("请选定一个你要修改的物品!!!");
	  else
		{
			if(MessageBox("是否真要更改?","警告！",
				MB_ICONWARNING+MB_YESNO+MB_DEFBUTTON2)==IDYES)
			{
			 i=m_ctrlSthList.GetCurSel();
	   	     m_thingList.Find(i);
	         pt=m_thingList.m_curposi;
	         UpdateData();
	         strcpy(pt->m_name,m_strName);
			 m_ctrlSthList.DeleteString(i);
			 m_ctrlSthList.InsertString(i,m_strName);
	         pt->m_function=m_intFunction;
             if(m_ctrlActive.GetCheck()==1)
		        pt->m_active=true;
		     else
			    pt->m_active=false;
		     if(m_ctrlVisible.GetCheck()==1)
                pt->m_visible=true;
		     else
			    pt->m_visible=false;
			}
			 
        
	}
}

HBRUSH CMyEditorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	//pDC->SetBkColor(RGB(98,91,7));
	//pDC->SetTextColor(RGB(255,255,255));
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CMyEditorDlg::OnDblclkPicList() 
{
	// TODO: Add your control notification handler code here
	int i=0,flag;
    bool isReply=true;
	CString str;
	UpdateData();
	flag=m_ctrlSthList.GetCount();
	if(flag!=0)
	{
	while((i<flag)&&isReply)
	{   
		m_ctrlSthList.GetText(i,str);
		if(strcmp(str,m_strName)==0)
		{
			isReply=false;
			AfxMessageBox(str+"已存在!!!");
			return;
		}
		i++;
	}
	}
	if(isReply)
	{  
		UpdateData();
	   	strcpy(m_thing.m_name,m_strName);
		m_thing.m_picid=m_intPicID;
		m_thing.m_ID=m_thingList.m_count;
		m_thing.m_function=m_intFunction;
		if(m_ctrlActive.GetCheck()==1)
		m_thing.m_active=true;
		else
			m_thing.m_active=false;
		if(m_ctrlVisible.GetCheck()==1)
         	m_thing.m_visible=true;
		else
			m_thing.m_visible=false;
		m_thingList.Add(m_thing);
		m_ctrlSthList.InsertString(-1,m_strName);
		m_strName="";
		m_intPicID=-1;
		m_intSthID=-1;
        m_intFunction=1;
		
		UpdateData(false);
	}
	
}
