
// CodeMake.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCodeMakeApp:
// �йش����ʵ�֣������ CodeMake.cpp
//

class CCodeMakeApp : public CWinApp
{
public:
	CCodeMakeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCodeMakeApp theApp;