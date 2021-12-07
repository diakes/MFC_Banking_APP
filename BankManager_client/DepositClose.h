#pragma once


// DepositClose 대화 상자

class DepositClose : public CDialog
{
	DECLARE_DYNAMIC(DepositClose)

public:
	DepositClose(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DepositClose();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DepositClose };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CComboBox m_combo;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	CString m_combotext;
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
