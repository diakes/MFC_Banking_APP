// Loan.cpp: 구현 파일
//

#include "pch.h"
#include "SejongBank.h"
#include "Loan.h"
#include "afxdialogex.h"

extern CSejongBankDlg* abc;
// Loan 대화 상자

IMPLEMENT_DYNAMIC(Loan, CDialog)

Loan::Loan(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Loan, pParent)
	, m_check(FALSE)
	, m_strApply(_T(""))
	, m_strRepay(_T(""))
{

}

Loan::~Loan()
{
}

void Loan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK, m_check);

	DDX_Control(pDX, IDC_BUTTON_APPLY, m_buttonApply);
	DDX_Control(pDX, IDC_BUTTON_REPAY, m_buttonRepay);

	DDX_Text(pDX, IDC_APPLY_PRICE, m_strApply);
	DDX_Text(pDX, IDC_REPAY_PRICE, m_strRepay);
}


BEGIN_MESSAGE_MAP(Loan, CDialog)
	ON_BN_CLICKED(IDC_CHECK, &Loan::OnBnClickedCheck)
	//ON_BN_CLICKED(IDC_APPLY, &Loan::OnBnClickedApply)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &Loan::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_REPAY, &Loan::OnBnClickedButtonRepay)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Loan 메시지 처리기

void Loan::OnBnClickedCheck()
{
	UpdateData(TRUE);
	if (m_check) //필수동의가 되면 대출 신청이 활성화 된다.
		GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(TRUE);
	else //체크박스5가 FALSE가 되면 해제
		GetDlgItem(IDC_BUTTON_APPLY)->EnableWindow(FALSE);
}

void Loan::OnBnClickedButtonApply() //대출 신청 버튼을 눌렀을 때
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	double price = atoi(m_strApply); //m_strApply는 사용자가 입력한 숫자의 값이다.
	if (price > 3000000)
	{
		AfxMessageBox("대출한도 초과!! 대출이 불가능합니다!");
		GetDlgItem(IDC_APPLY_PRICE)->SetFocus(); //선택해야 되는 부분을 줌인 해준다.
		return;
	}
	else if (m_strApply.GetLength() == 0 || price < 1)
	{
		AfxMessageBox("금액이 맞지않습니다");
		GetDlgItem(IDC_APPLY_PRICE)->SetFocus(); //선택해야 되는 부분을 줌인 해준다.
		return;
	}
	else
	{

		UpdateData(TRUE);
		char pTmp[256];
		int  IDLength;

		//pTmp에 전송할 데이터 입력
		memset(pTmp, '\0', 256);
		IDLength = abc->m_strID.GetLength();

		if (IDLength >= 10)
			sprintf_s(pTmp, "%d%s%s", IDLength, abc->m_strID, m_strApply);
		else
			sprintf_s(pTmp, "%d%d%s%s", 0, IDLength, abc->m_strID, m_strApply);

		abc->SendInfo(10, pTmp);
		AfxMessageBox("대출 신청 되었습니다!!", MB_ICONASTERISK);
	}
}


void Loan::OnBnClickedButtonRepay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//UpdateData(TRUE);
	double price = atoi(m_strRepay); //m_strApply는 사용자가 입력한 숫자의 값이다.
	//if (price > 3000000 || price < 1)
	//{
	//	AfxMessageBox("상환 금액이 맞지않습니다.");
	//	GetDlgItem(IDC_REPAY_PRICE)->SetFocus(); //선택해야 되는 부분을 줌인 해준다.
	//	return;
	//}
	////계좌 금액이 부족한 경우
	//else if (FALSE)
	//{
	//	AfxMessageBox("계좌금액이 부족하여 상환 불가능합니다");
	//	return;
	//}
	//else
	//{
	//	AfxMessageBox(m_strRepay +"원이 대출 상환 되었습니다", MB_ICONASTERISK);

	//}
	UpdateData(TRUE);
	char pTmp[256];
	int  IDLength;

	//pTmp에 전송할 데이터 입력
	memset(pTmp, '\0', 256);
	IDLength = abc->m_strID.GetLength();

	if (IDLength >= 10)
		sprintf_s(pTmp, "%d%s%s", IDLength, abc->m_strID, m_strRepay);
	else
		sprintf_s(pTmp, "%d%d%s%s", 0, IDLength, abc->m_strID, m_strRepay);

	abc->SendInfo(11, pTmp);

}


BOOL Loan::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(220, 150, 150));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다

	return TRUE;
}


HBRUSH Loan::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	case IDC_CHECK:
		pDC->SetBkColor(RGB(220, 150, 150));
		hbr = ::CreateSolidBrush(RGB(220, 150, 150));
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}