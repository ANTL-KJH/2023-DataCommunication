#pragma once

// CDataSocket 명령 대상
class CTCPServerthdDlg;

class CDataSocket : public CSocket
{
public:
	CDataSocket(CTCPServerthdDlg *pDlg);
	virtual ~CDataSocket();
	CTCPServerthdDlg* m_pDlg;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


