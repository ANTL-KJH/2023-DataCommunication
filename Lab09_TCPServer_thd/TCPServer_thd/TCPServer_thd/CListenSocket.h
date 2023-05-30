#pragma once

// CListenSocket 명령 대상
class CTCPServerthdDlg;

class CListenSocket : public CSocket
{
public:
	CListenSocket(CTCPServerthdDlg *pDlg);
	virtual ~CListenSocket();
	CTCPServerthdDlg* m_pDlg;
	virtual void OnAccept(int nErrorCode);
};


