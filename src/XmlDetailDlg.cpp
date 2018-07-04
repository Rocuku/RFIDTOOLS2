#include "stdafx.h"
#include "RFID_TOOL2.h"
#include "XmlDetailDlg.h"
#include "afxdialogex.h"
#include "RFID_TOOL2Dlg.h"

IMPLEMENT_DYNAMIC(CXmlDetailDlg, CDialogEx)
BEGIN_MESSAGE_MAP(CXmlDetailDlg, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()

	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON, OnButton)
END_MESSAGE_MAP()

CXmlDetailDlg::CXmlDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CXmlDetailDlg::IDD, pParent)
	, m_xmldetail(0)
{
}

CXmlDetailDlg::~CXmlDetailDlg()
{
}

void CXmlDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_title_text);
}

BOOL CXmlDetailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	RECT rect;
	GetClientRect(&rect);
	SetScrollRange(SB_HORZ, 0, rect.right - rect.left, TRUE);
	SetScrollRange(SB_VERT, 0, rect.bottom - rect.top, TRUE);

	font = new CFont;
	font->CreateFont(15, // nHeight 
		0, // nWidth 
		0, // nEscapement 
		0, // nOrientation 
		FW_BOLD, // nWeight 
		FALSE, // bItalic 
		FALSE, // bUnderline 
		0, // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("Microsoft JhengHei UI")); // lpszFac 

	items_num = 0;
	subfont = new CFont;
	subfont->CreateFont(14,  0, 0, 0, FW_BOLD, FALSE,FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,_T("Consolas")); 

	GetDlgItem(IDC_EDIT1)->SetFont(font);
	return TRUE;  // return TRUE unless you set the focus to a control
}

HBRUSH CXmlDetailDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
	}
	return hbr;
}



int CXmlDetailDlg::CreateButtom(tinyxml2::XMLElement *element, int top)
{
	CButton *p_Button = new CButton();
	CString text = cc2cs(element->Attribute("text"));
	int height = 24,weight;
	int left = 5, right, bottom = height + top;
	weight = text.GetLength() * 11;
	right = left + weight;
	p_Button->Create(text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(left, top, right, bottom), this, IDC_BUTTON);
	p_Button->SetFont(font);
	action = cc2cs(element->Attribute("action0"));
	return bottom;
}

int CXmlDetailDlg::CreateCheckbox(tinyxml2::XMLElement *element, int top)
{
	CButton *p_Button = new CButton();
	CStatic *p_Static = new CStatic();
	CString text = cc2cs(element->Attribute("text"));
	CString label = cc2cs(element->Attribute("label"));
	int height = 16, weight;
	int left = 5, right, bottom1, bottom2;

	if (label != ""){
		bottom1 = height + top;
		weight = label.GetLength() * 11;
		right = left + weight;
		p_Static->Create(label, WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom1), this, top + 1);
		p_Static->SetFont(subfont);
	}
	else bottom1 = top;

	height = 22;
	weight = text.GetLength() * 11 + 20;
	right = left + weight;
	bottom2 = height + bottom1;
	p_Button->Create(text, WS_CHILD | WS_VISIBLE | BS_CHECKBOX | BST_CHECKED, CRect(left, bottom1, right, bottom2), this, top);
	p_Button->SetFont(font);

	if (cc2cs(element->Attribute("defaultValue")) == _T("checked"))
		CheckDlgButton(top, 1);

	uniqueId_save(cc2cs(element->Attribute("uniqueId")), top, TYPE_CHECKBOX, cc2cs(element->Attribute("valueUnchecked")), cc2cs(element->Attribute("valueChecked")));
	return bottom2;
}

