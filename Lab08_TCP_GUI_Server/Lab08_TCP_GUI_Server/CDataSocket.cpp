// CDataSocket.cpp: 구현 파일
//

#include "pch.h"
#include "Lab08_TCP_GUI_Server.h"
#include "CDataSocket.h"
#include "CTCPServer2Doc"



 


// CDataSocket

CDataSocket::CDataSocket(CTCPServer2Doc *pDoc)
{
	m_pDoc = pDoc;
}

CDataSocket::~CDataSocket()
{
}


// CDataSocket 멤버 함수
