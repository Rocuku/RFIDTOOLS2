// RFID_TOOL2Dlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "RFID_TOOL2.h"
#include "RFID_TOOL2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CRFID_TOOL2Dlg �Ի���

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
}

BEGIN_MESSAGE_MAP(CRFID_TOOL2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT_LOG, &CRFID_TOOL2Dlg::OnEnChangeEditLog)
	ON_STN_CLICKED(IDC_STATIC5, &CRFID_TOOL2Dlg::OnStnClickedStatic5)
	ON_EN_CHANGE(IDC_EDIT_STATE, &CRFID_TOOL2Dlg::OnEnChangeEditState)
	ON_NOTIFY(TVN_GETINFOTIP, IDC_TREE1, &CRFID_TOOL2Dlg::OnTvnGetInfoTipTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CRFID_TOOL2Dlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_RADIO_COMPORT, &CRFID_TOOL2Dlg::OnBnClickedRadioComport)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CRFID_TOOL2Dlg::OnBnClickedButtonClear)
	ON_CBN_SELCHANGE(IDC_EDIT_COMPORT, &CRFID_TOOL2Dlg::OnCbnSelchangeEditComport)
	ON_BN_CLICKED(IDC_CHECK1, &CRFID_TOOL2Dlg::OnBnClickedCheck1)
	ON_WM_TIMER()
END_MESSAGE_MAP()



BEGIN_EVENTSINK_MAP(CRFID_TOOL2Dlg, CDialogEx)
	ON_EVENT(CRFID_TOOL2Dlg, IDC_MSCOMM1, 1, CRFID_TOOL2Dlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

// CRFID_TOOL2Dlg ��Ϣ�������

BOOL CRFID_TOOL2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	for (int i = 1; i < 50; i++){
		CString str;
		str.Format(_T("COM%d"),i);
		m_comport.AddString(str);
	}
	m_comport.SetCurSel(0);

	m_protocol.AddString(_T("TCP"));
	m_protocol.AddString(_T("UDP"));
	m_comport.SetCurSel(0);

	m_state.SetWindowTextW(_T("Ready!"));
	build_xmldetail_window();

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *el_root;
	HTREEITEM hRoot = m_tree.InsertItem(_T("RT2"), 0, 0);

    doc.LoadFile( ".\\settings.xml" );
	if (doc.Error()) 
		m_state.SetWindowTextW(_T("Error"));
	else {	
		el_root = doc.FirstChildElement("RT2");
		tree_init(hRoot, el_root->FirstChildElement());
	}
	m_loghex.SetCheck(1);
	m_commandhex.SetCheck(1);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRFID_TOOL2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRFID_TOOL2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRFID_TOOL2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRFID_TOOL2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rect;
	CRect r;
	float x, y, n,m;
	GetClientRect(&rect);     //ȡ�ͻ�����С 

	//�ı�IDC_EDIT_LOGλ��
	GetDlgItem(IDC_EDIT_LOG)->GetWindowRect(r);
	ScreenToClient(r);
	r.top = (rect.bottom - rect.top) * 0.68;
	r.right = rect.right - EDGE;
	r.bottom = rect.bottom - EDGE;
	m_log.MoveWindow(r);
	n = r.top - 3;

	//�ı�IDC_STATIC5λ��
	GetDlgItem(IDC_STATIC5)->GetWindowRect(r);
	ScreenToClient(r);
	y = r.bottom - r.top;
	r.bottom = n;
	r.top = r.bottom - y;
	m_static5.MoveWindow(r);

	//�ı�IDC_BUTTON_CLEARλ��
	GetDlgItem(IDC_BUTTON_CLEAR)->GetWindowRect(r);
	ScreenToClient(r);
	y = r.bottom - r.top;
	r.bottom = n;
	r.top = r.bottom - y;
	m_clear.MoveWindow(r);
	m = r.top;

	//�ı�IDC_CHECK2λ��
	GetDlgItem(IDC_CHECK2)->GetWindowRect(r);
	ScreenToClient(r);
	y = r.bottom - r.top;
	r.bottom = n;
	r.top = r.bottom - y;
	m_loghex.MoveWindow(r);

	//�ı�IDC_EDIT_STATEλ��
	GetDlgItem(IDC_EDIT_STATE)->GetWindowRect(r);
	ScreenToClient(r);
	x = r.right - r.left;
	r.right = rect.right - EDGE;
	r.left = r.right - x;
	y = r.bottom - r.top;
	r.bottom = n;
	r.top = r.bottom - y;
	m_state.MoveWindow(r);

	//�ı�IDC_TREE1λ��
	GetDlgItem(IDC_TREE1)->GetWindowRect(r);
	ScreenToClient(r);
	r.bottom = m - 6;
	r.right = (rect.right - rect.left) * 0.33;
	m_tree.MoveWindow(r);
	n = r.right;

	//�ı�IDD_XML_DETAILλ��
	r.right = rect.right - EDGE;
	r.left = n;
	r.bottom = m - 6;
	m_xmldetail.SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), SWP_SHOWWINDOW);
}

void CRFID_TOOL2Dlg::OnEnChangeEditLog()
{
}

void CRFID_TOOL2Dlg::OnStnClickedStatic5()
{
}

void CRFID_TOOL2Dlg::OnEnChangeEditState()
{
}

void CRFID_TOOL2Dlg::OnTvnGetInfoTipTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVGETINFOTIP pGetInfoTip = reinterpret_cast<LPNMTVGETINFOTIP>(pNMHDR);
	*pResult = 0;
	HTREEITEM hRoot = m_tree.GetRootItem();      // ��ȡ���ĸ��ڵ�   
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

