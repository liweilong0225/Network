
// ThreadTalking.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CThreadTalkingApp:
// �йش����ʵ�֣������ ThreadTalking.cpp
//

class CThreadTalkingApp : public CWinApp
{
public:
	CThreadTalkingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CThreadTalkingApp theApp;