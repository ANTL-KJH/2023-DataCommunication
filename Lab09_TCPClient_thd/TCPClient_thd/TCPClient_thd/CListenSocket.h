#pragma once

// CListenSocket 명령 대상
class CTCPClientthdDlg;

class CListenSocket : public CSocket
{
public:
	CListenSocket(CTCPClientthdDlg *pDlg);
	virtual ~CListenSocket();
	CTCPClientthdDlg* m_pDlg;
	virtual void OnAccept(int nErrorCode);
};


