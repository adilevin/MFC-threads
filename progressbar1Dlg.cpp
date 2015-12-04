// progressbar1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "progressbar1.h"
#include "progressbar1Dlg.h"
#include ".\progressbar1dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cprogressbar1Dlg dialog



Cprogressbar1Dlg::Cprogressbar1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cprogressbar1Dlg::IDD, pParent), pt(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cprogressbar1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, p1);
	DDX_Control(pDX, IDC_PROGRESS2, p2);
}

BEGIN_MESSAGE_MAP(Cprogressbar1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ACTIVATE( )
 
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
END_MESSAGE_MAP()


// Cprogressbar1Dlg message handlers

BOOL Cprogressbar1Dlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cprogressbar1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cprogressbar1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cprogressbar1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cprogressbar1Dlg::OnBnClickedButton1()
{
	// Progress bar in main thread.
	if (p1.IsPlaying()) {
		p1.Stop(); 
	} else
		p1.Play(10,2);

	if (pt->IsPlaying()) {
		pt->Stop();
	} else
		pt->Play(10,2);
}

static void long_computation()
{
	Beep(880,30);
	int n = 15000;
	static double a = 3;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			a += j;
	Beep(920,30);
}
void Cprogressbar1Dlg::OnBnClickedButton2()
{
	long_computation();
}

void Cprogressbar1Dlg::OnDestroy()
{
	if (pt) {
		pt->EndThread();
		pt = NULL;
	}
	CDialog::OnDestroy();
}

DWORD WINAPI thread_func(PVOID param)
{
	long_computation();
	return 0;
}

void Cprogressbar1Dlg::OnBnClickedButton3()
{
	DWORD tid;
	HANDLE h = CreateThread(NULL,0,thread_func,0,0,&tid);
	CloseHandle(h);
}


void Cprogressbar1Dlg::OnActivate( UINT, CWnd*, BOOL )
{
	// This does not work well if put inside OnInitDialog (which is called before all controls in the
	// dialog are ready). OnActivate is called later.
	if (!pt) {
		pt = new CProgressThread(&p2);
		pt->CreateThread();
	}
}