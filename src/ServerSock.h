#ifndef _INCLUDE_SERVERSOCK_H_ 
#define _INCLUDE_SERVERSOCK_H_ 

#pragma once
#include "afxsock.h"
class CRFID_TOOL2Dlg;

class CServerSock :
	public CAsyncSocket
{
public:
	CServerSock();
	virtual ~CServerSock();
	void SetDlg(CRFID_TOOL2Dlg* pDlg);

public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
private:
	CRFID_TOOL2Dlg* m_pDlg;
};

#endif

