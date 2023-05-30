﻿
// UDPClient_thdDlg.h: 헤더 파일
//

#pragma once
#define SERVERPORT 8880
#define CLIENTPORT 8888
class CDataSocket;
// CUDPClientthdDlg 대화 상자

struct ThreadArg
{
	CStringList* pList;
	CDialog* pDlg;
	int Thread_run;
};

class CUDPClientthdDlg : public CDialogEx
{
// 생성입니다.
public:
	CUDPClientthdDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CDataSocket* m_pDataSocket;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UDPCLIENT_THD_DIALOG };
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
	CWinThread* pThread1, * pThread2;
	ThreadArg arg1, arg2;
	CEdit m_tx_edit_short;
	CEdit m_tx_edit;
	CEdit m_rx_edit;
	CIPAddressCtrl m_ipaddr;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedDisconnect();
	void ProcessClose(CDataSocket* pSocket, int nErrorCode);
	void ProcessReceive(CDataSocket* pSocket, int nErrorCode);
};
