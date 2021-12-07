// DepositOpen.cpp: 구현 파일
//

#include "pch.h"
#include "SejongBank.h"
#include "DepositOpen.h"
#include "afxdialogex.h"
#include "SejongBank.h"

extern CSejongBankDlg* abc;


// DepositOpen 대화 상자

IMPLEMENT_DYNAMIC(DepositOpen, CDialog)

DepositOpen::DepositOpen(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DepositOpen, pParent)
	, m_rate("예상 이자율")
	, m_interest("예상 이자 금액")
	, m_strCombo("")
	, m_price(_T(""))
{

	m_time = _T("");
}

DepositOpen::~DepositOpen()
{
}

void DepositOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_RATE, m_rate);
	DDX_Text(pDX, IDC_STATIC_INTEREST, m_interest);
	DDX_CBString(pDX, IDC_COMBO1, m_strCombo);
	DDX_Text(pDX, IDC_PRICE, m_price);
}

BEGIN_MESSAGE_MAP(DepositOpen, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DepositOpen::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &DepositOpen::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_PRICE, &DepositOpen::OnEnChangePrice)
END_MESSAGE_MAP()


BOOL DepositOpen::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DepositOpen::OnEnChangePrice()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCbnSelchangeCombo1();
}

void DepositOpen::OnCbnSelchangeCombo1() //리스트 DATA 클릭 시, 이벤트 발생 함수
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	double d_price;
	d_price = atoi(m_price); // 멤버변수에 바뀐 가격을 double 형으로 불러온다.

	/*멤버변수와 문자열 같을 때*/
	if (m_strCombo == "12개월")
	{
		m_time = "12";
		m_rate = "연 1.60%";
		d_price = d_price * 0.016;
		m_interest.Format("(세전) %.2lf 원", d_price);
		//m_interest = "(세전)16,043 원";
	}
	else if (m_strCombo == "24개월")
	{
		m_time = "24";
		m_rate = "연 1.65%";
		d_price = d_price * 0.0165 * 2;
		m_interest.Format("(세전) %.2lf 원", d_price);
		//m_interest = "(세전)33,045 원";
	}
	else if (m_strCombo == "36개월")
	{
		m_time = "36";
		m_rate = "연 1.70%";
		d_price = d_price * 0.017 * 3;
		m_interest.Format("(세전) %.2lf 원", d_price);
		//m_interest = "(세전)51,046 원";
	}

	
	UpdateData(FALSE);
}



void DepositOpen::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int price = atoi(m_price);
	if (m_strCombo != "12개월" && m_strCombo != "24개월" && m_strCombo != "36개월")
	{
		GetDlgItem(IDC_COMBO1)->SetFocus(); //선택해야 되는 부분을 줌인 해준다.
		return;
	}
	else if (price < 1000 || price > 10000000)
	{
		AfxMessageBox("금액은 1000원이상 10,000,000원 이하입니다.");
		GetDlgItem(IDC_PRICE)->SetFocus(); //선택해야 되는 부분을 줌인 해준다.
		return;
	}
	else
	{

		UpdateData(TRUE);
		char pTmp[256];
		int  IDLength, timeLength;

		//pTmp에 전송할 데이터 입력
		memset(pTmp, '\0', 256);
		IDLength = abc->m_strID.GetLength();
		// ID, 계좌번호, 금액
		timeLength = m_time.GetLength(); // dlg에 맞춰서 연결해주기
		if (IDLength >= 10)
			sprintf_s(pTmp, "%d%d%s%s%s", IDLength, timeLength, abc->m_strID, m_time, m_price);
		else
			sprintf_s(pTmp, "%d%d%d%s%s%s", 0, IDLength, timeLength, abc->m_strID, m_time, m_price);
		// timeLength는 10 이상으로 가정
		abc->SendInfo(SOC_Deposit_Application, pTmp);


		AfxMessageBox("예금 계좌 등록 성공!! " + m_price + "원 예금 되었습니다.", MB_ICONINFORMATION);
		CDialog::OnOK();

	}
}

BOOL DepositOpen::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(220, 150, 150));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다

	return TRUE;
}


HBRUSH DepositOpen::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	case IDC_STATIC_RATE:
		pDC->SetBkColor(RGB(220, 150, 150));
		hbr = ::CreateSolidBrush(RGB(220, 150, 150));
		break;
	case IDC_STATIC_INTEREST:
		pDC->SetBkColor(RGB(220, 150, 150));
		hbr = ::CreateSolidBrush(RGB(220, 150, 150));
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
