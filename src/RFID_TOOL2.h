#ifndef _INCLUDE_RFIDTOOL2_H_ 
#define _INCLUDE_RFIDTOOL2_H_
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

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