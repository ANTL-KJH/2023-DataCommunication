
// Lab08_TCP_GUI_ServerView.h: CLab08TCPGUIServerView 클래스의 인터페이스
//

#pragma once


class CLab08TCPGUIServerView : public CEditView
{
protected: // serialization에서만 만들어집니다.
	CLab08TCPGUIServerView() noexcept;
	DECLARE_DYNCREATE(CLab08TCPGUIServerView)

// 특성입니다.
public:
	CLab08TCPGUIServerDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CLab08TCPGUIServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Lab08_TCP_GUI_ServerView.cpp의 디버그 버전
inline CLab08TCPGUIServerDoc* CLab08TCPGUIServerView::GetDocument() const
   { return reinterpret_cast<CLab08TCPGUIServerDoc*>(m_pDocument); }
#endif

