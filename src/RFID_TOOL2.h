#ifndef _INCLUDE_RFIDTOOL2_H_ 
#define _INCLUDE_RFIDTOOL2_H_
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

class CRFID_TOOL2App : public CWinApp
{
public:
	CRFID_TOOL2App();
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
extern CRFID_TOOL2App theApp;

#endif