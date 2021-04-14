
// ThreadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Thread.h"
#include "ThreadDlg.h"
#include "afxdialogex.h"

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


// CThreadDlg �Ի���



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


// CThreadDlg ��Ϣ�������

BOOL CThreadDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CThreadDlg::OnPaint()
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
HCURSOR CThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


PROCESS_INFORMATION pi;
void CThreadDlg::OnBnClickedButton1()
{
	//����+�ո�+�ļ���·����
	STARTUPINFO si = {sizeof(STARTUPINFO)};
	
	TCHAR szbuf[] = _T("C:\\Windows\\System32\\notepad.exe E:\\Visual Studio\\Network\\Thread\\1.txt");
	CreateProcess(
		NULL,//���̵�����
		szbuf,//�����в���
		NULL,//���̵İ�ȫ����
		NULL,//�̵߳İ�ȫ����
		NULL,//�̳���
		NORMAL_PRIORITY_CLASS,//�������ȼ�
		NULL,//������
		NULL,//Ŀ¼
		&si,//���̵���Ϣ
		&pi//
		);
}


void CThreadDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TerminateProcess(pi.hProcess,-1);
}




void CThreadDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SuspendThread(m_hThread);
}



void CThreadDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bFlag = false;
	if (m_hThread)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	m_progress.SetPos(0);
}
