#ifndef _INCLUDE_INFODLG_H_ 
#define _INCLUDE_INFODLG_H_
#include "afxwin.h"

#pragma once
class CInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	CInfoDlg(CWnd* pParent = NULL);  
	virtual ~CInfoDlg();
	enum { IDD = IDD_INFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_info;
};

#endif