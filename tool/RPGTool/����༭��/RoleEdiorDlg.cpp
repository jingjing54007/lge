// RoleEdiorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoleEdior.h"
#include "RoleEdiorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CAnimatorDlg* g_pCAnimatorDlg = NULL;

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
	virtual BOOL OnInitDialog();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoleEdiorDlg dialog

CRoleEdiorDlg::CRoleEdiorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoleEdiorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoleEdiorDlg)
	m_Def = 0;
	m_Exp = 0;
	m_ID = 0;
	m_Level = 0;
	m_Life = 0;
	m_Name = _T("");
	m_Speed = 0;
	m_Attack = 0;
	m_Function = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pNpcList = NULL;
	strCurrPathName.Empty();
	strCurrFileName.Empty();
	m_Namelib.read();
	IsMod = false;
}

void CRoleEdiorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoleEdiorDlg)
	DDX_Control(pDX, IDC_CHECK_ANI, m_Ani);
	DDX_Control(pDX, IDC_COMBO_PIC, m_Pic);
	DDX_Control(pDX, IDC_COMBO_VIEWPORT, m_Viewport);
	DDX_Control(pDX, IDC_COMBO_STATUS, m_Status);
	DDX_Control(pDX, IDC_SPIN7, m_Spin7);
	DDX_Control(pDX, IDC_SPIN6, m_Spin6);
	DDX_Control(pDX, IDC_SPIN5, m_Spin5);
	DDX_Control(pDX, IDC_SPIN4, m_Spin4);
	DDX_Control(pDX, IDC_SPIN3, m_Spin3);
	DDX_Control(pDX, IDC_SPIN2, m_Spin2);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_LISTVIEW, m_ListView);
	DDX_Text(pDX, IDC_EDIT_DEF, m_Def);
	DDX_Text(pDX, IDC_EDIT_EXP, m_Exp);
	DDX_Text(pDX, IDC_EDIT_ID, m_ID);
	DDX_Text(pDX, IDC_EDIT_LEVEL, m_Level);
	DDX_Text(pDX, IDC_EDIT_LIFE, m_Life);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_Speed);
	DDX_Text(pDX, IDC_EDIT_ATTACK, m_Attack);
	DDX_Text(pDX, IDC_EDIT_FUNCTION, m_Function);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRoleEdiorDlg, CDialog)
	//{{AFX_MSG_MAP(CRoleEdiorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_APPABOUT, OnAppAbout)
	ON_COMMAND(IDM_FILEOPEN, OnFileOpen)
	ON_COMMAND(IDM_FILENEW, OnFileNew)
	ON_COMMAND(IDM_FILESAVE, OnFileSave)
	ON_COMMAND(IDM_CHANEW, OnChaNew)
	ON_LBN_SELCHANGE(IDC_LISTVIEW, OnSelchangeListview)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	ON_CBN_SELCHANGE(IDC_COMBO_PIC, OnSelchangeComboPic)
	ON_CBN_SELCHANGE(IDC_COMBO_STATUS, OnSelchangeComboStatusViewport)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_CHECK_ANI, OnCheckAni)
	ON_COMMAND(IDM_CHADEL, OnChaDel)
	ON_EN_CHANGE(IDC_EDIT_ATTACK, OnChangeData)
	ON_CBN_SELCHANGE(IDC_COMBO_VIEWPORT, OnSelchangeComboStatusViewport)
	ON_EN_CHANGE(IDC_EDIT_DEF, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_EXP, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_FUNCTION, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_LEVEL, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_LIFE, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_MONEY, OnChangeData)
	ON_EN_CHANGE(IDC_EDIT_SPEED, OnChangeData)
	ON_BN_CLICKED(IDC_BUTTON_FOLLOW, OnButtonFollow)
	//}}AFX_MSG_MAP
  ON_COMMAND(IDM_FILECLOSE, OnFileclose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoleEdiorDlg message handlers

BOOL CRoleEdiorDlg::OnInitDialog()
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

	CString str, str1;
	str.LoadString(IDS_APPTITLE);
	str1.LoadString(IDS_VERSION);
	str = str + " " + str1;
	AfxGetMainWnd()->SetWindowText(str);

	GetDlgItem(IDC_STATIC_NOTE)->SetWindowText("-武汉理工·方亮 (C) 2001- (需配合其他编辑器使用)");

	m_Spin1.SetRange(0,999);
	m_Spin2.SetRange(0,999);
	m_Spin3.SetRange32(0,99999999);
	m_Spin4.SetRange(0,999);
	m_Spin5.SetRange(0,999);
	m_Spin6.SetRange32(0,99999999);
	m_Spin7.SetRange(0,999);

	m_Status.InsertString(0, "站立");
	m_Status.InsertString(1, "走动");
	m_Status.InsertString(2, "跑动");
	m_Status.InsertString(3, "战斗");
	m_Status.InsertString(4, "死亡");
	m_Status.SetCurSel(0);

	m_Viewport.InsertString(0, "斜45度");
	m_Viewport.InsertString(1, "正20度");
	m_Viewport.SetCurSel(0);
	m_Ani.SetCheck(1);

	for (int i=0; i<m_Namelib.m_count; i++)
	{
		str.Format("%s", m_Namelib.m_name[i]);
		str.Delete(str.GetLength()-4, 4);
		m_Pic.InsertString(i, str);
	}

	UpdateUI();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRoleEdiorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRoleEdiorDlg::OnPaint() 
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
HCURSOR CRoleEdiorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRoleEdiorDlg::OnClose() 
// Modified by YKJ
{
	if(!AskSave()) return;

  FileClose();
  //GetDlgItem(IDC_STATIC_NOTE)->SetWindowText("-武汉理工·方亮 (C) 2001- (需配合其他编辑器使用)");
  UpdateUI();

	CDialog::OnClose();
}

void CRoleEdiorDlg::OnAppAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CRoleEdiorDlg::OnFileOpen() 
{
	if(!AskSave()) return;
	if(m_pNpcList != NULL) FileClose();
	m_pNpcList = new CNpcList;

	static char BASED_CODE szFilter[] = "角色文件  (*.cha)|*.cha|所有文件  (*.*)|*.*||";
 	CFileDialog dlg(TRUE, NULL, NULL, OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, szFilter);
	if(dlg.DoModal() == IDOK)
	{
		strCurrPathName = dlg.GetPathName();
		strCurrFileName = dlg.GetFileName();
	
		ifstream in;
		in.open(strCurrPathName, ios::nocreate | ios::in | ios::binary);
		m_pNpcList->read(in);
		in.close();
		
		int id = 0;
		CString str;
		m_pNpcList->m_curposi = m_pNpcList->m_head;
		while(m_pNpcList->m_curposi != NULL)
		{
			m_pNpcList->m_curposi->m_ID = id++;
			str.Format("%s",m_pNpcList->m_curposi->m_name);
			m_ListView.InsertString(-1, str);
			m_pNpcList->Next();
		}
		if(m_pNpcList->m_head != NULL)
		{
			m_pNpcList->m_curposi = m_pNpcList->m_head;
			m_ListView.SetCurSel(0);
			m_Attack = m_pNpcList->m_curposi->m_attack;
			m_Def    = m_pNpcList->m_curposi->m_def;
			m_Exp    = m_pNpcList->m_curposi->m_exp;
			m_ID     = m_pNpcList->m_curposi->m_ID;
			m_Level  = m_pNpcList->m_curposi->m_level;
			m_Life   = m_pNpcList->m_curposi->m_life;
			m_Speed  = m_pNpcList->m_curposi->m_speed;
			m_Function = m_pNpcList->m_curposi->m_function;
			m_Name.Format("%s", m_pNpcList->m_curposi->m_name);
			for(int i = 0; i < 10; i++)
			{
				m_PicID[i] = m_pNpcList->m_curposi->m_picid[i];
			}
			UpdateData(false);
			OnSelchangeComboStatusViewport();
		}
	}
	UpdateUI();
	DataSaved();
}

void CRoleEdiorDlg::OnFileNew()
{
	if(!AskSave()) return;
	if(m_pNpcList != NULL) FileClose();
	m_pNpcList = new CNpcList;

	strCurrFileName = "未命名";
	strCurrPathName = ".\\未命名";
	UpdateUI();
	DataSaved();
}

void CRoleEdiorDlg::OnFileSave()
{
	if(m_pNpcList == NULL) return;
	if(strCurrFileName == "未命名")
	{
		static char BASED_CODE szFilter[] = "角色文件  (*.cha)|*.cha|所有文件  (*.*)|*.*||";
 		CFileDialog dlg(FALSE, "cha", strCurrPathName, OFN_ENABLESIZING | OFN_OVERWRITEPROMPT, szFilter);
		if(dlg.DoModal() == IDOK)
		{
			strCurrPathName = dlg.GetPathName();
			strCurrFileName = dlg.GetFileName();
			if(dlg.GetFileExt().IsEmpty()) strCurrPathName += ".cha";
		}
		else return;
	}
	
	OnChaSave();
	ofstream out;
	out.open(strCurrPathName, ios::out | ios::binary);
	m_pNpcList->write(out);
	out.close();
	DataSaved();
}

void CRoleEdiorDlg::OnChaNew() 
{
	if(m_pNpcList == NULL) return;
	
	m_Npc.m_ID = GetID();
	lstrcpy(m_Npc.m_name, "未命名");
	m_Npc.m_active = false;
	m_Npc.m_visible = true;
	m_Npc.m_function = -1;
	for(int i=0;i<10;i++)
	{
		m_Npc.m_picid[i]=-1;
	}
	m_Npc.m_attack = 0;
	m_Npc.m_def    = 0;
	m_Npc.m_exp    = 0;
	m_Npc.m_level  = 0;
	m_Npc.m_life   = 0;
	m_Npc.m_speed  = 0;

	m_Npc.m_sight = 0;
	m_Npc.m_radius = 0;

	if(m_pNpcList->m_head == NULL)
	{
		m_Name = m_Npc.m_name;
		for(i=0; i<10; i++)
		{	
			m_PicID[i] = -1;
		}
		UpdateData(false);
	}
	else
	{
		//OnChaSave();
	}	

	m_pNpcList->Add(m_Npc);

	m_ListView.InsertString(-1, m_Npc.m_name);
	m_ListView.SetCurSel(m_Npc.m_ID);
	m_Pic.SetCurSel(-1);

	OnSelchangeListview();
	DataMod();
}

int CRoleEdiorDlg::GetID()
{
	return m_pNpcList->m_count;
}

void CRoleEdiorDlg::OnSelchangeListview()
{
	if(m_pNpcList == NULL) return;
	OnChaSave();
	int m = m_ListView.GetCurSel();
	m_pNpcList->m_curposi = m_pNpcList->m_head;
	while(m_pNpcList->m_curposi->m_ID != m)
	{
		m_pNpcList->Next();
	}	
	m_Attack = m_pNpcList->m_curposi->m_attack;
	m_Def    = m_pNpcList->m_curposi->m_def;
	m_Exp    = m_pNpcList->m_curposi->m_exp;
	m_ID     = m_pNpcList->m_curposi->m_ID;
	m_Level  = m_pNpcList->m_curposi->m_level;
	m_Life   = m_pNpcList->m_curposi->m_life;
	m_Speed  = m_pNpcList->m_curposi->m_speed;
	m_Function = m_pNpcList->m_curposi->m_function;
	m_Name.Format("%s", m_pNpcList->m_curposi->m_name);
	for(int i = 0; i < 10; i++)
	{
		m_PicID[i] = m_pNpcList->m_curposi->m_picid[i];
	}
	UpdateData(false);
	OnSelchangeComboStatusViewport();
}

void CRoleEdiorDlg::OnChangeEditName() 
{
	int m = m_ListView.GetCurSel();
	if (m<0) return;
	UpdateData(true);
	m_ListView.DeleteString(m);
	m_ListView.InsertString(m, m_Name);
	m_ListView.SetCurSel(m);
	DataMod();
}

void CRoleEdiorDlg::OnChaSave()
{
	UpdateData(true);
	m_pNpcList->m_curposi = m_pNpcList->m_head;
	while(m_pNpcList->m_curposi->m_ID != m_ID)
	{
		m_pNpcList->Next();
	}
	m_pNpcList->m_curposi->m_attack	= m_Attack;
	m_pNpcList->m_curposi->m_def	= m_Def;
	m_pNpcList->m_curposi->m_exp	= m_Exp;
	m_pNpcList->m_curposi->m_ID		= m_ID;
	m_pNpcList->m_curposi->m_level	= m_Level;
	m_pNpcList->m_curposi->m_life	= m_Life;
	m_pNpcList->m_curposi->m_speed	= m_Speed;
	m_pNpcList->m_curposi->m_function = m_Function;
	strcpy(m_pNpcList->m_curposi->m_name, m_Name.operator LPCTSTR());
	for(int i = 0; i < 10; i++)
	{
		m_pNpcList->m_curposi->m_picid[i] = m_PicID[i];
	}
}

void CRoleEdiorDlg::OnSelchangeComboPic()
{
	if(m_pNpcList == NULL) 
	{
		m_Pic.SetCurSel(-1);
		return;
	}
	int nStatus = m_Status.GetCurSel();
	int nViewport = m_Viewport.GetCurSel();
	int nStatusCount = m_Status.GetCount();
	int nIndex = nViewport * nStatusCount + nStatus;

	m_PicID[nIndex] = m_Pic.GetCurSel();

	if(g_pCAnimatorDlg != NULL)
	{
		g_pCAnimatorDlg->ReleaseAll();
	}
	if(m_PicID[nIndex] > 0 && m_Ani.GetCheck())
	{
		CString str;
		str.Format("%s", m_Namelib.m_name[m_PicID[nIndex]]);
		g_pCAnimatorDlg = new CAnimatorDlg(str, this);
	}
	DataMod();
}

void CRoleEdiorDlg::OnSelchangeComboStatusViewport() 
{
	if(m_pNpcList == NULL) 
	{
		m_Status.SetCurSel(0);
		m_Viewport.SetCurSel(0);
		return;
	}
	int nStatus = m_Status.GetCurSel();
	int nViewport = m_Viewport.GetCurSel();
	int nStatusCount = m_Status.GetCount();
	int nIndex = nViewport * nStatusCount + nStatus;
	
	m_Pic.SetCurSel(m_PicID[nIndex]);


	if(g_pCAnimatorDlg != NULL)
	{
		g_pCAnimatorDlg->ReleaseAll();
	}
	if(m_PicID[nIndex] > 0 && m_Ani.GetCheck())
	{
		CString str;
		str.Format("%s", m_Namelib.m_name[m_PicID[nIndex]]);
		g_pCAnimatorDlg = new CAnimatorDlg(str, this);
	}
}

void CRoleEdiorDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	if(g_pCAnimatorDlg != NULL)
	{
		g_pCAnimatorDlg->SetAnimatorWindowPlacement();
	}
}



