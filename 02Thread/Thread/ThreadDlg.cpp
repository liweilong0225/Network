
// ThreadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Thread.h"
#include "ThreadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CThreadDlg 对话框



CThreadDlg::CThreadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThreadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hThread = NULL;
	m_bFlag = true;
}

void CThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS2, m_progress);
}

BEGIN_MESSAGE_MAP(CThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CThreadDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CThreadDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CThreadDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CThreadDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CThreadDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CThreadDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CThreadDlg 消息处理程序

BOOL CThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CThreadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


PROCESS_INFORMATION pi;
void CThreadDlg::OnBnClickedButton1()
{
	//命令+空格+文件（路径）
	STARTUPINFO si = {sizeof(STARTUPINFO)};
	
	TCHAR szbuf[] = _T("C:\\Windows\\System32\\notepad.exe E:\\Visual Studio\\Network\\Thread\\1.txt");
	CreateProcess(
		NULL,//进程的名称
		szbuf,//命令行参数
		NULL,//进程的安全属性
		NULL,//线程的安全属性
		NULL,//继承性
		NORMAL_PRIORITY_CLASS,//正常优先级
		NULL,//环境块
		NULL,//目录
		&si,//进程的信息
		&pi//
		);
}


void CThreadDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	TerminateProcess(pi.hProcess,-1);
}




void CThreadDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//CreateThread(NULL,0,&ThreadProc,0,0,0);
}

DWORD WINAPI ThreadProc( _In_  LPVOID lpParameter)
{
	CThreadDlg *pthis = (CThreadDlg*)lpParameter;
	while(pthis->m_bFlag)
	{
		pthis->m_progress.StepIt();
		Sleep(500);
	}
	return 0;
}
void CThreadDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_hThread)
	{
		m_bFlag = true;
		m_hThread =  CreateThread(NULL,0,&ThreadProc,this,0,0);
	}
	else
		ResumeThread(m_hThread);
}


void CThreadDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	SuspendThread(m_hThread);
}



void CThreadDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFlag = false;
	if (m_hThread)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	m_progress.SetPos(0);
}
