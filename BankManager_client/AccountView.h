#pragma once

// AccountView 대화 상자

#include "SejongBankDlg.h"

class AccountView : public CDialog
{
	DECLARE_DYNAMIC(AccountView)

public:
	AccountView(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AccountView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AccountView };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	CListCtrl m_list;
//	CString m_name;
	//void DlgBank3(CSejongBankDlg* tmp);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedOk();
};
