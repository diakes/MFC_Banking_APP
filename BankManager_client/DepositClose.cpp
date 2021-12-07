// DepositClose.cpp: 구현 파일
//

#include "pch.h"
#include "SejongBank.h"
#include "DepositClose.h"
#include "afxdialogex.h"

extern CSejongBankDlg* abc;
// DepositClose 대화 상자

IMPLEMENT_DYNAMIC(DepositClose, CDialog)

DepositClose::DepositClose(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DepositClose, pParent)
	
{

	m_combotext = _T("");
}

DepositClose::~DepositClose()
{
}

void DepositClose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_CBString(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	
}


BEGIN_MESSAGE_MAP(DepositClose, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DepositClose::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &DepositClose::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// DepositClose 메시지 처리기


BOOL DepositClose::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	char pTmp[256];
	memset(pTmp, '\0', 256);
	sprintf_s(pTmp, "%c%s", 'i', abc->m_strID);
	abc->SendInfo(SOC_Deposit_Delete, pTmp);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DepositClose::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nComboCurSel = m_combo.GetCurSel(); 
	int nComboCurSelLen = m_combo.GetLBTextLen(nComboCurSel);
	m_combo.GetLBText(nComboCurSel, m_combotext);
	//AfxMessageBox(m_combotext);

	
}


void DepositClose::OnBnClickedOk()
{
	char pTmp[256];
	int IDLength;
	IDLength = abc->m_strID.GetLength();
	if (IDLength >= 10)
		sprintf_s(pTmp, "%c%d%s%s", 'p', IDLength, abc->m_strID, m_combotext);
	else
		sprintf_s(pTmp, "%c%d%d%s%s", 'p', 0, IDLength, abc->m_strID, m_combotext);
	abc->SendInfo(SOC_Deposit_Delete, pTmp);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}



BOOL DepositClose::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(220, 150, 150));  // 클라이언트 영역 크기만큼 RGB 색으로 채운다

	return TRUE;
}


HBRUSH DepositClose::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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