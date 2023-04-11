
// Lab05_EditCtrlAndListBoxView.cpp: CLab05EditCtrlAndListBoxView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Lab05_EditCtrlAndListBox.h"
#endif

#include "Lab05_EditCtrlAndListBoxDoc.h"
#include "Lab05_EditCtrlAndListBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab05EditCtrlAndListBoxView

IMPLEMENT_DYNCREATE(CLab05EditCtrlAndListBoxView, CFormView)

BEGIN_MESSAGE_MAP(CLab05EditCtrlAndListBoxView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_EN_CHANGE(IDC_MYEDIT, &CLab05EditCtrlAndListBoxView::OnEnChangeMyedit)
	ON_EN_MAXTEXT(IDC_MYEDIT, &CLab05EditCtrlAndListBoxView::OnEnMaxtextMyedit)
	ON_BN_CLICKED(IDC_BUTTON1, &CLab05EditCtrlAndListBoxView::OnBnClickedButton1)
END_MESSAGE_MAP()

// CLab05EditCtrlAndListBoxView 생성/소멸

CLab05EditCtrlAndListBoxView::CLab05EditCtrlAndListBoxView() noexcept
	: CFormView(IDD_LAB05_EDITCTRLANDLISTBOX_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CLab05EditCtrlAndListBoxView::~CLab05EditCtrlAndListBoxView()
{
}

void CLab05EditCtrlAndListBoxView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYEDIT, m_edit);
	DDX_Control(pDX, IDC_LISTBOX, m_listbox);
	DDX_Control(pDX, IDC_BUTTON1, m_button);
}

BOOL CLab05EditCtrlAndListBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CLab05EditCtrlAndListBoxView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_edit.SetLimitText(30);

}


// CLab05EditCtrlAndListBoxView 인쇄

BOOL CLab05EditCtrlAndListBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CLab05EditCtrlAndListBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CLab05EditCtrlAndListBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CLab05EditCtrlAndListBoxView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CLab05EditCtrlAndListBoxView 진단

#ifdef _DEBUG
void CLab05EditCtrlAndListBoxView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLab05EditCtrlAndListBoxView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLab05EditCtrlAndListBoxDoc* CLab05EditCtrlAndListBoxView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab05EditCtrlAndListBoxDoc)));
	return (CLab05EditCtrlAndListBoxDoc*)m_pDocument;
}
#endif //_DEBUG


// CLab05EditCtrlAndListBoxView 메시지 처리기


void CLab05EditCtrlAndListBoxView::OnEnChangeMyedit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str;
	m_edit.GetWindowTextW(str);
}


void CLab05EditCtrlAndListBoxView::OnEnMaxtextMyedit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MessageBox(_T("최대 길이 도달!"), _T("오류"), MB_ICONERROR);	// error message
}


void CLab05EditCtrlAndListBoxView::OnBnClickedButton1()
{
	CString str;
	m_edit.GetWindowTextW(str);		// get string from editbox
	m_edit.SetSel(0, 30);			// select editbox
	m_edit.Clear();					// Editbox clear
	m_listbox.AddString(str);		// Add string without sorting
	m_listbox.SetCurSel(m_listbox.GetCount() - 1);	// auto scroll(select last element)
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
