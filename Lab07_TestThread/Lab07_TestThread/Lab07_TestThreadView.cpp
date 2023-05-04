
// Lab07_TestThreadView.cpp: CLab07TestThreadView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Lab07_TestThread.h"
#endif

#include "Lab07_TestThreadDoc.h"
#include "Lab07_TestThreadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LOOPCNT (200000)
#define DIVCNT (LOOPCNT/500)

// CLab07TestThreadView

IMPLEMENT_DYNCREATE(CLab07TestThreadView, CView)

BEGIN_MESSAGE_MAP(CLab07TestThreadView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CLab07TestThreadView 생성/소멸

CLab07TestThreadView::CLab07TestThreadView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CLab07TestThreadView::~CLab07TestThreadView()
{
}

BOOL CLab07TestThreadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CLab07TestThreadView 그리기

void CLab07TestThreadView::OnDraw(CDC* /*pDC*/)
{
	CLab07TestThreadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CLab07TestThreadView 인쇄

BOOL CLab07TestThreadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CLab07TestThreadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CLab07TestThreadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CLab07TestThreadView 진단

#ifdef _DEBUG
void CLab07TestThreadView::AssertValid() const
{
	CView::AssertValid();
}

void CLab07TestThreadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab07TestThreadDoc* CLab07TestThreadView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab07TestThreadDoc)));
	return (CLab07TestThreadDoc*)m_pDocument;
}
#endif //_DEBUG


UINT MyDraw(LPVOID arg)
{
	ThreadArg* pArg = (ThreadArg*)arg;
	CClientDC dc(pArg->pWnd);
	int x, y, i;
	CBrush brush1(RGB(255, 0, 0));
	CBrush brush2(RGB(0, 0, 255));

	// 서로 다른 위치에 느린 속도를 막대를 출력한다.
	switch (pArg->pos)
	{
	case 1:
		dc.SelectObject(&brush1);
		x = 50; y = 50;
		for (i = 0; i < LOOPCNT; i++)
		{
			int inc = i / DIVCNT;
			dc.Rectangle(x, y, x + inc, y + 20);
		}
		break;
	case 2:
		dc.SelectObject(&brush2);
		x = 50; y = 100;
		for (i = 0; i < LOOPCNT; i++)
		{
			int inc = i / DIVCNT;
			dc.Rectangle(x, y, x + inc, y + 20);
		}
		break;
	}
	return 0;
}

// CLab07TestThreadView 메시지 처리기


void CLab07TestThreadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CView::OnLButtonDown(nFlags, point);
	// 화면을 지운다
	CClientDC dc(this);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	CRect rect;
	GetClientRect(&rect);
	dc.Rectangle(&rect);

	// 첫 번째 스레드를 중지 상태로 생성한다.
	arg1.pWnd = this;
	arg1.pos = 1;
	pThread1 = AfxBeginThread(MyDraw, &arg1, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	// 두 번째 스레드를 중지 상태로 생성한다.
	arg2.pWnd = this;
	arg2.pos = 2;
	pThread2 = AfxBeginThread(MyDraw, &arg2, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	// 두 번째 스레드의 우선순위 레벨을 변경한다.
	//pThread2->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
	
	// 두 스레드의 실행을 재개한다.
	pThread1->ResumeThread();
	pThread2->ResumeThread();
}
