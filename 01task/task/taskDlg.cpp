
// taskDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "task.h"
#include "taskDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CtaskDlg �Ի���



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


// CtaskDlg ��Ϣ�������

BOOL CtaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_lstctrl.InsertColumn(0,_T("Name"),LVCFMT_LEFT,100,0);
	m_lstctrl.InsertColumn(1,_T("ThreadNum"),LVCFMT_LEFT,100,0);
	m_lstctrl.InsertColumn(2,_T("PID"),LVCFMT_LEFT,100,0);

	m_lstctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	ShowProcess();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtaskDlg::ShowProcess()
{
	//itask������Ϣ

	//1.���ϵͳ�д洢������Ϣ�ı�
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);
	if(INVALID_HANDLE_VALUE == hSnapShot)return;

	//2.������ͷ
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
		//3.������
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtaskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtaskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtaskDlg::OnBnClickedButton1()
{
	//1.��ȡ��ǰѡ����--id
	int nIndex = m_lstctrl.GetSelectionMark();
	if(-1 == nIndex)return;

	CString strProcessId = m_lstctrl.GetItemText(nIndex,2);
	//2.��ȡ������Ϣ--���
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,NULL,_wtoi(strProcessId));
	//3.��������
	if (true)
	{
		TerminateProcess(hProcess,-1);
		m_lstctrl.DeleteItem(nIndex);
	}
}
