// Menu.cpp: 구현 파일
//

#include "pch.h"
#include "BankManager.h"
#include "Menu.h"
#include "afxdialogex.h"


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
	DDX_Control(pDX, IDC_BUTTON_NAME, m_btnName);
	//  DDX_Control(pDX, IDC_LIST1, m_list);
	//  DDX_Control(pDX, IDC_LIST1, m_MemberList);
	//  DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(Menu, CDialog)
	ON_BN_CLICKED(IDOK, &Menu::OnBnClickedOk)
ON_BN_CLICKED(IDC_BUTTON_NAME, &Menu::OnBnClickedButtonName)
ON_BN_CLICKED(IDC_BUTTON_ACCOUNT, &Menu::OnBnClickedButtonAccount)
ON_WM_ERASEBKGND()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

//배경화면 색상 지정 함수
BOOL Menu::OnEraseBkgnd(CDC* pDC) //배경화면의 색을 정하는 함수
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(125, 102, 102));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다
	return TRUE;
}
// 글씨 색을 정하는 함수
HBRUSH Menu::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  여기서 DC의 특성을 변경합니다.
	UINT nID = pWnd->GetDlgCtrlID();
	switch (nID)
	{
	case IDC_STATIC:
		pDC->SetBkColor(RGB(125, 102, 102));
		hbr = ::CreateSolidBrush(RGB(125, 102, 102));
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
void Menu::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}

#include "SName.h"
void Menu::OnBnClickedButtonName()  //이름 조회 버튼 클릭 시, 이름 조회창으로 이동
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SName* sn = new SName;
	sn->DoModal();
}

#include "SAccount.h"
void Menu::OnBnClickedButtonAccount() //계좌번호 조회 버튼 클릭 시, 계좌번호창으로 이동
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SAccount* sa = new SAccount;
	sa->DoModal();
}
