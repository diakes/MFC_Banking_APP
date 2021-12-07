#pragma once


// Menu 대화 상자

class Menu : public CDialog
{
	DECLARE_DYNAMIC(Menu)

public:
	Menu(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Menu();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Menu };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonName();
	afx_msg void OnBnClickedButtonAccount();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CButton m_btnName;
//	CListBox m_list;
	CListBox m_list;
};