CString CRFID_TOOL2Dlg::cc2cs(const char *cc)
{
	CString str(cc);
	return str;
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

void CRFID_TOOL2Dlg::build_xmldetail_window()
{
	CRect rect;
	CRect r;
	float x, y, m, n;
	GetClientRect(&rect);     //ȡ�ͻ�����С 
	GetDlgItem(IDC_TREE1)->GetWindowRect(r);
	ScreenToClient(r);
	rect.right -= EDGE;
	rect.left = r.right;
	rect.top = r.top;
	rect.bottom = r.bottom;
	m_xmldetail.Create(IDD_XML_DETAIL);
	m_xmldetail.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
}

void CRFID_TOOL2Dlg::show_section_text(HTREEITEM hItem)
{
	CString str = m_tree.GetItemText(hItem);
	while (m_tree.GetParentItem(hItem)) {
		hItem = m_tree.GetParentItem(hItem);
		str = m_tree.GetItemText(hItem) + _T("\\") + str;
	}
	m_xmldetail.SetHeadText(str);
	m_state.SetWindowTextW(str);
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

void CRFID_TOOL2Dlg::deal_command(CString str)
{
	serial_send(str);

	if (m_loghex.GetCheck() == 0)
		str = hex2str(str);
	write_log(_T("command>") + str);
}

void CRFID_TOOL2Dlg::write_log(CString str)
{
	CString old_log;
	m_log.GetWindowTextW(old_log);
	if (old_log != _T(""))
		m_log.SetWindowTextW(old_log + _T("\r\n") + str);
	else
		m_log.SetWindowTextW(str);


	int nline = m_log.GetLineCount();
	m_log.LineScroll(nline - 1);
}

void CRFID_TOOL2Dlg::OnBnClickedRadioComport()
{
	serial_open(m_comport.GetCurSel() + 1);
}

void CRFID_TOOL2Dlg::OnCbnSelchangeEditComport()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (IsDlgButtonChecked(IDC_RADIO_COMPORT))
		serial_open(m_comport.GetCurSel() + 1);
}

void CRFID_TOOL2Dlg::serial_open(int port)
{
	if (m_ctrlComm.get_PortOpen())
		m_ctrlComm.put_PortOpen(FALSE);

	m_ctrlComm.put_CommPort(port);
	if (!m_ctrlComm.get_PortOpen())
		m_ctrlComm.put_PortOpen(TRUE);//�򿪴���  
	else
		write_log(_T("cannot open serial port"));

	m_ctrlComm.put_Settings(_T("9600,n,8,1")); //������9600����У�飬8������λ��1��ֹͣλ  
	m_ctrlComm.put_InputMode(1); //1����ʾ�Զ����Ʒ�ʽ��ȡ����  
	m_ctrlComm.put_RThreshold(1);
	//����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�  
	m_ctrlComm.put_InputLen(0); //���õ�ǰ���������ݳ���Ϊ0  
	m_ctrlComm.get_Input();//��Ԥ���������������������  
}

void CRFID_TOOL2Dlg::serial_send(CString str)
{
	CByteArray hex;
	char c[2];
	BYTE x;
	str.Remove(' ');
	for (int i = 0; i < str.GetLength(); i += 2){
		c[0] = str[i];
		c[1] = str[i + 1];
		x = strtol(c, NULL, 16);
		hex.Add(x);
	}
	m_ctrlComm.put_Output(COleVariant(hex));
}


void CRFID_TOOL2Dlg::OnCommMscomm1()
{
	// TODO: Add your control notification handler code here  
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata[2048]; //����BYTE���� An 8-bit integerthat is not signed.  
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
			strtemp.Format(_T("%c"), bt); 
			all += strtemp;
		}
	}
//	recv_msg += all;
	SetTimer(TIMER1, 100, 0);

}


void CRFID_TOOL2Dlg::OnBnClickedButtonClear()
{
	m_log.SetWindowTextW(_T(""));
}

void CRFID_TOOL2Dlg::OnOK()
{
	CString str;
	if (m_commandsend.GetFocus()){
		m_commandsend.GetWindowTextW(str);

		if (m_commandhex.GetCheck() == 0){
			str = str2hex(str);
		}

		serial_send(str);

		if (m_loghex.GetCheck() == 0)
			str = hex2str(str);
		write_log(_T("command>") + str);
			
	}
}



void CRFID_TOOL2Dlg::OnBnClickedCheck1()
{
	CString str;
	if (m_commandhex.GetCheck()){
		m_commandsend.GetWindowTextW(str);
		str = str2hex(str);
		m_commandsend.SetWindowTextW(str);
	}
	else{
		m_commandsend.GetWindowTextW(str);
		str = hex2str(str);
		m_commandsend.SetWindowTextW(str);
	}
}


void CRFID_TOOL2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent){
		case TIMER1:{
			CString msg,tmp;
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
		}
		default:
			break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


CString CRFID_TOOL2Dlg::str2hex(CString str)
{
	CString hex, tmp;
	for (int i = 0; i < str.GetLength(); i++)
	{
		tmp.Format(_T("%02x "), str[i]);
		hex += tmp;
	}
	return hex;
}

CString CRFID_TOOL2Dlg::hex2str(CString hex)
{
	CString str, tmp;
	char c[2];
	int n;
	BYTE x;
	hex.Remove(' ');
	for (int i = 0; i < hex.GetLength(); i += 2){
		c[0] = hex[i];
		c[1] = hex[i + 1];
		x = strtol(c, NULL, 16);
		tmp.Format(_T("%c"), x);
		str += tmp;
	}
	return str;
}
/*
CByteArray strhex2cbyte(CString str)
{
	CByteArray hex;
	for (int i = 0; i < str.GetLength(); i++)
		hex.Add(str[i]);
	return hex;
}
*/