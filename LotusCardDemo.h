// LotusCardDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CLotusCardDemoApp:
// �йش����ʵ�֣������ LotusCardDemo.cpp
//

class CLotusCardDemoApp : public CWinApp
{
public:
	CLotusCardDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLotusCardDemoApp theApp;
