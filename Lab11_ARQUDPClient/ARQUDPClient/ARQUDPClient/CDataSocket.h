#pragma once
#include "ARQUDPClientDlg.h"
// CDataSocket 명령 대상
class CARQUDPClientDlg;
class CDataSocket : public CSocket
{
public:
	CDataSocket(CARQUDPClientDlg* pDlg);
	CARQUDPClientDlg* m_pDlg;
	virtual ~CDataSocket();
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
};


