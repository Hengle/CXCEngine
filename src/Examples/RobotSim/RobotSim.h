
// RobotSim.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRobotSimApp: 
// �йش����ʵ�֣������ RobotSim.cpp
//

class CRobotSimApp : public CWinApp
{
public:
	CRobotSimApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRobotSimApp theApp;
