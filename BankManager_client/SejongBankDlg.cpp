
// SejongBankDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SejongBank.h"
#include "SejongBankDlg.h"
#include "afxdialogex.h"
#include "SignUp.h"
#include "Menu.h"
#include "AccountView.h"
#include "AccountTransfer.h"
#include "DepositClose.h"
#include "SavingClose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

SignUp* sign = new SignUp();
extern AccountView* abc2;
extern DepositClose* depositview;
extern SavingClose* savingview;
int list_index = 0;
AccountTransfer* transfer;
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnPaint();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSejongBankDlg 대화 상자

CSejongBankDlg::CSejongBankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEJONGBANK_DIALOG, pParent)
	, m_strID(_T(""))
	, m_strPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	list_index = 0;
}

void CSejongBankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strID);
	DDX_Text(pDX, IDC_EDIT2, m_strPassword);
}

BEGIN_MESSAGE_MAP(CSejongBankDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_RECEIVE, &CSejongBankDlg::OnReceive)
	ON_BN_CLICKED(ID_LOGIN, &CSejongBankDlg::OnBnClickedLogin)
	ON_BN_CLICKED(ID_SIGNUP, &CSejongBankDlg::OnBnClickedSignup)
END_MESSAGE_MAP()


// CSejongBankDlg 메시지 처리기

