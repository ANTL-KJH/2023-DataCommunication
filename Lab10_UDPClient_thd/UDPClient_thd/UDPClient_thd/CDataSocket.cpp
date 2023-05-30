// CDataSocket.cpp: 구현 파일
//

#include "pch.h"
#include "UDPClient_thd.h"
#include "CDataSocket.h"
#include "UDPClient_thdDlg.h"

// CDataSocket

CDataSocket::CDataSocket(CUDPClientthdDlg* pDlg)
{
	m_pDlg = pDlg;
}

CDataSocket::~CDataSocket()
{
}


// CDataSocket 멤버 함수


void CDataSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	CSocket::OnReceive(nErrorCode);
	m_pDlg->ProcessReceive(this, nErrorCode);
}


void CDataSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	CSocket::OnClose(nErrorCode);
	m_pDlg->ProcessClose(this, nErrorCode);
}
