#include "stdafx.h"
#include "RFID_TOOL2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRFID_TOOL2Dlg::CRFID_TOOL2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRFID_TOOL2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRFID_TOOL2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMPORT, m_comport);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_protocol);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_EDIT_LOG, m_log);
	DDX_Control(pDX, IDC_STATIC5, m_static5);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_clear);
	DDX_Control(pDX, IDC_EDIT_STATE, m_state);
	DDX_Control(pDX, IDC_CHECK2, m_loghex);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Control(pDX, IDC_EDIT_COMMANDTOSEND, m_commandsend);
	DDX_Control(pDX, IDC_CHECK1, m_commandhex);
	DDX_Control(pDX, IDC_COMBO1, m_baud);
	DDX_Control(pDX, IDC_COMBO2, m_data);
	DDX_Control(pDX, IDC_COMBO3, m_stop);
	DDX_Control(pDX, IDC_COMBO4, m_parity);
	DDX_Control(pDX, IDC_BUTTON2, m_connect);
	DDX_Control(pDX, IDC_EDIT1, m_lanport);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Control(pDX, IDC_COMBO5, m_nettype);
}

BEGIN_MESSAGE_MAP(CRFID_TOOL2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_NOTIFY(TVN_GETINFOTIP, IDC_TREE1, &CRFID_TOOL2Dlg::OnTvnGetInfoTipTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CRFID_TOOL2Dlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_RADIO_COMPORT, &CRFID_TOOL2Dlg::OnBnClickedRadioComport)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CRFID_TOOL2Dlg::OnBnClickedButtonClear)
	ON_CBN_SELCHANGE(IDC_EDIT_COMPORT, &CRFID_TOOL2Dlg::OnCbnSelchangeEditComport)
	ON_BN_CLICKED(IDC_CHECK1, &CRFID_TOOL2Dlg::OnBnClickedCheck1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_EXPAND, &CRFID_TOOL2Dlg::OnBnClickedCheckExpand)
	ON_BN_CLICKED(IDC_BUTTON2, &CRFID_TOOL2Dlg::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CRFID_TOOL2Dlg::OnCbnSelchangeCombo5)
	ON_BN_CLICKED(IDC_RADIO_LAN, &CRFID_TOOL2Dlg::OnBnClickedRadioLan)
	ON_CBN_SELCHANGE(IDC_COMBO_PROTOCOL, &CRFID_TOOL2Dlg::OnCbnSelchangeComboProtocol)
	ON_BN_CLICKED(IDC_BUTTON_INFO, &CRFID_TOOL2Dlg::OnBnClickedButtonInfo)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CRFID_TOOL2Dlg, CDialogEx)
	ON_EVENT(CRFID_TOOL2Dlg, IDC_MSCOMM1, 1, CRFID_TOOL2Dlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


BOOL CRFID_TOOL2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);	

	for (int i = 1; i < 50; i++){
		CString str;
		str.Format(_T("COM%d"),i);
		m_comport.AddString(str);
	}
	m_comport.SetCurSel(0);

	m_baud.AddString(_T("2400"));
	m_baud.AddString(_T("4800"));
	m_baud.AddString(_T("9600"));
	m_baud.AddString(_T("14400"));
	m_baud.AddString(_T("19200"));
	m_baud.AddString(_T("28800"));
	m_baud.AddString(_T("38400"));
	m_baud.AddString(_T("57600"));
	m_baud.AddString(_T("115200"));
	m_baud.SetCurSel(2);

	m_data.AddString(_T("5"));
	m_data.AddString(_T("6"));
	m_data.AddString(_T("7"));
	m_data.AddString(_T("8"));
	m_data.SetCurSel(3);

	m_stop.AddString(_T("1"));
	m_stop.AddString(_T("1.5"));
	m_stop.AddString(_T("2"));
	m_stop.SetCurSel(0);

	m_parity.AddString(_T("None"));
	m_parity.AddString(_T("Even"));
	m_parity.AddString(_T("Odd"));
	m_parity.AddString(_T("Mark"));
	m_parity.AddString(_T("Space"));
	m_parity.SetCurSel(0);

	m_ip.SetWindowText(_T("192.168.6.179"));
	m_lanport.SetWindowText(_T("2333"));

	m_protocol.AddString(_T("TCP"));
	m_protocol.AddString(_T("UDP"));
	m_protocol.SetCurSel(0);

	m_nettype.AddString(_T("Client"));
	m_nettype.AddString(_T("Server"));
	m_nettype.SetCurSel(0);

	m_connect.EnableWindow(false);

	m_state.SetWindowText(_T("Ready!"));
	build_xmldetail_window();

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *el_root;
	HTREEITEM hRoot = m_tree.InsertItem(_T("RT2"), 0, 0);

    doc.LoadFile( ".\\settings.xml" );
	if (doc.Error()) 
		m_state.SetWindowText(_T("Error"));
	else {	
		el_root = doc.FirstChildElement("RT2");
		tree_init(hRoot, el_root->FirstChildElement());
	}
	m_loghex.SetCheck(1);
	m_commandhex.SetCheck(1);

	m_clientsock.SetDlg(this);
	m_serversock.SetDlg(this);

	return TRUE; 
}