void CRoleEdiorDlg::OnCheckAni() 
{
	if(m_pNpcList == NULL) return;
	if(!m_Ani.GetCheck())
	{
		if(g_pCAnimatorDlg != NULL)
		{
			g_pCAnimatorDlg->ReleaseAll();
		}
		GetDlgItem(IDC_BUTTON_FOLLOW)->ShowWindow(SW_HIDE);
	}
	else
	{
		if(m_pNpcList->m_count != 0)
			OnSelchangeComboStatusViewport();
		GetDlgItem(IDC_BUTTON_FOLLOW)->ShowWindow(SW_SHOW);
	}
}

void CRoleEdiorDlg::UpdateUI()
{
	CMenu* mmenu = GetMenu();
	CMenu* submenu = NULL;
	if(m_pNpcList == NULL)
	{
		submenu = mmenu->GetSubMenu(0);
		submenu->EnableMenuItem(IDM_FILECLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		submenu->EnableMenuItem(IDM_FILESAVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

		submenu = mmenu->GetSubMenu(1);
		submenu->EnableMenuItem(IDM_CHANEW, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		submenu->EnableMenuItem(IDM_CHADEL, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

		GetDlgItem(IDC_EDIT_ID)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_NAME)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_ATTACK)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_DEF)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_EXP)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_LEVEL)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_LIFE)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_MONEY)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_SPEED)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_FUNCTION)->EnableWindow(false);
		GetDlgItem(IDC_LISTVIEW)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_STATUS)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_VIEWPORT)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_PIC)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_FOLLOW)->EnableWindow(false);
		GetDlgItem(IDC_CHECK_ANI)->EnableWindow(false);
	}
	else
	{
		submenu = mmenu->GetSubMenu(0);
		submenu->EnableMenuItem(IDM_FILECLOSE, MF_BYCOMMAND | MF_ENABLED);
		submenu->EnableMenuItem(IDM_FILESAVE, MF_BYCOMMAND | MF_ENABLED);

		submenu = mmenu->GetSubMenu(1);
		submenu->EnableMenuItem(IDM_CHANEW, MF_BYCOMMAND | MF_ENABLED);
		submenu->EnableMenuItem(IDM_CHADEL, MF_BYCOMMAND | MF_ENABLED);

		GetDlgItem(IDC_EDIT_ID)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_NAME)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_ATTACK)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_DEF)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_EXP)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_LEVEL)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_LIFE)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_MONEY)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_SPEED)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_FUNCTION)->EnableWindow(true);
		GetDlgItem(IDC_LISTVIEW)->EnableWindow(true);
		GetDlgItem(IDC_COMBO_STATUS)->EnableWindow(true);
		GetDlgItem(IDC_COMBO_VIEWPORT)->EnableWindow(true);
		GetDlgItem(IDC_COMBO_PIC)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_FOLLOW)->EnableWindow(true);
		GetDlgItem(IDC_CHECK_ANI)->EnableWindow(true);
	}
}

