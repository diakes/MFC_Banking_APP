#pragma once


// DepositOpen 대화 상자

class DepositOpen : public CDialog
{
	DECLARE_DYNAMIC(DepositOpen)

public:
	DepositOpen(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DepositOpen();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DepositOpen };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	CComboBox m_combo;
	CString m_rate;
	virtual BOOL OnInitDialog();

//	afx_msg void OnStnClickedStaticRate();
	CString m_interest;
	CString m_strCombo;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
	CString m_price;
	CString m_time;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangePrice();
};