void CRFID_TOOL2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CRFID_TOOL2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//***********************************Serial*************************************************

void CRFID_TOOL2Dlg::serial_open(int port)
{
	if (m_ctrlComm.get_PortOpen())
		m_ctrlComm.put_PortOpen(FALSE);

	m_ctrlComm.put_CommPort(port);
	if (!m_ctrlComm.get_PortOpen())
		m_ctrlComm.put_PortOpen(TRUE);//´ò¿ª´®¿Ú  
	else
		write_log(_T("cannot open serial port"));

	CString settings, tmp;
	m_baud.GetWindowText(tmp);
	settings += tmp + _T(",");
	m_parity.GetWindowText(tmp);
	tmp = tmp[0];
	tmp.MakeLower();
	settings += tmp + _T(",");
	m_data.GetWindowText(tmp);
	settings += tmp + _T(",");
	m_stop.GetWindowText(tmp);
	settings += tmp;

	m_ctrlComm.put_Settings(settings);
	m_ctrlComm.put_InputMode(1);
	m_ctrlComm.put_RThreshold(1);
	m_ctrlComm.put_InputLen(0);
	m_ctrlComm.get_Input();
}

void CRFID_TOOL2Dlg::OnCommMscomm1()
{
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata[2048];
	CString strtemp;
	CString all;
	if (m_ctrlComm.get_CommEvent() == 2) {
		variant_inp = m_ctrlComm.get_Input();
		safearray_inp = variant_inp;
		len = safearray_inp.GetOneDimSize();
		for (k = 0; k<len; k++)
			safearray_inp.GetElement(&k, rxdata + k);
		for (k = 0; k<len; k++) {
			BYTE bt = *(char*)(rxdata + k);
			recv_msg.Add(bt);
		}
	}
	SetTimer(TIMER1, 100, 0);
}

void CRFID_TOOL2Dlg::OnBnClickedRadioComport()
{
	serial_open(m_comport.GetCurSel() + 1);
	socket_init();
	m_connect.EnableWindow(false);
}

void CRFID_TOOL2Dlg::OnCbnSelchangeEditComport()
{
	if (IsDlgButtonChecked(IDC_RADIO_COMPORT))
		serial_open(m_comport.GetCurSel() + 1);
}

