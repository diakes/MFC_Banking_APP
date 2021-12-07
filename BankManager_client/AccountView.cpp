// AccountView.cpp: 구현 파일
//

#include "pch.h"
#include "SejongBank.h"
#include "AccountView.h"
#include "afxdialogex.h"
#include "SejongBankDlg.h"
#include "SejongBank.h"
extern CSejongBankDlg* abc;
extern int list_index;

// AccountView 대화 상자

IMPLEMENT_DYNAMIC(AccountView, CDialog)

AccountView::AccountView(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_AccountView, pParent)
	
{

}

AccountView::~AccountView()
{
}

void AccountView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	//DDX_Text(pDX, IDC_NAME, m_name);
}


BEGIN_MESSAGE_MAP(AccountView, CDialog)
//	ON_WM_ERASEBKGND()
//	ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
ON_WM_ERASEBKGND()
ON_BN_CLICKED(IDOK, &AccountView::OnBnClickedOk)
END_MESSAGE_MAP()


// AccountView 메시지 처리기

BOOL AccountView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//리스트 컨트롤 헤더 설정
	m_list.InsertColumn(0, "계좌번호", LVCFMT_CENTER, 250);
	m_list.InsertColumn(1, "시간", LVCFMT_CENTER, 123);
	m_list.InsertColumn(2, "잔액", LVCFMT_CENTER, 123);
	//
	UpdateData(TRUE);
	char pTmp[256];

	//pTmp에 전송할 데이터 입력
	memset(pTmp, '\0', 256);
	sprintf_s(pTmp, "%s", abc->m_strID);
	//AfxMessageBox(pTmp);
	abc->SendInfo(SOC_ACCOUNT_INFO, pTmp);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



HBRUSH AccountView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL AccountView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
    GetClientRect(&rect);
    pDC->FillSolidRect(&rect, RGB(220, 150, 150));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다

   return TRUE;
}


void AccountView::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	list_index = 0;
	CDialog::OnOK();
}
