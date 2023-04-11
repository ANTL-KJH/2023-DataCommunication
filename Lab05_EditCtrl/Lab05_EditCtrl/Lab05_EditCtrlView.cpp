
// Lab05_EditCtrlView.cpp: CLab05EditCtrlView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Lab05_EditCtrl.h"
#endif

#include "Lab05_EditCtrlDoc.h"
#include "Lab05_EditCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab05EditCtrlView

IMPLEMENT_DYNCREATE(CLab05EditCtrlView, CFormView)

BEGIN_MESSAGE_MAP(CLab05EditCtrlView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_STN_CLICKED(IDHELP, &CLab05EditCtrlView::OnStnClickedHelp)
	ON_EN_CHANGE(IDC_MYEDIT, &CLab05EditCtrlView::OnEnChangeMyedit)
	ON_EN_MAXTEXT(IDC_MYEDIT, &CLab05EditCtrlView::OnEnMaxtextMyedit)
END_MESSAGE_MAP()

// CLab05EditCtrlView 생성/소멸

CLab05EditCtrlView::CLab05EditCtrlView() noexcept
	: CFormView(IDD_LAB05_EDITCTRL_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CLab05EditCtrlView::~CLab05EditCtrlView()
{
}

void CLab05EditCtrlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYEDIT, m_edit);
	DDX_Control(pDX, IDC_MYSTATIC, m_static);
}

BOOL CLab05EditCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CLab05EditCtrlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_edit.SetLimitText(20);
}


// CLab05EditCtrlView 인쇄

BOOL CLab05EditCtrlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CLab05EditCtrlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CLab05EditCtrlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CLab05EditCtrlView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CLab05EditCtrlView 진단

#ifdef _DEBUG
void CLab05EditCtrlView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLab05EditCtrlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLab05EditCtrlDoc* CLab05EditCtrlView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab05EditCtrlDoc)));
	return (CLab05EditCtrlDoc*)m_pDocument;
}
#endif //_DEBUG


// CLab05EditCtrlView 메시지 처리기


void CLab05EditCtrlView::OnStnClickedHelp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLab05EditCtrlView::OnEnChangeMyedit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str;
	m_edit.GetWindowText(str);
	m_static.SetWindowTextW(str);
}


void CLab05EditCtrlView::OnEnMaxtextMyedit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MessageBox(_T("최대 길이 도달!"), _T("오류"), MB_ICONERROR);
}
