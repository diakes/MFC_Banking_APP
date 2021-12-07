#pragma once
#include "SejongBankDlg.h"

// SignUp 대화 상자

class SignUp : public CDialog
{
	DECLARE_DYNAMIC(SignUp)

public:
	SignUp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SignUp();

	//void DlgBank(CSejongBankDlg* tmp);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SignUp };
#endif

protected:

	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

//	afx_msg void OnEnablePicture();
	//void DlgBank(CSejongBankDlg* tmp);
	CStatic m_picSejong;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonSignup();
	CString m_pwcheck;
	CString m_pw;
	CString m_name;
	CString m_id;
	CString m_phone;
	CString m_accountnum;
	afx_msg void OnBnClickedButtonIdcheck();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