void CRoleEdiorDlg::OnChaDel() 
{
	if(m_pNpcList == NULL) return;
	if(m_ListView.GetCount() <= 0) return;	
	UpdateData(true);
	int id = m_ID;
	m_ListView.DeleteString(m_ListView.GetCurSel());

	m_pNpcList->m_preposi = m_pNpcList->m_curposi = m_pNpcList->m_head;
	while(m_pNpcList->m_curposi->m_ID != id)
	{
		m_pNpcList->m_preposi = m_pNpcList->m_curposi;
		m_pNpcList->Next();
	}
	m_pNpcList->Delcur();
	
	id =0;
	m_pNpcList->m_curposi = m_pNpcList->m_head;
	while(m_pNpcList->m_curposi != NULL)
	{
		m_pNpcList->m_curposi->m_ID = id++;
		m_pNpcList->Next();
	}
	if(m_ListView.GetCount() > 0)
	{
		m_ListView.SetCurSel(0);
		
		m_pNpcList->m_curposi = m_pNpcList->m_head;
		while(m_pNpcList->m_curposi->m_ID != 0)
		{
			m_pNpcList->Next();
		}	
		m_Attack = m_pNpcList->m_curposi->m_attack;
		m_Def    = m_pNpcList->m_curposi->m_def;
		m_Exp    = m_pNpcList->m_curposi->m_exp;
		m_ID     = m_pNpcList->m_curposi->m_ID;
		m_Level  = m_pNpcList->m_curposi->m_level;
		m_Life   = m_pNpcList->m_curposi->m_life;
		m_Speed  = m_pNpcList->m_curposi->m_speed;
		m_Function = m_pNpcList->m_curposi->m_function;
		m_Name.Format("%s", m_pNpcList->m_curposi->m_name);
		for(int i = 0; i < 10; i++)
		{
			m_PicID[i] = m_pNpcList->m_curposi->m_picid[i];
		}
		UpdateData(false);
		OnSelchangeComboStatusViewport();
	}
	DataMod();
}

