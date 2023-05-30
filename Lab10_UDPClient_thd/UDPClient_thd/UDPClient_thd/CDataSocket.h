#pragma once

// CDataSocket 명령 대상
class CUDPClientthdDlg;
class CDataSocket : public CSocket
{
public:
	CDataSocket(CUDPClientthdDlg* pDlg);
	virtual ~CDataSocket();
	CUDPClientthdDlg* m_pDlg;
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
};


