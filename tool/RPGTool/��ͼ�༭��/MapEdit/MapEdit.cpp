// MapEdit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MapEdit.h"

#include "MainFrm.h"
#include "MapEditDoc.h"
#include "MapEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapEditApp

BEGIN_MESSAGE_MAP(CMapEditApp, CWinApp)
	//{{AFX_MSG_MAP(CMapEditApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapEditApp construction

CMapEditApp::CMapEditApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMapEditApp object

CMapEditApp theApp;
int npcstate,npcstoptime,m_x,m_y,m_qiehuancode,m_save;
float	m_zoomout,m_zoomin;
BOOL m_modeltest;
//CDlgSingleContent m_DlgSingleState;

/////////////////////////////////////////////////////////////////////////////
// CMapEditApp initialization

BOOL CMapEditApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMapEditDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMapEditView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CListBox	m_listDevcaps;
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
	DDX_Control(pDX, IDC_SYSDEVICE, m_listDevcaps);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMapEditApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();

}

/////////////////////////////////////////////////////////////////////////////
// CMapEditApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CClientDC dcDev(this);
	CString display;
	
	TCHAR szBuffer[256];
	DWORD dwSize=256;
	GetComputerName(szBuffer,&dwSize);
	display.Format("Computer Name: %s",szBuffer);
	m_listDevcaps.AddString(display);
	MEMORYSTATUS mem_stat;
	GlobalMemoryStatus(&mem_stat);
	display.Format("Total Memory:  %ld KB",mem_stat.dwTotalPhys/1024);
	m_listDevcaps.AddString(display);
	display.Format("Free Memory:   %ld KB",mem_stat.dwAvailPhys/1024);
	m_listDevcaps.AddString(display);
	display.Format("Load Memory:   %ld KB",mem_stat.dwMemoryLoad);
	m_listDevcaps.AddString(display);
	display.Format("- - - - - - - - - - - - - - ");
	m_listDevcaps.AddString(display);
	display.Format("Horizontal Resolution: %d pixels",dcDev.GetDeviceCaps(HORZRES));
	m_listDevcaps.AddString(display);
	display.Format("Vertial Resolution: %d pixels",dcDev.GetDeviceCaps(VERTRES));
	m_listDevcaps.AddString(display);
	display.Format("Supported Colors: %ld colors",dcDev.GetDeviceCaps(COLORRES));
	m_listDevcaps.AddString(display);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


