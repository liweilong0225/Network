
// ThreadTalkingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ThreadTalking.h"
#include "ThreadTalkingDlg.h"
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


// CThreadTalkingDlg 对话框



CThreadTalkingDlg::CThreadTalkingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThreadTalkingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hThread = NULL;
	m_bFlagQuit = true;
	m_nCalNum = 0;
	m_hEvent = CreateEvent(0,//安全属性
							FALSE,//TRUE人工事件 FALSE自动事件
							FALSE,//无信号FALSEE 有信号TRYE
							0	//名字
	); 
	//创建事件--无信号
}

void CThreadTalkingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edttext);
}

BEGIN_MESSAGE_MAP(CThreadTalkingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CThreadTalkingDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON1, &CThreadTalkingDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO2, &CThreadTalkingDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CThreadTalkingDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON2, &CThreadTalkingDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CThreadTalkingDlg 消息处理程序

BOOL CThreadTalkingDlg::OnInitDialog()
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

void CThreadTalkingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CThreadTalkingDlg::OnPaint()
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
HCURSOR CThreadTalkingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//线程函数
DWORD WINAPI CThreadTalkingDlg::ThreadProc(_In_  LPVOID lpParameter)
{
	
	CThreadTalkingDlg *pthis = (CThreadTalkingDlg*)lpParameter;
	int nSum = 0;
	TCHAR szbuf[1024]={0};
	while (pthis->m_bFlagQuit)
	{
		//阻塞--等事件的信号
		WaitForSingleObject(pthis->m_hEvent,INFINITE);
		//将时间置为无信号
		//ResetEvent(pthis->m_hEvent );
		//计算
		nSum = (1+pthis->m_nCalNum)*pthis->m_nCalNum/2;

		_itow_s(nSum,szbuf,sizeof(szbuf)/sizeof(TCHAR),10);
		pthis->m_edttext.SetWindowTextW(szbuf);
	}
	return 0;
}

void CThreadTalkingDlg::OnBnClickedButton1()
{
	//创建线程
	if (!m_hThread)
	{
		m_hThread = CreateThread(0,0,&ThreadProc,this,0,0);
	}
}


void CThreadTalkingDlg::OnClose()
{
	// 退出线程

	m_bFlagQuit = false;

	if (m_hThread)
	{
		if ( WAIT_TIMEOUT == WaitForSingleObject(m_hThread,200))
			TerminateThread(m_hThread,-1);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	
	CDialogEx::OnClose();
}

void CThreadTalkingDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCalNum = 10;
}

void CThreadTalkingDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCalNum = 100;
}


void CThreadTalkingDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nCalNum = 1000;
}


void CThreadTalkingDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetEvent(m_hEvent);
}
