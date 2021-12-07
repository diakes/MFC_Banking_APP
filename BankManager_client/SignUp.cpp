// SignUp.cpp: 구현 파일
//

#include "pch.h"
#include "SejongBank.h"
#include "SignUp.h"
#include "afxdialogex.h"

#include "SejongBankDlg.h"
#include "SejongBank.h"
extern CSejongBankDlg* abc;

 //CSejongBankDlg *test;
//// SignUp 대화 상자

IMPLEMENT_DYNAMIC(SignUp, CDialog)

SignUp::SignUp(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SignUp, pParent)
	, m_pwcheck(_T(""))
	, m_pw(_T(""))
	, m_name(_T(""))
	, m_id(_T(""))
	, m_phone(_T(""))
	, m_accountnum(_T(""))
{

}

SignUp::~SignUp()
{
}

//void SignUp::DlgBank(CSejongBankDlg* tmp)
//{
//	test = tmp;
//}
void SignUp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE_SEJONG, m_picSejong);
	DDX_Text(pDX, IDC_EDIT_PWCHECK, m_pwcheck);
	DDX_Text(pDX, IDC_EDIT_PW, m_pw);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_phone);
	DDX_Text(pDX, IDC_EDIT_ACCOUNTNUM, m_accountnum);
}


BEGIN_MESSAGE_MAP(SignUp, CDialog)
ON_WM_PAINT()
ON_BN_CLICKED(IDC_BUTTON_SIGNUP, &SignUp::OnBnClickedButtonSignup)
ON_BN_CLICKED(IDC_BUTTON_IDCHECK, &SignUp::OnBnClickedButtonIdcheck)
ON_WM_ERASEBKGND()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// SignUp 메시지 처리기

void SignUp::OnPaint() //이미지 추가 함수로, 메시지->WM_PAINT->OnPaint->처리기추가
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CDC memDC;
	memDC.CreateCompatibleDC(m_picSejong.GetDC());
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_PIC_SEJONG);
	memDC.SelectObject(&bitmap);
	/*컨트롤 박스 사이즈 구하는 부분*/
	CStatic* staticSize = (CStatic*)GetDlgItem(IDC_PICTURE_SEJONG);
	CRect rect;
	staticSize->GetClientRect(rect);
	int iWidth = rect.Width();
	int iHeight = rect.Height();
	m_picSejong.GetDC()->StretchBlt(0, 0, iWidth, iHeight, &memDC, 0, 0, 230, 230, SRCCOPY);
}
void SignUp::OnBnClickedButtonIdcheck()// ID 중복확인 클릭시 함수
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_id.GetLength() < 4)
	{
		AfxMessageBox("아이디는 최소 4자리가 되어야 합니다.");
		return;
	}
	//GetDlgItem(IDC_EDIT_PW)->EnableWindow(TRUE);
	//GetDlgItem(IDC_EDIT_PWCHECK)->EnableWindow(TRUE);
	//
	//GetDlgItem(IDC_EDIT_PW)->SetFocus();
	//GetDlgItem(IDC_BUTTON_SIGNUP)->EnableWindow(TRUE);

	char pTmp[256];

	//pTmp에 전송할 데이터 입력
	memset(pTmp, '\0', 256);
	sprintf_s(pTmp, "%s", m_id);
	abc->SendInfo(SOC_IDCHECK, pTmp);
	//test->SendInfo(SOC_IDCHECK,pTmp);
	//dlg.SendInfo()


	Sleep(100);
}

void SignUp::OnBnClickedButtonSignup() //회원가입 클릭시, 비밀번호와 공백을 체크하는 함수
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_pwcheck.GetLength() == 0 || m_pw.GetLength() == 0)
	{
		AfxMessageBox("비밀번호는 비워 둘 수 없습니다.");
		GetDlgItem(IDC_EDIT_PW)->SetFocus();
		return;
	}
	else if (m_pw != m_pwcheck)
	{
		AfxMessageBox("비밀번호가 올바르지 않습니다.");
		GetDlgItem(IDC_EDIT_PWCHECK)->SetFocus();
		return;
	}
	else if (m_name.GetLength() == 0 || m_phone.GetLength() == 0 || m_accountnum.GetLength() == 0)
	{
		AfxMessageBox("개인정보를 비워 둘 수 없습니다.");
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return;
	}
	else
	{
		UpdateData(TRUE);
		char pTmp[256];
		int IDLength, PWLength, nameLength, accountLength, phoneLength;
		CString strTmp;

		//pTmp에 전송할 데이터 입력
		memset(pTmp, '\0', 256);
		IDLength = m_id.GetLength();
		PWLength = m_pw.GetLength();
		nameLength = m_name.GetLength();
		accountLength = m_accountnum.GetLength();
		phoneLength = m_phone.GetLength();
		if (IDLength >= 10 && PWLength >= 10)
			sprintf_s(pTmp, "%d%d%d%d%d%d%s%s%s%s%s", IDLength, PWLength, 0, nameLength, accountLength, phoneLength, m_id, m_pw, m_name, m_accountnum, m_phone);
		else if (IDLength < 10 && PWLength >= 10)
			sprintf_s(pTmp, "%d%d%d%d%d%d%d%s%s%s%s%s", 0, IDLength, PWLength, 0, nameLength, accountLength, phoneLength, m_id, m_pw, m_name, m_accountnum, m_phone);
		else if (IDLength >= 10 && PWLength < 10)
			sprintf_s(pTmp, "%d%d%d%d%d%d%d%s%s%s%s%s", IDLength, 0, PWLength, 0, nameLength, accountLength, phoneLength, m_id, m_pw, m_name, m_accountnum, m_phone);
		else
			sprintf_s(pTmp, "%d%d%d%d%d%d%d%d%s%s%s%s%s", 0, IDLength, 0, PWLength, 0, nameLength, accountLength, phoneLength, m_id, m_pw, m_name, m_accountnum, m_phone);
		//test->SendInfo(SOC_REGISTER, pTmp);
		abc->SendInfo(SOC_REGISTER, pTmp);
		AfxMessageBox("회원가입에 성공했습니다.", MB_ICONASTERISK);
	}
	CDialog::OnOK();
}


BOOL SignUp::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(220, 150, 150));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다

	return TRUE;
}


HBRUSH SignUp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);


	// TODO:  여기서 DC의 특성을 변경합니다.
	UINT nID = pWnd->GetDlgCtrlID();

	switch (nID)
	{
	case IDC_STATIC:
		pDC->SetBkColor(RGB(220, 150, 150));
		hbr = ::CreateSolidBrush(RGB(220, 150, 150));
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}