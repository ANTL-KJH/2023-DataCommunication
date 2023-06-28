#pragma once

// CDataSocket 명령 대상
class CARQUDPServerDlg;
class CDataSocket : public CSocket
{
public:
	CDataSocket(CARQUDPServerDlg *pDlg);
	virtual ~CDataSocket();
	CARQUDPServerDlg* m_pDlg;
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
};


