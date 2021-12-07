// Menu.cpp: 구현 파일
//

#include "pch.h"
#include "SejongBank.h"
#include "Menu.h"
#include "afxdialogex.h"
#include "SejongBankDlg.h"
#include "AccountView.h"
#include "DepositClose.h"
#include "SavingClose.h"
AccountView* abc2;
DepositClose* depositview;
SavingClose* savingview;
// Menu 대화 상자

IMPLEMENT_DYNAMIC(Menu, CDialog)

Menu::Menu(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Menu, pParent)
{

}

Menu::~Menu()
{
}

void Menu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Menu, CDialog)
	ON_BN_CLICKED(IDC_ACC_VIEW, &Menu::OnBnClickedAccView)
	ON_BN_CLICKED(IDC_DEPOSIT_OK, &Menu::OnBnClickedDepositOk)
	ON_BN_CLICKED(IDC_SAVING_OK, &Menu::OnBnClickedSavingOk)
	ON_BN_CLICKED(IDC_LOGOUT, &Menu::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_ACC_TRANS, &Menu::OnBnClickedAccTrans)
	ON_BN_CLICKED(IDC_DEPOSIT_CANCEL, &Menu::OnBnClickedDepositCancel)
	ON_BN_CLICKED(IDC_SAVING_CANCEL, &Menu::OnBnClickedSavingCancel)
	ON_BN_CLICKED(IDC_LOAN, &Menu::OnBnClickedLoan)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Menu 메시지 처리기

#include "AccountView.h"
void Menu::OnBnClickedAccView()	//계좌 조회 창
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	

	AccountView view;
	abc2 = &view;
	view.DoModal(); //DoModal()을 이용하여 창을 띄웁니다

}

#include "AccountTransfer.h"
void Menu::OnBnClickedAccTrans()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AccountTransfer* transfer = new AccountTransfer;
	transfer->DoModal(); //DoModal()을 이용하여 창을 띄웁니다
}

#include "Manual.h"
#include "DepositOpen.h"

void Menu::OnBnClickedDepositOk() //예금 신청 창
{
	Manual* manual = new Manual;
	DepositOpen* d_open = new DepositOpen;

	if(manual->DoModal()==IDOK) //이용약관을 띄워준후 OK를 누르면 예금신청란이 켜진다.
	{		
		d_open->DoModal();
		return;
	}
}

#include "SavingOpen.h"
void Menu::OnBnClickedSavingOk() //적금 신청 창
{
	Manual* manual = new Manual;
	SavingOpen* s_open = new SavingOpen;

	if (manual->DoModal() == IDOK) //이용약관을 띄워준후 OK를 누르면 적금신청란이 켜진다.
	{
		s_open->DoModal();
		return;
	}
}


#include "DepositClose.h"
void Menu::OnBnClickedDepositCancel()
{

	DepositClose DeC;
	depositview = &DeC;
	DeC.DoModal(); //DoModal()을 이용하여 창을 띄웁니다
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

#include "SavingClose.h"
void Menu::OnBnClickedSavingCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SavingClose SaC;
	savingview = &SaC;
	SaC.DoModal(); //DoModal()을 이용하여 창을 띄웁니다
}

#include "Loan.h"
void Menu::OnBnClickedLoan()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Loan* loan = new Loan;
	loan->DoModal(); //DoModal()을 이용하여 창을 띄웁니다
}

#include "SejongBankDlg.h"
void Menu::OnBnClickedLogout()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
	CSejongBankDlg* cse = new CSejongBankDlg;
	cse->DoModal(); //DoModal()을 이용하여 창을 띄웁니다

}


BOOL Menu::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(220, 150, 150));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다

	return TRUE;
}


HBRUSH Menu::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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