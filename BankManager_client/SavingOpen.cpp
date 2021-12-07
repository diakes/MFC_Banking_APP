// SavingOpen.cpp: 구현 파일
//

#include "pch.h"
#include "SejongBank.h"
#include "SavingOpen.h"
#include "afxdialogex.h"


// SavingOpen 대화 상자

IMPLEMENT_DYNAMIC(SavingOpen, CDialog)

SavingOpen::SavingOpen(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SavingOpen, pParent)
	, m_strCombo1(_T(""))
	, m_strCombo2(_T(""))
	, m_strCombo3(_T(""))
	, m_strCombo4(_T(""))
	, m_price(_T(""))
	, m_rate("예상 이자율")
	, m_interest(_T("예상 이자 금액"))

{

	m_time = _T("");
}

SavingOpen::~SavingOpen()
{
}

void SavingOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_strCombo1);
	DDX_CBString(pDX, IDC_COMBO2, m_strCombo2);
	DDX_CBString(pDX, IDC_COMBO3, m_strCombo3);	
	DDX_CBString(pDX, IDC_COMBO4, m_strCombo4);
	DDX_Text(pDX, IDC_PRICE, m_price);
	DDX_Text(pDX, IDC_RATE, m_rate);
	DDX_Text(pDX, IDC_STATIC_INTEREST, m_interest);

}


BEGIN_MESSAGE_MAP(SavingOpen, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &SavingOpen::OnCbnSelchangeCombo1)	
	ON_CBN_SELCHANGE(IDC_COMBO2, &SavingOpen::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDOK, &SavingOpen::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_PRICE, &SavingOpen::OnEnChangePrice)
END_MESSAGE_MAP()


// SavingOpen 메시지 처리기
void SavingOpen::OnEnChangePrice()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCbnSelchangeCombo1();
}

void SavingOpen::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	double d_price;
	d_price = atoi(m_price); // 멤버변수에 바뀐 가격을 double 형으로 불러온다.

	/*멤버변수와 문자열 같을 때*/
	if (m_strCombo1 == "12개월")
	{
		m_time = "12";
		m_rate = "연 1.70%";
		if (m_strCombo2 == "매달")
		{
			d_price = d_price * 0.017 * 12 * 0.5;
			m_interest.Format("(세전) %.2lf 원", d_price);
		}
		else if (m_strCombo2 == "매주")
		{
			d_price = d_price * 0.017 * 53 * 0.5;
			m_interest.Format("(세전) %.2lf 원", d_price);
		}
	}
	else if (m_strCombo1 == "24개월")
	{
		m_time = "24";
		m_rate = "연 1.80%";
		if (m_strCombo2 == "매달")
		{
			d_price = d_price * 0.018 * 24;
			m_interest.Format("(세전) %.2lf 원", d_price);
		}
		else if (m_strCombo2 == "매주")
		{
			d_price = d_price * 0.018 * 53;
			m_interest.Format("(세전) %.2lf 원", d_price);
		}
	}
	else if (m_strCombo1 == "36개월")
	{
		m_time = "36";
		m_rate = "연 1.90%";
		if (m_strCombo2 == "매달")
		{
			d_price = d_price * 0.019 * 36 * 1.5;
			m_interest.Format("(세전) %.2lf 원", d_price);
		}
		else if (m_strCombo2 == "매주")
		{
			d_price = d_price * 0.019 * 53 * 1.5;
			m_interest.Format("(세전) %.2lf 원", d_price);
		}
	}
	UpdateData(FALSE);
}



void SavingOpen::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_strCombo2 == "매달")
	{
		GetDlgItem(IDC_COMBO3)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO4)->ShowWindow(FALSE);
		OnCbnSelchangeCombo1();

	}
	else if (m_strCombo2 == "매주")
	{
		GetDlgItem(IDC_COMBO4)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO3)->ShowWindow(FALSE);
		OnCbnSelchangeCombo1();
	}
}

void SavingOpen::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	int price = atoi(m_price);//입력 받은 금액을 int형으로 변환한다.
	if (m_strCombo1 != "12개월" && m_strCombo1 != "24개월" && m_strCombo1 != "36개월")
	{
		
		GetDlgItem(IDC_COMBO1)->SetFocus();
		return;
	}
	else if (m_strCombo2 != "매달" && m_strCombo2 != "매주")
	{
		GetDlgItem(IDC_COMBO2)->SetFocus();
		GetDlgItem(IDC_COMBO2)->SetFocus();
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
		abc->SendInfo(SOC_Saving_Application, pTmp);

		AfxMessageBox("적금 계좌 등록 성공!! " + m_price + "원 적금 되었습니다.", MB_ICONASTERISK);
		CDialog::OnOK();
	}
}

BOOL SavingOpen::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(220, 150, 150));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다

	return TRUE;
}


HBRUSH SavingOpen::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	case IDC_RATE:
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

