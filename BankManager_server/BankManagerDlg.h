
// BankManagerDlg.h: 헤더 파일
//

#pragma once


// CBankManagerDlg 대화 상자
class CBankManagerDlg : public CDialogEx
{
// 생성입니다.
public:
	CBankManagerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CSocServer m_socServer; // 서버용 소켓
	CSocCom* m_socCom; //통신용 소켓
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BANKMANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int checkcount(char fnum, char snum);
	void sendcountinfo(int iType);
	afx_msg void OnBnClickedOk();
	
	CString m_strSend;
//	LPARAM OnAccept(UINT wParam, LPARAM IParam);
	void Sendinfo(int iType);
//	LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
	CString m_strStatus;
	CString m_strID;
	CString m_strPassword;

	CString m_strName;
	CString m_strAccount_number;
	CString m_strPhone_number;
	CString m_strMoney;
	CString m_strTime;
	CString id_check;
	CString store_time;
	CString m_strAccount_Name;
	CString m_acctmp;
protected:
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAccept(WPARAM wParam, LPARAM lParam);
};
