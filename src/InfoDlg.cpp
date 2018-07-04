
#include "stdafx.h"
#include "RFID_TOOL2.h"
#include "InfoDlg.h"
#include "afxdialogex.h"



IMPLEMENT_DYNAMIC(CInfoDlg, CDialogEx)

CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInfoDlg::IDD, pParent)
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_info);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont *font = new CFont;
	font->CreateFont(15, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		1, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		VARIABLE_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("Microsoft JhengHei UI")); // lpszFac 

	GetDlgItem(IDC_EDIT1)->SetFont(font);

	CString info = _T("RFID_TOOL2 Client By Rocuku Version 1.0 \r\n\
Set correct COM port number.\r\n");

	m_info.SetWindowText(info);
	return TRUE;
}
