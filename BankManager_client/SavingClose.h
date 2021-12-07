#pragma once


// SavingClose 대화 상자

class SavingClose : public CDialog
{
	DECLARE_DYNAMIC(SavingClose)

public:
	SavingClose(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SavingClose();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SavingClose };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
	CString m_combotext;
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
