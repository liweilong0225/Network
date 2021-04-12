
// taskDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "task.h"
#include "taskDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

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


// CtaskDlg 对话框



CtaskDlg::CtaskDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtaskDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstctrl);
}

BEGIN_MESSAGE_MAP(CtaskDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtaskDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CtaskDlg 消息处理程序

BOOL CtaskDlg::OnInitDialog()
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
	m_lstctrl.InsertColumn(0,_T("Name"),LVCFMT_LEFT,100,0);
	m_lstctrl.InsertColumn(1,_T("ThreadNum"),LVCFMT_LEFT,100,0);
	m_lstctrl.InsertColumn(2,_T("PID"),LVCFMT_LEFT,100,0);

	m_lstctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	ShowProcess();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtaskDlg::ShowProcess()
{
	//itask进程信息

	//1.获得系统中存储进程信息的表
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);
	if(INVALID_HANDLE_VALUE == hSnapShot)return;

	//2.遍历表头
	PROCESSENTRY32 pe = {sizeof(PROCESSENTRY32)};
	BOOL bflag = Process32First(hSnapShot,&pe);
	TCHAR szbuf[100] = {0};
	while (bflag)
	{
		m_lstctrl.InsertItem(0,pe.szExeFile);
		_itow_s(pe.cntThreads,szbuf,sizeof(szbuf)/sizeof(TCHAR),10);
		m_lstctrl.SetItemText(0,1,szbuf);
		_itow_s(pe.th32ProcessID,szbuf,sizeof(szbuf)/sizeof(TCHAR),10);
		m_lstctrl.SetItemText(0,2,szbuf);
		//3.遍历表
		bflag = Process32Next(hSnapShot,&pe);
	}
}
void CtaskDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtaskDlg::OnPaint()
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
HCURSOR CtaskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtaskDlg::OnBnClickedButton1()
{
	//1.获取当前选中项--id
	int nIndex = m_lstctrl.GetSelectionMark();
	if(-1 == nIndex)return;

	CString strProcessId = m_lstctrl.GetItemText(nIndex,2);
	//2.获取进程信息--句柄
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,NULL,_wtoi(strProcessId));
	//3.结束进程
	if (true)
	{
		TerminateProcess(hProcess,-1);
		m_lstctrl.DeleteItem(nIndex);
	}
}
