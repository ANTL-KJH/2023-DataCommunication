// CDataSocket.cpp: 구현 파일
//

#include "pch.h"
#include "ARQUDPClient.h"
#include "CDataSocket.h"


// CDataSocket

CDataSocket::CDataSocket(CARQUDPClientDlg* pDlg)
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
