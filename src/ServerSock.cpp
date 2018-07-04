#include "stdafx.h"
#include "ServerSock.h"
#include "RFID_TOOL2Dlg.h"


CServerSock::CServerSock()
{
	m_pDlg = NULL;
}

CServerSock::~CServerSock()
{
	m_pDlg = NULL;
}

void CServerSock::OnAccept(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		m_pDlg->OnAccepted();
	}
	CAsyncSocket::OnAccept(nErrorCode);
}

void CServerSock::OnClose(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		m_pDlg->OnClose();
	}
	CAsyncSocket::OnClose(nErrorCode);
}


void CServerSock::SetDlg(CRFID_TOOL2Dlg* pDlg)
{
	if (NULL != pDlg)
		m_pDlg = pDlg;
}