void CRoleEdiorDlg::DataMod()
{
	if(!strCurrFileName.IsEmpty())
	{
		IsMod = true;
		CString str, str1;
		str = " [" + strCurrFileName + " *]";
		str1.LoadString(IDS_AUTHOR);
		str = str + "    -" + str1;
		str1.LoadString(IDS_COPYRIGHT);
	    str = str + " " + str1 + "-";
		GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(str);
	}
}

void CRoleEdiorDlg::DataSaved()
{
	if(!strCurrFileName.IsEmpty())
	{
		IsMod = false;
		CString str, str1;
		str = " [" + strCurrFileName + "]";
		str1.LoadString(IDS_AUTHOR);
		str = str + "    -" + str1;
		str1.LoadString(IDS_COPYRIGHT);
	    str = str + " " + str1 + "-";
		GetDlgItem(IDC_STATIC_NOTE)->SetWindowText(str);
	}
}

void CRoleEdiorDlg::OnChangeData() 
{
	DataMod();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strTitle,temp;
	temp.LoadString(IDS_APPTITLE);
	strTitle="关于 "+temp;
	SetWindowText(strTitle);

	strTitle.LoadString(IDS_APPTITLE);
	temp.LoadString(IDS_VERSION);
	strTitle=strTitle+" "+temp;
	GetDlgItem(IDC_STATIC1)->SetWindowText(strTitle);

	strTitle.LoadString(IDS_AUTHOR);
	temp.LoadString(IDS_COPYRIGHT);
	strTitle=strTitle+" "+temp;
	GetDlgItem(IDC_STATIC2)->SetWindowText(strTitle);	
	return TRUE;  
}

