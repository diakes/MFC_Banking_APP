// Manual.cpp: 구현 파일
//

#include "pch.h"
#include "SejongBank.h"
#include "Manual.h"
#include "afxdialogex.h"


// Manual 대화 상자

IMPLEMENT_DYNAMIC(Manual, CDialog)

Manual::Manual(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Manual, pParent)
	, m_check5(FALSE)
{

}

Manual::~Manual()
{
}

void Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK5, m_check5);
}


BEGIN_MESSAGE_MAP(Manual, CDialog)
	ON_BN_CLICKED(IDOK, &Manual::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &Manual::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &Manual::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &Manual::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &Manual::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &Manual::OnBnClickedCheck5)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Manual 메시지 처리기

void Manual::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}

void Manual::OnBnClickedCheck5()
{
	UpdateData(TRUE);
	if(m_check5) //체크박스5가 TRUE가 되면 확인창이 활성화 된다.
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	else //체크박스5가 FALSE가 되면 해제
		GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void Manual::CheckFun() //체크박스 4개가 체크 되면 마지막 체크박스 해제해주는 함수
{
	// TODO: 여기에 구현 코드 추가.
	BOOL c1 = IsDlgButtonChecked(IDC_CHECK1) ? TRUE : FALSE;
	BOOL c2 = IsDlgButtonChecked(IDC_CHECK2) ? TRUE : FALSE;
	BOOL c3 = IsDlgButtonChecked(IDC_CHECK3) ? TRUE : FALSE;
	BOOL c4 = IsDlgButtonChecked(IDC_CHECK4) ? TRUE : FALSE;

	if (c1 && c2 && c3 && c4)
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
	else
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);//버튼 기능 해제
		CheckDlgButton(IDC_CHECK5, FALSE); //체크박스 체크 해제
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE); 
	}
}

void Manual::OnBnClickedCheck1()
{
	CheckFun();
}
void Manual::OnBnClickedCheck2()
{
	CheckFun();
}
void Manual::OnBnClickedCheck3()
{
	CheckFun();
}
void Manual::OnBnClickedCheck4()
{
	CheckFun();
}

BOOL Manual::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    CRect rect;
    GetClientRect(&rect);
    pDC->FillSolidRect(&rect, RGB(220, 150, 150));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다

    return TRUE;
}


HBRUSH Manual::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
    case IDC_CHECK1:
        pDC->SetBkColor(RGB(220, 150, 150));
        hbr = ::CreateSolidBrush(RGB(220, 150, 150));
        break;

    case IDC_CHECK2:
        pDC->SetBkColor(RGB(220, 150, 150));
        hbr = ::CreateSolidBrush(RGB(220, 150, 150));
        break;
    case IDC_CHECK3:
        pDC->SetBkColor(RGB(220, 150, 150));
        hbr = ::CreateSolidBrush(RGB(220, 150, 150));
        break;
    case IDC_CHECK4:
        pDC->SetBkColor(RGB(220, 150, 150));
        hbr = ::CreateSolidBrush(RGB(220, 150, 150));
        break;
    case IDC_CHECK5:
        pDC->SetBkColor(RGB(220, 150, 150));
        hbr = ::CreateSolidBrush(RGB(220, 150, 150));
        break;
    }
    // TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
    return hbr;
}