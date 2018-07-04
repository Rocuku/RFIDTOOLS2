#ifndef _INCLUDE_RFIDTOOL2DLG_H_ 
#define _INCLUDE_RFIDTOOL2DLG_H_

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "RFID_TOOL2.h"
#include "XmlDetailDlg.h"
#include "InfoDlg.h"
#include "tinyxml2.h"
#include "CMSComm.h"
#include "ClientSock.h"
#include "ServerSock.h"
#include "tools.h"

#define EDGE 12
#define TIMER1 1
#define TIMER2 2

#define TCP 0
#define UDP 1
#define CLIENT 0
#define SERVER 1

struct Section 
{
	CString title;
	CString tooltip;
	CString uniqueId;
	CString item[10];
};

class CRFID_TOOL2Dlg : public CDialogEx
{
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

public:
	CRFID_TOOL2Dlg(CWnd* pParent = NULL);
	enum { IDD = IDD_RFID_TOOL2_DIALOG };

	//Serial
	CComboBox m_comport;
	CComboBox m_baud;
	CComboBox m_data;
	CComboBox m_stop;
	CComboBox m_parity;
	CMSComm m_ctrlComm;
	CByteArray recv_msg;
	void serial_open(int port);
	void OnCommMscomm1();
	afx_msg void OnBnClickedRadioComport();
	afx_msg void OnCbnSelchangeEditComport();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//Net
	CButton m_connect;
	CEdit m_lanport;
	CIPAddressCtrl m_ip;
	CComboBox m_nettype;
	CComboBox m_protocol;
	CClientSock m_clientsock;
	CServerSock m_serversock;
	CString udp_clientip, udp_clientport;
	void OnClose();
	void OnAccepted();
	void OnConnected();
	void OnClientRvc();
	void socket_init();
	void set_socket();
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnBnClickedRadioLan();
	afx_msg void OnCbnSelchangeComboProtocol();
	afx_msg void OnBnClickedButton2();

	//Command
	CTreeCtrl m_tree;
	CEdit m_log;
	CEdit m_commandsend;
	CXmlDetailDlg m_xmldetail;
	CButton m_commandhex;
	struct Section section[500];
	int section_nowid = 0;
	tinyxml2::XMLDocument doc;

	void command_send(CString str);
	void deal_command(CString str);
	void build_xmldetail_window();
	void create_section(tinyxml2::XMLElement *element);
	void show_section_text(HTREEITEM hItem);
	void ExpandTree(HTREEITEM hTreeItem);
	void tree_init(HTREEITEM hr, tinyxml2::XMLElement *element);
	HTREEITEM tree_add(HTREEITEM hr, tinyxml2::XMLElement *element);
	tinyxml2::XMLElement * tree_find(HTREEITEM hItem);

	afx_msg void OnOK();
	afx_msg void OnBnClickedCheckExpand();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnTvnGetInfoTipTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	
	//Log
	CStatic m_static5;
	CButton m_clear;
	CEdit m_state;
	CButton m_loghex;
	void write_log(CString str);
	afx_msg void OnBnClickedButtonClear();

	//Other	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonInfo();
};

#endif