BOOL CSejongBankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//transfer->DlgBank2(this);
	SetBackgroundColor(RGB(160, 46, 46));

	m_socCom.Create();
	// IP 주소와 포트 번호를 지정
	BOOL bConnect = m_socCom.Connect("127.0.0.1", 5000);

	if (bConnect)
	{
		m_socCom.Init(this->m_hWnd);
		m_strStatus = "접속성공";
		GetDlgItem(ID_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(ID_SIGNUP)->EnableWindow(TRUE);
	}
	else
	{
		m_strStatus = "접속실패";
		GetDlgItem(ID_LOGIN)->EnableWindow(FALSE);
		GetDlgItem(ID_SIGNUP)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSejongBankDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

HCURSOR CSejongBankDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "Menu.h" //로그인시 메뉴창


afx_msg LRESULT CSejongBankDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	// 접속된 곳에서 데이터가 도착했을 때
	char pTmp[256];
	int iType;


	//CMain* dlg = new CMain;
	CString strTmp, strLogin, strRegister;
	memset(pTmp, '\0', 256);

	// 데이터를 pTmp에 받는다.
	m_socCom.Receive(pTmp, 256);

	//AfxMessageBox(pTmp);

	// strTmp에 헤더를 저장한다.
	strTmp.Format("%c", pTmp[0]);
	if (strTmp == "L")
		iType = 10;
	else if (strTmp == "T")
		iType = 11;
	else
		iType = atoi(strTmp);

	// 받은 데이터의 헤더를 분석해 행동을 결정한다.

	if (iType == SOC_LOGIN)
	{
		strLogin.Format("%c", pTmp[3]);
		int iLogin = atoi(strLogin);


		if (iLogin == 1)
		{
			// 메인 작업
			//FindWindow("CMain", "계좌조회");
			CDialog::OnOK();
			Menu* menu = new Menu;
			menu->DoModal(); //DoModal()을 이용하여 창을 띄웁니다
		}
		else
		{
			AfxMessageBox(_T("로그인 실패"));
		}
	}
	else if (iType == SOC_REGISTER) {
		strRegister.Format("%c", pTmp[3]);
		int iRegister = atoi(strRegister);

		if (iRegister == 1)
		{
			AfxMessageBox(_T("회원가입 성공"));
			//dlg->DoModal();
		}
		else
		{
			AfxMessageBox(_T("회원가입 실패"));
		}
	}
	else if (iType == SOC_IDCHECK) {
		CString strCheck;
		strCheck.Format("%c", pTmp[3]);
		int iCheck = atoi(strCheck);

		if (iCheck == 1)
		{
			AfxMessageBox(_T("아이디 사용가능"));

			sign->GetDlgItem(IDC_EDIT_PW)->EnableWindow(TRUE);
			sign->GetDlgItem(IDC_EDIT_PWCHECK)->EnableWindow(TRUE);

			sign->GetDlgItem(IDC_EDIT_PW)->SetFocus();
			sign->GetDlgItem(IDC_BUTTON_SIGNUP)->EnableWindow(TRUE);

		}
		else
		{
			AfxMessageBox(_T("아이디 중복"));
		}
	}
	else if (iType == SOC_ACCOUNT_INFO)
	{
		int MoneyLength;
		int TimeLength;
		int AccountNameLength;
		CString str = "", id = "", money = "", time = "", account = "";


		// CString money에 한글자씩 받아오는 방식
		MoneyLength = checkcount(pTmp[1], pTmp[2]);
		for (int i = 0; i < MoneyLength; i++)
		{
			str.Format("%c", pTmp[i + 7]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
			money += str;
		}
		TimeLength = checkcount(pTmp[3], pTmp[4]);
		for (int i = 0; i < TimeLength; i++)
		{
			str.Format("%c", pTmp[i + 7 + MoneyLength]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
			time += str;
		}
		AccountNameLength = checkcount(pTmp[5], pTmp[6]);
		for (int i = 0; i < AccountNameLength; i++)
		{
			str.Format("%c", pTmp[i + 7 + (MoneyLength + TimeLength)]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
			account += str;
		}
		//AfxMessageBox(money);
		//AfxMessageBox(account);
		//AfxMessageBox(time);
		
		abc2->m_list.InsertItem(0, account);
		abc2->m_list.SetItemText(0, 1, time);
		abc2->m_list.SetItemText(0, 2, money);
		//list_index++;
		UpdateData(FALSE);
	}
	else if (iType == SOC_ACCOUNT_MOVE) // 계좌 이체
	{
		CString strMove;
		strMove.Format("%c", pTmp[3]);
		int iMove = atoi(strMove);

		if (iMove == 1) // 계좌이체 성공 시
		{
			AfxMessageBox(_T("계좌이체 성공"));
			//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);	// 현재 계좌이체 대화상자 닫기
		}
		else
		{
			AfxMessageBox(_T("잔액 부족!"));
		}
	}
	else if (iType == SOC_Deposit_Application) // 예금신청
	{
		CString strApply;
		strApply.Format("%c", pTmp[3]);
		int iApply = atoi(strApply);

		if (iApply == 1) // 예금신청 성공 시
		{
			AfxMessageBox(_T("예금신청 완료"));
			//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);	// 현재 계좌이체 대화상자 닫기
		}
		else
		{
			AfxMessageBox(_T("예금신청 실패"));
		}
	}
	else if (iType == SOC_Deposit_Delete) // 예금삭제
	{

		//	AfxMessageBox(pTmp);
			//돌돌돌
		CString dType, accountNum, strDelete;
		int IDLength, timeLength, count, nIndex;
		IDLength = m_strID.GetLength();

		//dType.Format("%c", pTmp[1]);

		if (pTmp[1] == 'c') // 이 부분이 안될 씨 dType.Compare(dType,"c") == 0으로 변경 // c: count
		{
			accountNum.Format("%s", pTmp + 2);
			//AfxMessageBox(accountNum);
			//depositview->m_combo.AddString(accountNum);
			depositview->m_combo.AddString(accountNum);
			

		}

		else if (pTmp[1] == 'p') // 이 부분이 안될 씨 dType.Compare(dType,"p") == 0으로 변경 // p: performance
		{
			strDelete.Format("%c", pTmp[4]);
			int iDelete = atoi(strDelete);

			if (iDelete == 1) // 예금해지 성공 시
			{
				AfxMessageBox(_T("예금해지 성공"));
			}
			else
			{
				AfxMessageBox(_T("예금해지 실패"));
			}
		}

	}
	else if (iType == SOC_Deposit_Application) // 예금신청
	{
		CString strApply;
		strApply.Format("%c", pTmp[3]);
		int iApply = atoi(strApply);

		if (iApply == 1) // 예금신청 성공 시
		{
			AfxMessageBox(_T("예금신청 완료"));
			//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);	// 현재 계좌이체 대화상자 닫기
		}
		else
		{
			AfxMessageBox(_T("예금신청 실패"));
		}
	}

	else if (iType == SOC_Saving_Application) // 적금신청
	{
		CString strApply;
		strApply.Format("%c", pTmp[3]);
		int iApply = atoi(strApply);

		if (iApply == 1) // 적금신청 성공 시
		{
			AfxMessageBox(_T("적금신청 완료"));
			//::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);	// 현재 계좌이체 대화상자 닫기
		}
		else
		{
			AfxMessageBox(_T("적금신청 실패"));
		}
	}
	else if (iType == SOC_Saving_Delete) // 적금삭제
	{

		CString dType, accountNum, strDelete;
		int IDLength, timeLength, count, nIndex;
		IDLength = m_strID.GetLength();

		//dType.Format("%c", pTmp[1]);
		//AfxMessageBox(pTmp);

		if (pTmp[1] == 'c') // 이 부분이 안될 씨 dType.Compare(dType,"c") == 0으로 변경 // c: count
		{
			accountNum.Format("%s", pTmp + 2);

			savingview->m_combo.AddString(accountNum);

		}

		else if (pTmp[1] == 'p') // 이 부분이 안될 씨 dType.Compare(dType,"p") == 0으로 변경 // p: performance
		{
			strDelete.Format("%c", pTmp[4]);
			int iDelete = atoi(strDelete);

			if (iDelete == 1) // 예금해지 성공 시
			{
				AfxMessageBox(_T("예금해지 성공"));
			}
			else
			{
				AfxMessageBox(_T("예금해지 실패"));
			}
		}
	}
	else if (iType == SOC_Loan) // 대출
	{
		CString strLoan;
		strLoan.Format("%c", pTmp[3]);
		int iLoan = atoi(strLoan);

		if (iLoan == 1) // 대출 가능 시
		{
			AfxMessageBox(_T("대출 완료"));
		}
		else
		{
			AfxMessageBox(_T("대출 불가능"));
		}
	}
	else if (iType == SOC_Loan_Delete) // 대출상환
	{

		CString strLoan;
		strLoan.Format("%c", pTmp[3]);
		int iLoan = atoi(strLoan);

		if (iLoan == 1) // 대출 가능 시
		{
			AfxMessageBox(_T("상환 완료"));
		}
		else
		{
			AfxMessageBox(_T("상환 불가능"));
		}
	}
	return TRUE;
}
void CSejongBankDlg::SendInfo(int iType, CString strTmp)
{
	// TODO: 여기에 구현 코드 추가.
	// 데이터 전송
	UpdateData(TRUE);
	char pTmp[256];

	memset(pTmp, '\0', 256);
	if (iType == 10)
		sprintf_s(pTmp, "%c%s", 'L', strTmp);
	else if (iType == 11)
		sprintf_s(pTmp, "%c%s", 'T', strTmp);
	else
		sprintf_s(pTmp, "%d%s", iType, strTmp);

	m_socCom.Send(pTmp, 256);
}

int CSejongBankDlg::checkcount(char fnum, char snum)
{
	// TODO: 여기에 구현 코드 추가.
	CString pfnum, psnum;
	pfnum.Format("%c", fnum); // 아이디 
	psnum.Format("%c", snum);
	int count = atoi(pfnum) * 10 + atoi(psnum);
	return count;
}

void CSejongBankDlg::OnBnClickedLogin()
{

	/*로그인이 성공한다면*/
	 //로그인창 끄기
	char pTmp[256];
	int IDLength;
	CString strTmp;

	//pTmp에 전송할 데이터 입력
	UpdateData(TRUE);
	memset(pTmp, '\0', 256);
	IDLength = m_strID.GetLength();
	if (IDLength >= 10)
		sprintf_s(pTmp, "%d%s%s", IDLength, m_strID, m_strPassword);
	else
		sprintf_s(pTmp, "%d%d%s%s", 0, IDLength, m_strID, m_strPassword);
	SendInfo(SOC_LOGIN, pTmp);


}

void CSejongBankDlg::OnBnClickedSignup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	sign->DoModal(); //DoModal()을 이용하여 창을 띄웁니다
}
