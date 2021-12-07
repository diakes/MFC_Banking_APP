#pragma once


// SAccount 대화 상자

class SAccount : public CDialog
{
	DECLARE_DYNAMIC(SAccount)

public:
	SAccount(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SAccount();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAccount };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSearch();

	CString m_account;
	CListCtrl m_MemberList;

};
