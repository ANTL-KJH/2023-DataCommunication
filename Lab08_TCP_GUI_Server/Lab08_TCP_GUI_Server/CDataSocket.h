#pragma once

// CDataSocket 명령 대상
class CTCPServer2Doc;
class CDataSocket : public CSocket
{
public:
	CDataSocket();
	virtual ~CDataSocket();
	CTCPServer2Doc* m_pDoc;
};


