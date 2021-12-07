
// SejongBankDlg.h: 헤더 파일
//

#pragma once

// CSejongBankDlg 대화 상자
class CSejongBankDlg : public CDialogEx
{
// 생성입니다.
public:

	CSejongBankDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CSocCom m_socCom;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEJONGBANK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
//	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedSignup();
	
	CString m_strID;
	CString m_strPassword;
	CString m_strStatus;
	CString m_strExample;
	void SendInfo(int iType, CString strTmp);
	afx_msg void OnClickedButtonLogin();
	int checkcount(char fnum, char snum);



//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	int list_index;
};