void CRFID_TOOL2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent){
		case TIMER1:{
			CString msg, tmp;
			for (int i = 0; i < recv_msg.GetCount(); i++){
				tmp.Format(_T("%02x "), recv_msg[i]);
				msg += tmp;
			}
			if (m_loghex.GetCheck() == 0)
				msg = hex2str(msg);
			write_log(_T("recieve>") + msg);
			recv_msg.RemoveAll();
			KillTimer(TIMER1);
			break;
		}
		case TIMER2:{
			break;
		}
		default:
			break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

//***********************************Net*************************************************
void CRFID_TOOL2Dlg::OnClose()
{
}

void CRFID_TOOL2Dlg::OnAccepted()
{
	write_log(_T("TCP client connected"));
	if (m_serversock.Accept(m_clientsock))
		m_clientsock.AsyncSelect(FD_READ | FD_CLOSE);
}

void CRFID_TOOL2Dlg::OnConnected()
{
	write_log(_T("TCP connect success"));
}

void CRFID_TOOL2Dlg::OnClientRvc()
{
	char szRcv[200] = { 0 };
	CString tmp, msg;
	int nRcved;
	int sel_protocol = m_protocol.GetCurSel();
	int sel_type = m_nettype.GetCurSel();

	if (sel_protocol == UDP){
		UINT port;
		CString ip;
		nRcved = m_clientsock.ReceiveFrom(szRcv, 200, ip, port);
		if (sel_type == SERVER){
			CString p;
			p.Format(_T("%d"), port);
			if (udp_clientip != ip || udp_clientport != p){
				udp_clientip = ip;
				udp_clientport = p;
				write_log(_T("UDP client   ") + ip + _T(":") + p);
			}
		}
	}
	else if (sel_protocol == TCP){
		nRcved = m_clientsock.Receive(szRcv, 200);
	}

	for (int k = 0; k<nRcved; k++) {
		BYTE bt = szRcv[k];
		recv_msg.Add(bt);
	}

	for (int i = 0; i < recv_msg.GetCount(); i++){
		tmp.Format(_T("%02x "), recv_msg[i]);
		msg += tmp;
	}

	if (m_loghex.GetCheck() == 0)
		msg = hex2str(msg);
	write_log(_T("recieve>") + msg);
	recv_msg.RemoveAll();
}

void CRFID_TOOL2Dlg::socket_init()
{
	m_clientsock.Close();
	m_serversock.Close();
	udp_clientip = _T("");
	udp_clientport = _T("");
}

void CRFID_TOOL2Dlg::set_socket()
{
	int sel_type = m_nettype.GetCurSel();
	int sel_protocol = m_protocol.GetCurSel();
	socket_init();
	if (sel_type == SERVER){
		m_connect.SetWindowText(_T("Bind"));
	}
	else if (sel_type == CLIENT){
		if (sel_protocol == UDP)
			m_connect.SetWindowText(_T("Create"));
		else if (sel_protocol == TCP)
			m_connect.SetWindowText(_T("Connect"));
	}
}

void CRFID_TOOL2Dlg::OnBnClickedButton2()
{
	int sel_type = m_nettype.GetCurSel();
	int sel_protocol = m_protocol.GetCurSel();
	CString ip, port;
	socket_init();
	m_ip.GetWindowText(ip);
	m_lanport.GetWindowText(port);
	if (sel_type == SERVER){
		if (sel_protocol == UDP){
			m_clientsock.Create(_ttoi(port), SOCK_DGRAM, FD_READ | FD_CLOSE);
			m_clientsock.Bind(_ttoi(port), ip);
		}
		else if (sel_protocol == TCP){
			m_serversock.Create(_ttoi(port), SOCK_STREAM, FD_CLOSE | FD_ACCEPT);
			m_serversock.Bind(_ttoi(port), ip);
			m_serversock.Listen();
		}
	}
	else if (sel_type == CLIENT){
		if (sel_protocol == UDP){
			m_clientsock.Create(0, SOCK_DGRAM, FD_READ | FD_CLOSE);
		}
		else if (sel_protocol == TCP){
			m_clientsock.Create(0, SOCK_STREAM, FD_READ | FD_CONNECT | FD_CLOSE);
			m_clientsock.Connect(ip, _ttoi(port));
		}
	}
}

void CRFID_TOOL2Dlg::OnBnClickedRadioLan()
{
	m_connect.EnableWindow(true);
}

void CRFID_TOOL2Dlg::OnCbnSelchangeCombo5()
{
	set_socket();
}

void CRFID_TOOL2Dlg::OnCbnSelchangeComboProtocol()
{
	set_socket();
}

//***********************************Command*************************************************

void CRFID_TOOL2Dlg::command_send(CString str)
{
	CByteArray hex;
	char c[2];
	BYTE x;
	char msg[500];
	str.Remove(' ');
	for (int i = 0; i < str.GetLength(); i += 2){
		c[0] = str[i];
		c[1] = str[i + 1];
		x = strtol(c, NULL, 16);
		hex.Add(x);
		msg[i / 2] = x;
	}

	if (IsDlgButtonChecked(IDC_RADIO_LAN)){
		int sel_protocol = m_protocol.GetCurSel();
		int sel_nettype = m_nettype.GetCurSel();
		if (sel_protocol == UDP){
			CString ip, port;
			m_lanport.GetWindowText(port);
			m_ip.GetWindowText(ip);
			if (sel_nettype == SERVER){
				if (udp_clientip != _T(""))
					m_clientsock.SendTo(msg, str.GetLength() / 2, _ttoi(udp_clientport), udp_clientip);
				else
					write_log(_T("no client found"));
			}
			else if (sel_nettype == CLIENT){
				m_clientsock.SendTo(msg, str.GetLength() / 2, _ttoi(port), ip);
			}
		}
		else if (sel_protocol == TCP)
			m_clientsock.Send(msg, str.GetLength() / 2);
	}
	else if (IsDlgButtonChecked(IDC_RADIO_COMPORT)){
		m_ctrlComm.put_Output(COleVariant(hex));
	}
}

void CRFID_TOOL2Dlg::deal_command(CString str)
{
	command_send(str);

	if (m_loghex.GetCheck() == 0)
		str = hex2str(str);
	write_log(_T("command>") + str);
}

void CRFID_TOOL2Dlg::build_xmldetail_window()
{
	CRect rect;
	CRect r;
	float x, y, m, n;
	GetClientRect(&rect);
	GetDlgItem(IDC_TREE1)->GetWindowRect(r);
	ScreenToClient(r);
	rect.right -= EDGE;
	rect.left = r.right;
	rect.top = r.top;
	rect.bottom = r.bottom;
	m_xmldetail.Create(IDD_XML_DETAIL);
	m_xmldetail.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
}

void CRFID_TOOL2Dlg::create_section(tinyxml2::XMLElement * element)
{
	tinyxml2::XMLElement *el_item = element->FirstChildElement();
	CString s;
	int top = 30;
	do{
		s = cc2cs(el_item->Attribute("type"));
		if (s == _T("button"))
			top = m_xmldetail.CreateButtom(el_item, top) + 5;
		else if (s == _T("checkbox"))
			top = m_xmldetail.CreateCheckbox(el_item, top) + 5;
		else if (s == _T("drop-down"))
			top = m_xmldetail.CreateComboBox(el_item, top) + 5;
		else if (s == _T("label"))
			top = m_xmldetail.CreateStatic(el_item, top) + 5;
		else if (s == _T("textbox"))
			top = m_xmldetail.CreateEdit(el_item, top) + 5;
		else if (s == _T("browse-save"))
			top = m_xmldetail.CreateBrowse(el_item, top) + 5;
		else
			s = cc2cs(el_item->Attribute("type"));
		el_item = el_item->NextSiblingElement();
	} while (el_item);

}

void CRFID_TOOL2Dlg::show_section_text(HTREEITEM hItem)
{
	CString str = m_tree.GetItemText(hItem);
	while (m_tree.GetParentItem(hItem)) {
		hItem = m_tree.GetParentItem(hItem);
		str = m_tree.GetItemText(hItem) + _T("\\") + str;
	}
	m_xmldetail.SetHeadText(str);
	m_state.SetWindowText(str);
}

void CRFID_TOOL2Dlg::ExpandTree(HTREEITEM hTreeItem)
{
	if (!m_tree.ItemHasChildren(hTreeItem)){
		return;
	}
	HTREEITEM hNextItem = m_tree.GetChildItem(hTreeItem);
	while (hNextItem != NULL){
		ExpandTree(hNextItem);
		hNextItem = m_tree.GetNextItem(hNextItem, TVGN_NEXT);
	}
	m_tree.Expand(hTreeItem, TVE_EXPAND);
}

void CRFID_TOOL2Dlg::tree_init(HTREEITEM hr, tinyxml2::XMLElement *element)
{
	HTREEITEM hrr = tree_add(hr, element);
	tinyxml2::XMLElement *el = element->FirstChildElement();
	if (cc2cs(el->Name()) == _T("section"))
		tree_init(hrr, el);
	if (element->NextSiblingElement())
		tree_init(hr, element->NextSiblingElement());
	return;
}

HTREEITEM CRFID_TOOL2Dlg::tree_add(HTREEITEM hr, tinyxml2::XMLElement *element)
{
	HTREEITEM hrr = m_tree.InsertItem(cc2cs(element->Attribute("title")), 2, 2, hr, TVI_LAST);
	m_tree.SetItemData(hrr, section_nowid);

	section[section_nowid].title = cc2cs(element->Attribute("title"));
	section[section_nowid].tooltip = cc2cs(element->Attribute("tooltip"));
	if (element->Attribute("uniqueId"))
		section[section_nowid].uniqueId = cc2cs(element->Attribute("uniqueId"));
	section_nowid += 1;
	return hrr;
}

tinyxml2::XMLElement * CRFID_TOOL2Dlg::tree_find(HTREEITEM hItem)
{
	tinyxml2::XMLElement *el_root;
	HTREEITEM hr = hItem;
	int i = 0;
	CString s[20];

	doc.LoadFile(".\\settings.xml");
	el_root = doc.FirstChildElement("RT2");

	while (m_tree.GetParentItem(hr)) {
		s[i++] = m_tree.GetItemText(hr);
		hr = m_tree.GetParentItem(hr);
	}
	for (i = i - 1; i >= 0; i--){
		el_root = el_root->FirstChildElement();
		do{
			if ((el_root->Attribute("title")) == s[i])
				break;
			else
				el_root = el_root->NextSiblingElement();
		} while (el_root->NextSiblingElement());
	}
	return el_root;
}

void CRFID_TOOL2Dlg::OnOK()
{
	CString str;
	if (m_commandsend.GetFocus()){
		m_commandsend.GetWindowText(str);
		if (m_commandhex.GetCheck() == 0){
			str = str2hex(str);
		}
		command_send(str);
		if (m_loghex.GetCheck() == 0)
			str = hex2str(str);
		write_log(_T("command>") + str);
	}
}

void CRFID_TOOL2Dlg::OnBnClickedCheckExpand()
{
	ExpandTree(m_tree.GetRootItem());
}

void CRFID_TOOL2Dlg::OnBnClickedCheck1()
{
	CString str;
	if (m_commandhex.GetCheck()){
		m_commandsend.GetWindowText(str);
		str = str2hex(str);
		m_commandsend.SetWindowText(str);
	}
	else{
		m_commandsend.GetWindowText(str);
		str = hex2str(str);
		m_commandsend.SetWindowText(str);
	}
}

void CRFID_TOOL2Dlg::OnTvnGetInfoTipTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVGETINFOTIP pGetInfoTip = reinterpret_cast<LPNMTVGETINFOTIP>(pNMHDR);
	*pResult = 0;
	HTREEITEM hRoot = m_tree.GetRootItem();
	if (pGetInfoTip->hItem == hRoot)
		wcscpy_s(pGetInfoTip->pszText, 1, _T(""));
	else
		wcscpy_s(pGetInfoTip->pszText, 500, section[pGetInfoTip->lParam].tooltip);
	*pResult = 0;
}

