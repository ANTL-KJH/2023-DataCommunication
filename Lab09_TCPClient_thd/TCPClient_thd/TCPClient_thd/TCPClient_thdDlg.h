
// TCPClient_thdDlg.h: 헤더 파일
//

#pragma once
#include "afxcoll.h"
#include "afxwin.h"

class CDataSocket;
class CListenSocket;

struct ThreadArg
{
	CStringList* pList;
	CDialogEx* pDlg;
	int Thread_run;
};
// CTCPClientthdDlg 대화 상자
class CTCPClientthdDlg : public CDialogEx
{
// 생성입니다.
public:
	CTCPClientthdDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CWinThread* pThread1, * pThread2;
	ThreadArg arg1, arg2;
	CListenSocket* m_pListenSocket;
	CDataSocket* m_pDataSocket;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TCPCLIENT_THD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	CEdit m_edit;
	CIPAddressCtrl m_ipaddr;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedSend();
	afx_msg void OnEnChangeEdit3();
	CEdit m_tx_edit;
	CEdit m_rx_edit;
	void ProcessAccept(int nErrorCode);
	void ProcessReceive(CDataSocket* pSocket, int nErrorCode);
	void ProcessClose(CDataSocket* pSocket, int nErrorCode);
};