BOOL CRoleEdiorDlg::AskSave()
{
	if(IsMod)
	{
		CString str, strtitle;
		str = "是否保存对文件 ";
		str += strCurrFileName;
		str += " * 修改？";
		strtitle.LoadString(IDS_APPTITLE);
		switch(MessageBox(str, strtitle, MB_YESNOCANCEL | MB_ICONWARNING))
		{
			case IDCANCEL:
				return false;
				break;
			case IDYES:
				OnFileSave();
			case IDNO:
				break;
		}
	} 
	return true;
}

void CRoleEdiorDlg::FileClose()
{
	if(m_pNpcList != NULL)
 	{
 		delete	m_pNpcList;
 		m_pNpcList = NULL;
 	}
	while(m_ListView.GetCount())
 	{
 		m_ListView.DeleteString(0);
 	}
 	strCurrFileName.Empty();
 	strCurrPathName.Empty();
	IsMod = false;
	ClearAll();
}

void CRoleEdiorDlg::ClearAll()
{
	m_Attack  = 0;
	m_Def     = 0;
	m_Exp     = 0;
	m_ID      = 0;
	m_Level   = 0;
	m_Life    = 0;
	m_Speed   = 0;
	m_Function = -1;
	m_Name.Empty();
	for(int i = 0; i < 10; i++)
	{
		m_PicID[i] = -1;
	}
	UpdateData(false);
}

void CRoleEdiorDlg::OnButtonFollow() 
{
	if(g_pCAnimatorDlg != NULL)
	{
		g_pCAnimatorDlg->IsMoved = false;
		g_pCAnimatorDlg->SetAnimatorWindowPlacement();
	}
	GetDlgItem(IDC_BUTTON_DEFAULT)->SetFocus();
}

void CRoleEdiorDlg::OnFileclose()
{
	if(!AskSave()) m_bDoClose = false;
  else{
	  FileClose();
	  GetDlgItem(IDC_STATIC_NOTE)->SetWindowText("-武汉理工·方亮 (C) 2001- (需配合其他编辑器使用)");
	  UpdateUI();
	  m_bDoClose = true;
  }
}
