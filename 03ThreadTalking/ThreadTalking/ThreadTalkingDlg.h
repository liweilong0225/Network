
// ThreadTalkingDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CThreadTalkingDlg �Ի���
class CThreadTalkingDlg : public CDialogEx
{
// ����
public:
	CThreadTalkingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_THREADTALKING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	static DWORD WINAPI ThreadProc(_In_  LPVOID lpParameter);
	HANDLE m_hThread;
	bool m_bFlagQuit;

	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();

	int m_nCalNum;
	CEdit m_edttext;
	HANDLE m_hEvent;
	afx_msg void OnBnClickedButton2();
};
