
// ARQUDPServerDlg.h: 헤더 파일
//

#pragma once
#include "afxcoll.h"
#include "afxwin.h"
#include "CDataSocket.h"


#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")	// 디버깅을 위한 console

#define SERVERPORT 8880
#define CLIENTPORT 8888
#define FSIZE 16 //1 Frame = 16 Byte
#define SEQNUMSIZE 16


struct Frame
{
	int seq_num;
	int ack_num;
	char type; //1Byte (ACK, NACK, SEND)
	unsigned short checksum; //16bit = 2Byte필요하기 때문
	char p_buffer[FSIZE + 1] = { 0 };//데이터 담을 버퍼
	LARGE_INTEGER starttime;//보내기 시작한 타임
	char more; //총 보낼 프레임이 몇개인지
};
struct ThreadArg
{
	CList<Frame>* pFrameList;
	CStringList* pList;
	CDialogEx* pDlg;
	int Thread_run;
};
// CARQUDPServerDlg 대화 상자
class CARQUDPServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CARQUDPServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CWinThread* pThread1, * pThread2;
	ThreadArg arg1, arg2;
	CDataSocket* m_pDataSocket;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARQUDPSERVER_DIALOG };
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
	int seqnum;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedDisconnect();
	void ProcessReceive(CDataSocket* pSocket, int nErrorCode);
	void ProcessClose(CDataSocket* pSocket, int nErrorCode);
};
