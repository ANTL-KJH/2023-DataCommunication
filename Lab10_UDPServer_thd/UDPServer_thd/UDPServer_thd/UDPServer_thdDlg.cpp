﻿
// UDPServer_thdDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "UDPServer_thd.h"
#include "UDPServer_thdDlg.h"
#include "afxdialogex.h"
#include "CDataSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCriticalSection tx_cs;
CCriticalSection rx_cs;
CString PeerAddr = _T("");
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUDPServerthdDlg 대화 상자



CUDPServerthdDlg::CUDPServerthdDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UDPSERVER_THD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPServerthdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_tx_edit_short);
	DDX_Control(pDX, IDC_EDIT2, m_tx_edit);
	DDX_Control(pDX, IDC_EDIT3, m_rx_edit);
}

BEGIN_MESSAGE_MAP(CUDPServerthdDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CUDPServerthdDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_DISCONNECT, &CUDPServerthdDlg::OnBnClickedDisconnect)
END_MESSAGE_MAP()


UINT RXThread(LPVOID arg)
{
	ThreadArg* pArg = (ThreadArg*)arg;
	CStringList* plist = pArg->pList;
	CUDPServerthdDlg* pDlg = (CUDPServerthdDlg*)pArg->pDlg;


	while (pArg->Thread_run) // Thread running
	{
		POSITION pos = plist->GetHeadPosition();
		POSITION current_pos;

		while (pos != NULL)
		{
			current_pos = pos;
			rx_cs.Lock();	// CS Lock
			CString str = plist->GetNext(pos);
			rx_cs.Unlock(); // CS Unlock

			CString message;
			pDlg->m_rx_edit.GetWindowText(message);
			message += str; // rx message에 받은 message 추가
			pDlg->m_rx_edit.SetWindowText(message);
			pDlg->m_rx_edit.LineScroll(pDlg->m_rx_edit.GetLineCount());

			plist->RemoveAt(current_pos);
		}
		Sleep(10);
	}
	return true;
}


UINT TXThread(LPVOID arg)
{
	ThreadArg* pArg = (ThreadArg*)arg;
	CStringList* plist = pArg->pList;
	CUDPServerthdDlg* pDlg = (CUDPServerthdDlg*)pArg->pDlg;

	while (pArg->Thread_run)	// Thread running
	{
		POSITION pos = plist->GetHeadPosition();
		POSITION current_pos;

		while (pos != NULL)
		{
			current_pos = pos;
			tx_cs.Lock();	// CS Lock
			CString str = plist->GetNext(pos);
			pDlg->m_pDataSocket->SendToEx((LPCTSTR)str, (str.GetLength() + 1) * sizeof(TCHAR), CLIENTPORT, PeerAddr, 0);
			tx_cs.Unlock(); // CS Unlock
			plist->RemoveAt(current_pos);
		}
		Sleep(10);
	}
	return true;
}

// CUDPServerthdDlg 메시지 처리기

BOOL CUDPServerthdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_pDataSocket = NULL;
	CStringList* newlist = new CStringList;
	arg1.pList = newlist;
	arg1.Thread_run = 1;
	arg1.pDlg = this;

	CStringList* newlist2 = new CStringList;
	arg2.pList = newlist2;
	arg2.Thread_run = 1;
	arg2.pDlg = this;

	WSADATA wsa;
	int error_code;
	if ((error_code = WSAStartup(MAKEWORD(2, 2), &wsa)) != 0)
	{
		TCHAR buffer[256];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, 256, NULL);
		AfxMessageBox(buffer, MB_ICONERROR);
	}

	m_pDataSocket = new CDataSocket(this);
	m_pDataSocket->Create(SERVERPORT, SOCK_DGRAM);
	AfxMessageBox(_T("서버를 시작합니다"), MB_ICONINFORMATION);
	pThread1 = AfxBeginThread(TXThread, (LPVOID)&arg1);
	pThread2 = AfxBeginThread(RXThread, (LPVOID)&arg2);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CUDPServerthdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CUDPServerthdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CUDPServerthdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUDPServerthdDlg::ProcessReceive(CDataSocket* pSocket, int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	TCHAR pBuf[1024 + 1];
	CString strData;
	int nbytes;
	UINT PeerPort;


	PeerAddr = _T("127.0.0.1");	// default Peer Addr
	PeerPort = CLIENTPORT;		// default Peer Port
	nbytes = pSocket->ReceiveFromEx(pBuf, 1024, PeerAddr, PeerPort);
	pBuf[nbytes] = NULL;

	strData = (LPCTSTR)pBuf;

	rx_cs.Lock();	// CS Lock
	arg2.pList->AddTail((LPCTSTR)strData);
	rx_cs.Unlock(); // CS Unlock
}


void CUDPServerthdDlg::ProcessClose(CDataSocket* pSocket, int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	pSocket->Close();
	delete m_pDataSocket;
	m_pDataSocket = NULL;

	int len = m_rx_edit.GetWindowTextLengthW();
	CString message = _T("##접속 종료## \r\n\r\n");
	m_rx_edit.SetSel(len, len);		// select sel
	m_rx_edit.ReplaceSel(message);
}


void CUDPServerthdDlg::OnBnClickedSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString tx_message;
	CString tx_edit_msg;

	m_tx_edit_short.GetWindowText(tx_message); // 전송될 메세지
	m_tx_edit.GetWindowText(tx_edit_msg);
	m_tx_edit_short.LineScroll(m_tx_edit_short.GetLineCount());
	tx_message += _T("\r\n");
	tx_edit_msg += tx_message;
	m_tx_edit.SetWindowTextW(tx_edit_msg);
	m_tx_edit.LineScroll(m_tx_edit.GetLineCount());

	tx_cs.Lock();	// CS Lock
	arg1.pList->AddTail(tx_message);
	tx_cs.Unlock();	// CS Unlock

	tx_message += _T("\r\n");
	m_tx_edit_short.SetWindowTextW(_T(""));	// edit 초기화
	m_tx_edit_short.SetFocus();
}


void CUDPServerthdDlg::OnBnClickedDisconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDataSocket == NULL)
	{
		AfxMessageBox(_T("이미 접속 종료"));
	}
	else
	{
		arg1.Thread_run = 0;
		arg2.Thread_run = 0;
		m_pDataSocket->Close();	// socket close
		delete m_pDataSocket;
		m_pDataSocket = NULL;
	}
}
