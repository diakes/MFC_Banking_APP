#pragma once


// Loan 대화 상자

class Loan : public CDialog
{
	DECLARE_DYNAMIC(Loan)

public:
	Loan(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Loan();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Loan };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CButton m_check;
	afx_msg void OnBnClickedCheck();
//	CButton m_apply;
//	CButton m_repay;
	BOOL m_check;
	afx_msg void OnBnClickedApply();
	CButton m_buttonApply;
	CButton m_buttonRepay;
//	CEdit m_strApply;
	CString m_strApply;
	CString m_strRepay;
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonRepay();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
