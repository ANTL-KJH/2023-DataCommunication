#pragma once

// CDataSocket 명령 대상
class CUDPServerthdDlg;
class CDataSocket : public CSocket
{
public:
	CDataSocket(CUDPServerthdDlg *pDlg);
	virtual ~CDataSocket();
	CUDPServerthdDlg* m_pDlg;
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
};