int CXmlDetailDlg::CreateComboBox(tinyxml2::XMLElement *element, int top)
{
	CComboBox *p_ComboBox = new CComboBox();
	CStatic *p_Static = new CStatic();
	CString items = cc2cs(element->Attribute("values"));
	CString label = cc2cs(element->Attribute("label"));
	int height = 16, weight;
	int left = 5, right, bottom1, bottom2;

	if (label){
		bottom1 = height + top;
		weight = label.GetLength() * 11;
		right = left + weight;
		p_Static->Create(label, WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom1), this, top + 1);
		p_Static->SetFont(subfont);
	}
	else bottom1 = top;
	
	weight = atoi(element->Attribute("width")) + 30;
	height = 20;
	bottom2 = height + bottom1;
	right = left + weight;
	p_ComboBox->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, CRect(left, bottom1, right, bottom2), this, top);
	int x = items.Find(','), x_last = -1;
	CString m,item;
	if (x == -1){
		int start, end;
		x = items.Find(':');
		item = _T("");
		for (int j = 0; j < x; j++){
			m.Format(_T("%c"), items[j]);
			item += m;
		}
		start = _ttoi(item);
		item = _T("");
		for (int j = x + 1; j < items.GetLength(); j++){
			m.Format(_T("%c"), items[j]);
			item += m;
		}
		end = _ttoi(item);
		char str[25];
		for (int j = start; j <= end; j++){
			_itoa_s(j, str, 25, 10);
			p_ComboBox->AddString(cc2cs(str));
		}
	}
	else{
		while (x != -1){
			item = _T("");
			for (int j = x_last + 1; j < x; j++){
				m.Format(_T("%c"), items[j]);
				item += m;
			}
			p_ComboBox->AddString(item);
			x_last = x;
			x = items.Find(',', x + 1);
		}
		item = _T("");
		for (int j = x_last + 1; j < items.GetLength(); j++){
			m.Format(_T("%c"), items[j]);
			item += m;
		}
		p_ComboBox->AddString(item);
	}
	p_ComboBox->SetCurSel(p_ComboBox->FindString(0, cc2cs(element->Attribute("defaultValue"))));
	p_ComboBox->SetFont(font);

	uniqueId_save(cc2cs(element->Attribute("uniqueId")), top, TYPE_COMBOBOX, _T(""), _T(""));
	return bottom2;
}

int CXmlDetailDlg::CreateStatic(tinyxml2::XMLElement *element, int top)
{
	CStatic *p_Static= new CStatic();
	CString label = cc2cs(element->Attribute("label"));
	int height, weight = 1000;
	int left = 5, right = left + weight, bottom;

	label.Remove(_T('\t'));

	int line = weight / 16;
	int x = label.Find('\n'), n = 0, y;
	int x_last = 0;
	while (x != -1){
		n++;
		while (x - x_last > line){
			x_last += line;
			x_last = label.Find(' ', x_last);
			label.Insert(x_last, '\n');
			x++;
			x_last++;
		}
		x_last = x;
		x = label.Find('\n', x + 1);
	}

	x = label.GetLength();
	while (x - x_last > line){
		x_last += line;
		x_last = label.Find(' ', x_last);
		label.Insert(x_last, '\n');
		x++;
		x_last++;
	}


	height = (n + 1) * 20;
	bottom = top + height;
	p_Static->Create(label, WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(left, top, right, bottom), this, top);
	p_Static->SetFont(font);
	return bottom;
}

int CXmlDetailDlg::CreateEdit(tinyxml2::XMLElement *element, int top)
{
	CEdit *p_Edit = new CEdit();
	CStatic *p_Static = new CStatic();
	CString label = cc2cs(element->Attribute("label"));
	int height = 18, weight;
	int left = 5, right, bottom1, bottom2;

	if (label){
		bottom1 = height + top;
		weight = label.GetLength() * 11;
		right = left + weight;
		p_Static->Create(label, WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom1), this, top + 1);
		p_Static->SetFont(subfont);
	}
	else bottom1 = top;

	if (element->Attribute("width") != "")
		weight = 150;
	else
		weight = atoi(element->Attribute("width")) + 30;
	height = 22;
	bottom2 = height + bottom1;
	right = left + weight;
	p_Edit->Create(WS_CHILD | WS_VISIBLE | DT_TABSTOP | WS_BORDER, CRect(left, bottom1, right, bottom2), this, top);
	p_Edit->SetFont(font);

	p_Edit->SetWindowText(cc2cs(element->Attribute("defaultValue")));
	uniqueId_save(cc2cs(element->Attribute("uniqueId")), top, TYPE_EDIT, _T(""), _T(""));
	return bottom2;
}

