
// Lab06_DialogCalculatorDlg.h: 헤더 파일
//

#pragma once


// CLab06DialogCalculatorDlg 대화 상자
class CLab06DialogCalculatorDlg : public CDialogEx
{
// 생성입니다.
public:
	CLab06DialogCalculatorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAB06_DIALOGCALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double m_num1;
	double m_num3;
	CComboBox m_ComboBox;
	double m_num2;
	CButton m_calculation;
	CButton m_clear;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