void CRFID_TOOL2Dlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hItem = m_tree.GetSelectedItem();
	tinyxml2::XMLElement *element = tree_find(hItem);
	int id = m_tree.GetItemData(hItem);

	m_xmldetail.DestroyWindow();
	build_xmldetail_window();

	show_section_text(hItem);
	if (section[id].uniqueId != "")
		create_section(element);

	*pResult = 0;
}

//***********************************Log*************************************************
void CRFID_TOOL2Dlg::write_log(CString str)
{
	CString old_log;
	m_log.GetWindowText(old_log);
	if (old_log != _T(""))
		m_log.SetWindowText(old_log + _T("\r\n") + str);
	else
		m_log.SetWindowText(str);


	int nline = m_log.GetLineCount();
	m_log.LineScroll(nline - 1);
}

void CRFID_TOOL2Dlg::OnBnClickedButtonClear()
{
	m_log.SetWindowText(_T(""));
}

//***********************************Other*************************************************
void CRFID_TOOL2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rect;
	CRect r;
	float x, y, n,m;
	GetClientRect(&rect);    
	/*
	// IDC_EDIT_LOG
	
	GetDlgItem(IDC_EDIT_LOG)->GetWindowRect(r);
	ScreenToClient(r);
	r.top = (rect.bottom - rect.top) * 0.68;
	r.right = rect.right - EDGE;
	r.bottom = rect.bottom - EDGE;
	m_log.MoveWindow(r);
	n = r.top - 3;

	// IDC_STATIC5
	GetDlgItem(IDC_STATIC5)->GetWindowRect(r);
	ScreenToClient(r);
	y = r.bottom - r.top;
	r.bottom = n;
	r.top = r.bottom - y;
	m_static5.MoveWindow(r);

	// IDC_BUTTON_CLEAR
	GetDlgItem(IDC_BUTTON_CLEAR)->GetWindowRect(r);
	ScreenToClient(r);
	y = r.bottom - r.top;
	r.bottom = n;
	r.top = r.bottom - y;
	m_clear.MoveWindow(r);
	m = r.top;

	// IDC_CHECK2
	GetDlgItem(IDC_CHECK2)->GetWindowRect(r);
	ScreenToClient(r);
	y = r.bottom - r.top;
	r.bottom = n;
	r.top = r.bottom - y;
	m_loghex.MoveWindow(r);

	//IDC_EDIT_STATE 
	GetDlgItem(IDC_EDIT_STATE)->GetWindowRect(r);
	ScreenToClient(r);
	x = r.right - r.left;
	r.right = rect.right - EDGE;
	r.left = r.right - x;
	y = r.bottom - r.top;
	r.bottom = n;
	r.top = r.bottom - y;
	m_state.MoveWindow(r);

	// IDC_TREE1
	GetDlgItem(IDC_TREE1)->GetWindowRect(r);
	ScreenToClient(r);
	r.bottom = m - 6;
	r.right = (rect.right - rect.left) * 0.33;
	m_tree.MoveWindow(r);
	n = r.right;

	// IDD_XML_DETAIL
	r.right = rect.right - EDGE;
	r.left = n;
	r.bottom = m - 6;
	m_xmldetail.SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), SWP_SHOWWINDOW);
	*/
}


void CRFID_TOOL2Dlg::OnBnClickedButtonInfo()
{
	CInfoDlg infoDlg;  
	infoDlg.DoModal(); 
}
