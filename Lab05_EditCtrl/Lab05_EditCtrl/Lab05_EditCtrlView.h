
// Lab05_EditCtrlView.h: CLab05EditCtrlView 클래스의 인터페이스
//

#pragma once


class CLab05EditCtrlView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CLab05EditCtrlView() noexcept;
	DECLARE_DYNCREATE(CLab05EditCtrlView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_LAB05_EDITCTRL_FORM };
#endif

// 특성입니다.
public:
	CLab05EditCtrlDoc* GetDocument() const;

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
	virtual ~CLab05EditCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedHelp();
	CEdit m_edit;
	CStatic m_static;
	afx_msg void OnEnChangeMyedit();
	afx_msg void OnEnMaxtextMyedit();
};

#ifndef _DEBUG  // Lab05_EditCtrlView.cpp의 디버그 버전
inline CLab05EditCtrlDoc* CLab05EditCtrlView::GetDocument() const
   { return reinterpret_cast<CLab05EditCtrlDoc*>(m_pDocument); }
#endif

