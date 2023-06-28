
// ARQUDPServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ARQUDPServer.h"
#include "ARQUDPServerDlg.h"
#include "afxdialogex.h"
#include "CDataSocket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCriticalSection tx_cs;
CCriticalSection rx_cs;
CString PeerAddr = _T("");
Frame sendFrame;
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


// CARQUDPServerDlg 대화 상자



CARQUDPServerDlg::CARQUDPServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARQUDPSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CARQUDPServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_tx_edit_short);
	DDX_Control(pDX, IDC_EDIT2, m_tx_edit);
	DDX_Control(pDX, IDC_EDIT3, m_rx_edit);
}

BEGIN_MESSAGE_MAP(CARQUDPServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CARQUDPServerDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_DISCONNECT, &CARQUDPServerDlg::OnBnClickedDisconnect)
END_MESSAGE_MAP()

UINT RXThread(LPVOID arg)
{
	ThreadArg* pArg = (ThreadArg*)arg;
	CStringList* plist = pArg->pList;
	CARQUDPServerDlg* pDlg = (CARQUDPServerDlg*)pArg->pDlg;


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
	CARQUDPServerDlg* pDlg = (CARQUDPServerDlg*)pArg->pDlg;

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

// CARQUDPServerDlg 메시지 처리기

BOOL CARQUDPServerDlg::OnInitDialog()
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

void CARQUDPServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CARQUDPServerDlg::OnPaint()
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
HCURSOR CARQUDPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CARQUDPServerDlg::OnBnClickedSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString tx_short_message;
	CString tx_edit_msg;
	m_tx_edit_short.GetWindowText(tx_short_message);	// get new tx message from send edit control
	m_tx_edit.GetWindowText(tx_edit_msg);		// get tx message from tx edit control

	m_tx_edit_short.LineScroll(m_tx_edit_short.GetLineCount());
	//tx_short_message += _T("\r\n");					// line change
	tx_edit_msg += tx_short_message;					// m_tx_edit msg + m_tx_edit_short msg
	m_tx_edit.SetWindowTextW(tx_edit_msg);		// set m_tx_edit msg
	m_tx_edit.LineScroll(m_tx_edit.GetLineCount());
	
	/*
	int WideCharToMultiByte(
    UINT   uCodePage,
    DWORD  dwFlags,
    PCWSTR pWideCharStr,
    int    cchWideChar,
    PSTR   pMultiByteStr,
    int    cchMultiByte,
    PCSTR  pDefaultChar,
    PBOOL  pUsedDefaultChar
	);
	*/
	int cstrLen = WideCharToMultiByte(CP_ACP, 0, tx_short_message, -1, NULL, 0, NULL, NULL);	// cstrLen = len + 1
	char* message = new char[cstrLen];															// dynamic memory allocation
	//printf("%d", cstrLen);
	WideCharToMultiByte(CP_ACP, 0, tx_short_message, -1, message, cstrLen, NULL, NULL);			// Unicode -> Multibyte/UTF-8
	printf("%s", message);

	//sendFrame.type = SEND;
	for (int i = 0; i < strlen(message) / FSIZE + 1; i++)
	{
		memcpy(sendFrame.p_buffer, message + i * FSIZE, FSIZE);
		sendFrame.seq_num = this->seqnum;//시퀀스 넘버
		this->seqnum = (this->seqnum + 1) % SEQNUMSIZE;//시퀀스넘버 사이즈를 넘어가면 다시 0부터 시작 0~15로 구성
		printf("%s", message);
		if (i == strlen(message) / FSIZE)
			sendFrame.more = 0;//마지막 프레임이라면 more을 0으로 표시
		else
			sendFrame.more = 1;//마지막 프레임이 아니라면 더 있다고 more을 1로 표시
		//sendFrame.checksum = this->calcul_checksum(&sendFrame);//체크섬
		tx_cs.Lock();
		arg1.pFrameList->AddTail(sendFrame);// 프레임으로 나눠서 각각의 Arg 프레임리스트에 저장
		tx_cs.Unlock();
	}

	
	m_tx_edit_short.SetWindowTextW(_T(""));	// edit 초기화
	m_tx_edit_short.SetFocus();
}


void CARQUDPServerDlg::OnBnClickedDisconnect()
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


void CARQUDPServerDlg::ProcessReceive(CDataSocket* pSocket, int nErrorCode)
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


void CARQUDPServerDlg::ProcessClose(CDataSocket* pSocket, int nErrorCode)
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
