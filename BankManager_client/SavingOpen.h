#pragma once


// SavingOpen 대화 상자

class SavingOpen : public CDialog
{
	DECLARE_DYNAMIC(SavingOpen)

public:
	SavingOpen(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SavingOpen();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SavingOpen };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo2();
//	afx_msg void OnBnClickedOk2();
	CString m_strCombo1;
	CString m_strCombo2;
	CString m_strCombo3;
	CString m_price;
	CString m_rate;
	CString m_interest;
	afx_msg void OnCbnSelchangeCombo1();
//	afx_msg void OnCbnSelchangeCombo3();
//	CString m_combo4;
	CString m_strCombo4;
	afx_msg void OnBnClickedOk();
	CString m_time;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangePrice();
};
