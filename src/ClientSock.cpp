#include "stdafx.h"
#include "ClientSock.h"
#include "RFID_TOOL2Dlg.h"


CClientSock::CClientSock()
{
	m_pDlg = NULL;
}

CClientSock::~CClientSock()
{
	m_pDlg = NULL;
}

void CClientSock::OnClose(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		m_pDlg->OnClose();
	}
	CAsyncSocket::OnClose(nErrorCode);
}

void CClientSock::OnConnect(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		m_pDlg->OnConnected();
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSock::OnReceive(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		m_pDlg->OnClientRvc();
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSock::SetDlg(CRFID_TOOL2Dlg* pDlg)
{
	if (NULL != pDlg)
	{
		m_pDlg = pDlg;
	}
}