int CXmlDetailDlg::CreateBrowse(tinyxml2::XMLElement *element, int top)
{
	CEdit *p_Edit = new CEdit();
	CStatic *p_Static = new CStatic();
	CButton *p_Button = new CButton();
	CString label = cc2cs(element->Attribute("label"));
	CString text = _T("BROWSE");
	int height = 18, weight;
	int left = 5, right, bottom1, bottom2;

	if (label){
		bottom1 = height + top;
		weight = label.GetLength() * 11;
		right = left + weight;
		p_Static->Create(label, WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom1), this, top + 1);
		p_Static->SetFont(subfont);
	}
	else bottom1 = top;

	weight = 300;
	height = 24;
	bottom2 = height + bottom1;
	right = left + weight;
	p_Edit->Create(WS_CHILD | WS_VISIBLE | DT_TABSTOP | WS_BORDER, CRect(left, bottom1, right, bottom2), this, top);
	p_Edit->SetFont(font);
	uniqueId_save(cc2cs(element->Attribute("uniqueId")), top, TYPE_BROWSE, _T(""), _T(""));

	weight = 65;
	left = right + 5;
	right = left + weight;
	p_Button->Create(text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(left, bottom1, right, bottom2), this, top + 2);
	p_Button->SetFont(font);

	return bottom2;
}

void CXmlDetailDlg::SetHeadText(CString str)
{
	//	pDC->SetTextColor(#104E8B);
	m_title_text.SetWindowText(str); 
}


void CXmlDetailDlg::OnButton()
{

	CRFID_TOOL2Dlg *tmp = (CRFID_TOOL2Dlg *)this->GetOwner();
	
	UINT nCheck = 0;
	
	for (int i = 0; i < items_num; i++){
		switch (items_type[i]){
			case TYPE_CHECKBOX :
				CheckDlgButton(items_id[i], nCheck);
				items_res[i] = items_value[i][nCheck];
				break;
			case TYPE_COMBOBOX:
				GetDlgItem(items_id[i])->GetWindowText(items_res[i]);
				break;
			case TYPE_EDIT:
				GetDlgItem(items_id[i])->GetWindowText(items_res[i]);
				break;
			case TYPE_BROWSE:
				GetDlgItem(items_id[i])->GetWindowText(items_res[i]);
				break;
			default:
				break;
		}
	}
	CString command = action;
	int start = command.Find('$'), end, end_new;
	CString str;
	while (start != -1){
		end = command.Find(' ', start + 1);
		if (end == -1) end = command.GetLength();
		str = _T("");
		for (int j = start + 1; j < end; j++){
			str += command[j];
		}
		
		for (int i = 0; i < items_num; i++)
			if (items_uniqueId[i] == str){
				end_new = end - str.GetLength() + items_res[i].GetLength();
				command.Replace(_T("$") + str, items_res[i]);
			}
			start = command.Find('$', start + 1);
	}
	tmp->deal_command(command);
}

void CXmlDetailDlg::uniqueId_save(CString uniqueId, int id, int type, CString value1, CString value2)
{
	if (uniqueId != ""){
		items_id[items_num] = id;
		items_uniqueId[items_num] = uniqueId;
		items_type[items_num] = type;
		items_value[items_num][0] = value1;
		items_value[items_num++][1] = value2;
	}
}

void CXmlDetailDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO scrollInfo;
	GetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
	switch (nSBCode)
	{
	case   SB_LINEUP:
		scrollInfo.nPos -= 1;
		if (scrollInfo.nPos   <   scrollInfo.nMin)
		{
			scrollInfo.nPos = scrollInfo.nMin;
			break;
		}
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		ScrollWindow(0, 1);
		break;
	case   SB_LINEDOWN:
		scrollInfo.nPos += 1;
		if (scrollInfo.nPos   >   scrollInfo.nMax)
		{
			scrollInfo.nPos = scrollInfo.nMax;
			break;
		}
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		ScrollWindow(0, -1);
		break;
	case   SB_TOP:
		ScrollWindow(0, (scrollInfo.nPos - scrollInfo.nMin) * 1);
		scrollInfo.nPos = scrollInfo.nMin;
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		break;
	case   SB_BOTTOM:
		ScrollWindow(0, -(scrollInfo.nMax - scrollInfo.nPos) * 1);
		scrollInfo.nPos = scrollInfo.nMax;
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		break;
	case   SB_PAGEUP:
		scrollInfo.nPos -= 1;
		if (scrollInfo.nPos   <   scrollInfo.nMin)
		{
			scrollInfo.nPos = scrollInfo.nMin;
			break;
		}
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		ScrollWindow(0, 1 * 1);
		break;
	case   SB_PAGEDOWN:
		scrollInfo.nPos += 1;
		if (scrollInfo.nPos   >   scrollInfo.nMax)
		{
			scrollInfo.nPos = scrollInfo.nMax;
			break;
		}
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		ScrollWindow(0, -1 * 1);
		break;
	case   SB_ENDSCROLL:
		break;
	case   SB_THUMBPOSITION:
		break;
	case   SB_THUMBTRACK:


		ScrollWindow(0, (scrollInfo.nPos - nPos));
		scrollInfo.nPos = nPos;
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		break;
	}
}


void CXmlDetailDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO scrollInfo;
	GetScrollInfo(SB_HORZ, &scrollInfo, SIF_ALL);
	switch (nSBCode)
	{
	case   SB_LINEUP:
		scrollInfo.nPos -= 1;
		if (scrollInfo.nPos   <   scrollInfo.nMin)
		{
			scrollInfo.nPos = scrollInfo.nMin;
			break;
		}
		SetScrollInfo(SB_HORZ, &scrollInfo, SIF_ALL);
		ScrollWindow(10, 0);
		break;
	case   SB_LINEDOWN:
		scrollInfo.nPos += 1;
		if (scrollInfo.nPos   >   scrollInfo.nMax)
		{
			scrollInfo.nPos = scrollInfo.nMax;
			break;
		}
		SetScrollInfo(SB_HORZ, &scrollInfo, SIF_ALL);
		ScrollWindow(-10, 0);
		break;
	case   SB_TOP:
		ScrollWindow((scrollInfo.nPos - scrollInfo.nMin) * 10, 0);
		scrollInfo.nPos = scrollInfo.nMin;
		SetScrollInfo(SB_HORZ, &scrollInfo, SIF_ALL);
		break;
	case   SB_BOTTOM:
		ScrollWindow(-(scrollInfo.nMax - scrollInfo.nPos) * 10, 0);
		scrollInfo.nPos = scrollInfo.nMax;
		SetScrollInfo(SB_HORZ, &scrollInfo, SIF_ALL);
		break;
	case   SB_PAGEUP:
		scrollInfo.nPos -= 5;
		if (scrollInfo.nPos   <   scrollInfo.nMin)
		{
			scrollInfo.nPos = scrollInfo.nMin;
			break;
		}
		SetScrollInfo(SB_HORZ, &scrollInfo, SIF_ALL);
		ScrollWindow(10 * 5, 0);
		break;
	case   SB_PAGEDOWN:
		scrollInfo.nPos += 5;
		if (scrollInfo.nPos   >   scrollInfo.nMax)
		{
			scrollInfo.nPos = scrollInfo.nMax;
			break;
		}
		SetScrollInfo(SB_HORZ, &scrollInfo, SIF_ALL);
		ScrollWindow(-10 * 5, 0);
		break;
	case   SB_ENDSCROLL:
		break;
	case   SB_THUMBPOSITION:
		break;
	case   SB_THUMBTRACK:
		ScrollWindow((scrollInfo.nPos - nPos) * 10, 0);
		scrollInfo.nPos = nPos;
		SetScrollInfo(SB_HORZ, &scrollInfo, SIF_ALL);
		break;
	}
}



