#pragma once
#include "SejongBankDlg.h"
#include "DepositClose.h"
// Menu 대화 상자

class Menu : public CDialog
{
	DECLARE_DYNAMIC(Menu)

public:
	Menu(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Menu();

	//void DlgBank(CSejongBankDlg* tmp);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Menu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAccView();
	afx_msg void OnBnClickedDepositOk();
	afx_msg void OnBnClickedSavingOk();
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedAccTrans();
	afx_msg void OnBnClickedDepositCancel();
	afx_msg void OnBnClickedSavingCancel();
	afx_msg void OnBnClickedLoan();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

