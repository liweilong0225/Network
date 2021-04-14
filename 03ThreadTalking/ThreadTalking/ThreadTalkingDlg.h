
// ThreadTalkingDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CThreadTalkingDlg 对话框
class CThreadTalkingDlg : public CDialogEx
{
// 构造
public:
	CThreadTalkingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_THREADTALKING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
