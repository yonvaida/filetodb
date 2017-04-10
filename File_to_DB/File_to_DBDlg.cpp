
// File_to_DBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "File_to_DB.h"
#include "File_to_DBDlg.h"
#include "afxdialogex.h"
#include "VALUES.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFile_to_DBDlg dialog



CFile_to_DBDlg::CFile_to_DBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILE_TO_DB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFile_to_DBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFile_to_DBDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CFile_to_DBDlg::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CFile_to_DBDlg::OnBnClickedButtonInsert)
END_MESSAGE_MAP()


// CFile_to_DBDlg message handlers

BOOL CFile_to_DBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFile_to_DBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFile_to_DBDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFile_to_DBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFile_to_DBDlg::OnBnClickedButtonBrowse()
{
	CFileDialog fileDlg(true);
	fileDlg.DoModal();
	SetDlgItemText(IDC_EDIT_FILE_PATH, fileDlg.GetPathName());
}

void CFile_to_DBDlg::OnBnClickedButtonInsert()
{
	CVALUES db(NULL);
	CString mFileName = "";

	GetDlgItemText(IDC_EDIT_FILE_PATH, mFileName);

	db.Open();

	db.AddNew();
	UpdateData(TRUE);

	db.m_Text = mFileName;

	CFile file;
	if (file.Open(mFileName, CFile::modeRead, NULL))
	{

		db.m_binFile.m_hData = GlobalAlloc(GMEM_MOVEABLE, file.GetLength());
		LPVOID ptr = GlobalLock(db.m_binFile.m_hData);

		if (ptr != NULL)
			file.Read(ptr, file.GetLength());
		db.m_binFile.m_dwDataLength = file.GetLength();
		db.SetFieldDirty(&db.m_binFile, TRUE);
		db.SetFieldNull(&db.m_binFile, FALSE);

		db.Update();
		
		GlobalUnlock(db.m_binFile.m_hData);

		GlobalFree(db.m_binFile.m_hData);
		file.Close();
	}

}
