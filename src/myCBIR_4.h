
// myCBIR_4.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmyCBIR_4App: 
// �йش����ʵ�֣������ myCBIR_4.cpp
//

class CmyCBIR_4App : public CWinApp
{
public:
	CmyCBIR_4App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmyCBIR_4App theApp;