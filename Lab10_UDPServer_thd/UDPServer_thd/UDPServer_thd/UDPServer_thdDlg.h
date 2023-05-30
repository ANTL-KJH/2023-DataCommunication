﻿
// UDPServer_thdDlg.h: 헤더 파일
//

#pragma once
#include "afxcoll.h"
#include "afxwin.h"
#include "CDataSocket.h"
#define SERVERPORT 8880
#define CLIENTPORT 8888
struct ThreadArg
{
	CStringList* pList;
	CDialogEx* pDlg;
	int Thread_run;
};
// CUDPServerthdDlg 대화 상자
class CUDPServerthdDlg : public CDialogEx
{
// 생성입니다.
public:
	CUDPServerthdDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CWinThread* pThread1, * pThread2;
	ThreadArg arg1, arg2;
	CDataSocket* m_pDataSocket;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UDPSERVER_THD_DIALOG };
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
	CEdit m_tx_edit_short;
	CEdit m_tx_edit;
	CEdit m_rx_edit;
	void ProcessReceive(CDataSocket* pSocket, int nErrorCode);
	void ProcessClose(CDataSocket* pSocket, int nErrorCode);
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedDisconnect();
};
