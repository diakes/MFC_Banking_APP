#pragma once


// SName 대화 상자

class SName : public CDialog
{
	DECLARE_DYNAMIC(SName)

public:
	SName(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SName();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SName };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	CListCtrl m_list;
//	afx_msg void OnLvnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedSearch();
	
	CString m_name;
	CListCtrl m_MemberList;
};
