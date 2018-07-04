#ifndef _INCLUDE_CLIENTSOCK_H_ 
#define _INCLUDE_CLIENTSOCK_H_ 

#pragma once
#include "afxsock.h"
class CRFID_TOOL2Dlg;

class CClientSock :
	public CAsyncSocket
{
public:
	CClientSock();
	virtual ~CClientSock();
	void SetDlg(CRFID_TOOL2Dlg* pDlg);

public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

private:
	CRFID_TOOL2Dlg* m_pDlg;
};

#endif