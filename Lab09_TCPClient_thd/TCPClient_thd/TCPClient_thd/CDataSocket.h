#pragma once

// CDataSocket 명령 대상
class CTCPClientthdDlg;

class CDataSocket : public CSocket
{
public:
	CDataSocket(CTCPClientthdDlg* pDlg);
	virtual ~CDataSocket();
	CTCPClientthdDlg* m_pDlg;
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


