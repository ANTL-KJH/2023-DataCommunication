
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Lab07_TimerCircle.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	POSITION pos = theApp.cir_lst.GetHeadPosition();		// get head pos
	CPoint point;
	while (pos != NULL)
	{
		point = theApp.cir_lst.GetNext(pos);
		dc.Ellipse(point.x - 20, point.y - 20, point.x + 20, point.y + 20);		// draw all circle in list 
	}
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

UINT delCir(LPVOID arg)
{
	ThreadArg* pArg = (ThreadArg*)arg;
	CClientDC dc(pArg->pWnd);


	Sleep(3000);	// wait 3 sec
	POSITION pos =  theApp.cir_lst.GetHeadPosition();
	theApp.cir_lst.RemoveAt(pos); // delete first circle


	InvalidateRect(*pArg->pWnd, NULL, TRUE);
	
	return 0;
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CWnd::OnLButtonDown(nFlags, point);
	CClientDC dc(this);
	dc.Ellipse(point.x - 20, point.y - 20, point.x + 20, point.y + 20);	// draw circle, 좌측 하단(x-20, y-20), 우측 상단(x+20, y+20)
	theApp.cir_lst.AddTail(point);
	
	arg.pWnd = this;
	pThread = AfxBeginThread(delCir, &arg);
	//pThread->ResumeThread();

}
