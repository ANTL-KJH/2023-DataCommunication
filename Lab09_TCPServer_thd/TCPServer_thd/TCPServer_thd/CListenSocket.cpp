// CListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "TCPServer_thd.h"
#include "CListenSocket.h"
#include "TCPServer_thdDlg.h"
#include "CDataSocket.h"
#include "CListenSocket.h"
// CListenSocket

CListenSocket::CListenSocket(CTCPServerthdDlg* pDlg)
{
	m_pDlg = pDlg;
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	CSocket::OnAccept(nErrorCode);
	m_pDlg->ProcessAccept(nErrorCode);
}


void CTCPServerthdDlg::ProcessAccept(int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	CString PeerAddr;
	UINT PeerPort;
	CString str;

	ASSERT(nErrorCode == 0);
	if (m_pDataSocket == NULL)
	{
		m_pDataSocket = new CDataSocket(this);
		if (m_pListenSocket->Accept(*m_pDataSocket))
		{
			m_pDataSocket->GetPeerName(PeerAddr, PeerPort);
			str.Format(_T("### IP주소: %s, 포트 번호: %d ###\r\n"), PeerAddr, PeerPort);
			m_rx_edit.ReplaceSel(str);
			//m_rx_edit.SetWindowTextW(str);
		}
		else
		{
			delete m_pDataSocket;
			m_pDataSocket = NULL;
		}
	}
}