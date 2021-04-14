
// ThreadTalkingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ThreadTalking.h"
#include "ThreadTalkingDlg.h"
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


// CThreadTalkingDlg �Ի���



CThreadTalkingDlg::CThreadTalkingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThreadTalkingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hThread = NULL;
	m_bFlagQuit = true;
	m_nCalNum = 0;
	m_hEvent = CreateEvent(0,//��ȫ����
							FALSE,//TRUE�˹��¼� FALSE�Զ��¼�
							FALSE,//���ź�FALSEE ���ź�TRYE
							0	//����
	); 
	//�����¼�--���ź�
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


// CThreadTalkingDlg ��Ϣ�������

BOOL CThreadTalkingDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CThreadTalkingDlg::OnPaint()
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
HCURSOR CThreadTalkingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//�̺߳���
DWORD WINAPI CThreadTalkingDlg::ThreadProc(_In_  LPVOID lpParameter)
{
	
	CThreadTalkingDlg *pthis = (CThreadTalkingDlg*)lpParameter;
	int nSum = 0;
	TCHAR szbuf[1024]={0};
	while (pthis->m_bFlagQuit)
	{
		//����--���¼����ź�
		WaitForSingleObject(pthis->m_hEvent,INFINITE);
		//��ʱ����Ϊ���ź�
		//ResetEvent(pthis->m_hEvent );
		//����
		nSum = (1+pthis->m_nCalNum)*pthis->m_nCalNum/2;

		_itow_s(nSum,szbuf,sizeof(szbuf)/sizeof(TCHAR),10);
		pthis->m_edttext.SetWindowTextW(szbuf);
	}
	return 0;
}

void CThreadTalkingDlg::OnBnClickedButton1()
{
	//�����߳�
	if (!m_hThread)
	{
		m_hThread = CreateThread(0,0,&ThreadProc,this,0,0);
	}
}


void CThreadTalkingDlg::OnClose()
{
	// �˳��߳�

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCalNum = 10;
}

void CThreadTalkingDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCalNum = 100;
}


void CThreadTalkingDlg::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCalNum = 1000;
}


void CThreadTalkingDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetEvent(m_hEvent);
}
