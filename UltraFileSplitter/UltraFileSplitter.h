
// UltraFileSplitter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUltraFileSplitterApp: 
// �йش����ʵ�֣������ UltraFileSplitter.cpp
//

class CUltraFileSplitterApp : public CWinApp
{
public:
	CUltraFileSplitterApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUltraFileSplitterApp theApp;