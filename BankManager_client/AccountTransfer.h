#pragma once
#include "SejongBankDlg.h"

// AccountTransfer 대화 상자

class AccountTransfer : public CDialog
{
	DECLARE_DYNAMIC(AccountTransfer)

public:
	AccountTransfer(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AccountTransfer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AccountTransfer };
#endif

protected:
	
	

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	//void DlgBank2(CSejongBankDlg* tmp);
	
	afx_msg void OnBnClickedOk();
	CString m_accountNum;
	CString m_price;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
