// AccountTransfer.cpp: 구현 파일
//

#include "pch.h"
#include "SejongBank.h"
#include "AccountTransfer.h"
#include "afxdialogex.h"
//#include "SejongBankDlg.h"
#include "SejongBank.h"
extern CSejongBankDlg* abc;

//CSejongBankDlg* test2;

// AccountTransfer 대화 상자

IMPLEMENT_DYNAMIC(AccountTransfer, CDialog)

AccountTransfer::AccountTransfer(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_AccountTransfer, pParent)
	, m_accountNum(_T(""))
	, m_price(_T(""))
{

}

AccountTransfer::~AccountTransfer()
{
}

//void AccountTransfer::DlgBank2(CSejongBankDlg* tmp)
//{
//	test2 = tmp;
//}
void AccountTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ACCOUNTNUM, m_accountNum);
	DDX_Text(pDX, IDC_PRICE, m_price);
}


BEGIN_MESSAGE_MAP(AccountTransfer, CDialog)
	ON_BN_CLICKED(IDOK, &AccountTransfer::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// AccountTransfer 메시지 처리기


void AccountTransfer::OnBnClickedOk()
{
	UpdateData(TRUE);
	int price = atoi(m_price);

	if (m_price.GetLength() == 0)
	{
		AfxMessageBox("금액을 입력해주세요", MB_ICONQUESTION);
		GetDlgItem(IDC_PRICE)->SetFocus();
		return;
	}
	else if (m_accountNum.GetLength() == 0)
	{
		AfxMessageBox("계좌번호를 입력해주세요", MB_ICONQUESTION);
		GetDlgItem(IDC_ACCOUNTNUM)->SetFocus();
		return;
	}
	else
	{
		UpdateData(TRUE);
		char pTmp[256];
		int  IDLength,accountNumLength,moneyLength;
		//pTmp에 전송할 데이터 입력
		memset(pTmp, '\0', 256);
		IDLength = abc->m_strID.GetLength();
		//nameLength = m_.GetLength(); // 서버에서 가져와야 함
		accountNumLength = m_accountNum.GetLength(); // 서버에서 가져와야 함
		moneyLength = m_price.GetLength(); // 서버에서 가져와야 함
		// : 정보가 저장되어 있는 Info 대화 상자를 따로 만들까?
		
	//돌
		if(AfxMessageBox((m_price + "원을" + m_accountNum + "로 이체 하시겠습니까?"),MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			if (IDLength >= 10)
				sprintf_s(pTmp, "%d%d%s%s%s", IDLength, accountNumLength, abc->m_strID, m_accountNum, m_price);
			else
				sprintf_s(pTmp, "%d%d%d%s%s%s", 0, IDLength, accountNumLength, abc->m_strID, m_accountNum, m_price);
			
			abc->SendInfo(SOC_ACCOUNT_MOVE, pTmp);
			CDialog::OnOK();
		}
		else
		{
			return;
		}
	}
	UpdateData(FALSE);
}


BOOL AccountTransfer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(220, 150, 150));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다

	return TRUE;
}


HBRUSH AccountTransfer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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