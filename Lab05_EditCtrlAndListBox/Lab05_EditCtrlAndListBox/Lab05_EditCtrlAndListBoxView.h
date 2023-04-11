
// Lab05_EditCtrlAndListBoxView.h: CLab05EditCtrlAndListBoxView 클래스의 인터페이스
//

#pragma once


class CLab05EditCtrlAndListBoxView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CLab05EditCtrlAndListBoxView() noexcept;
	DECLARE_DYNCREATE(CLab05EditCtrlAndListBoxView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_LAB05_EDITCTRLANDLISTBOX_FORM };
#endif

// 특성입니다.
public:
	CLab05EditCtrlAndListBoxDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CLab05EditCtrlAndListBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit;
	CListBox m_listbox;
	afx_msg void OnEnChangeMyedit();
	afx_msg void OnEnMaxtextMyedit();
	CButton m_button;
	afx_msg void OnBnClickedButton1();
};

#ifndef _DEBUG  // Lab05_EditCtrlAndListBoxView.cpp의 디버그 버전
inline CLab05EditCtrlAndListBoxDoc* CLab05EditCtrlAndListBoxView::GetDocument() const
   { return reinterpret_cast<CLab05EditCtrlAndListBoxDoc*>(m_pDocument); }
#endif

