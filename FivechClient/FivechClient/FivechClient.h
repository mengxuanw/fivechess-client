
// FivechClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFivechClientApp:
// �йش����ʵ�֣������ FivechClient.cpp
//

class CFivechClientApp : public CWinApp
{
public:
	CFivechClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFivechClientApp theApp;