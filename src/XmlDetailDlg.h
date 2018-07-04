#ifndef _INCLUDE_XMLDETAILDLG_H_ 
#define _INCLUDE_XMLDETAILDLG_H_

#pragma once
#include "afxwin.h"
#include "tinyxml2.h"
#include "tools.h"

#define IDC_BUTTON 999

#define TYPE_CHECKBOX 0
#define TYPE_COMBOBOX 1
#define TYPE_EDIT 2
#define TYPE_BROWSE 3


class CXmlDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CXmlDetailDlg)

public:
	CXmlDetailDlg(CWnd* pParent = NULL);  
	virtual ~CXmlDetailDlg();
	enum { IDD = IDD_XML_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_title_text;
	CFont *font, *subfont;
	int items_num = 0;
	int items_id[20];
	int items_type[20];
	int m_xmldetail;
	CString items_uniqueId[20];
	CString items_value[20][2];
	CString items_res[20];
	CString action;

	int CreateButtom(tinyxml2::XMLElement *element, int top);
	int CreateCheckbox(tinyxml2::XMLElement *element, int top);
	int CreateComboBox(tinyxml2::XMLElement *element, int top);
	int CreateStatic(tinyxml2::XMLElement *element, int top);
	int CreateEdit(tinyxml2::XMLElement *element, int top);
	int CreateBrowse(tinyxml2::XMLElement *element, int top);
	
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnButton();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	void uniqueId_save(CString uniqueId, int id, int type, CString value1, CString value2);
	void SetHeadText(CString str);
};

#endif