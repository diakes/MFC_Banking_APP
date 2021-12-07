// SAccount.cpp: 구현 파일
//

#include "pch.h"
#include "BankManager.h"
#include "SAccount.h"
#include "afxdialogex.h"


// SAccount 대화 상자

IMPLEMENT_DYNAMIC(SAccount, CDialog)

SAccount::SAccount(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SAccount, pParent)
	, m_account(_T(""))
{

}

SAccount::~SAccount()
{
}

void SAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST, m_list);
	//  DDX_Control(pDX, IDC_ACCOUNT, m_account);
	DDX_Text(pDX, IDC_ACCOUNT, m_account);
	DDX_Control(pDX, IDC_LIST, m_MemberList);
}


BEGIN_MESSAGE_MAP(SAccount, CDialog)
	ON_BN_CLICKED(IDOK, &SAccount::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_SEARCH, &SAccount::OnBnClickedSearch)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// SAccount 메시지 처리기
BOOL SAccount::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//리스트 컨트롤 헤더 설정
	m_MemberList.InsertColumn(0, "계좌 번호", LVCFMT_CENTER, 100);
	m_MemberList.InsertColumn(1, "이름", LVCFMT_LEFT, 100);
	m_MemberList.InsertColumn(2, "회원 아이디", LVCFMT_LEFT, 100);
	m_MemberList.InsertColumn(3, "회원 비밀번호", LVCFMT_LEFT, 100);
	m_MemberList.InsertColumn(4, "휴대폰 번호", LVCFMT_LEFT, 100);
	m_MemberList.InsertColumn(5, "잔액", LVCFMT_CENTER, 100);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
//배경화면의 색을 정하는 함수
BOOL SAccount::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(125, 102, 102));  // 클라이언트 영역 크기만큼 색으로 채운다

	return TRUE;
}
//글씨 색을 정하는 함수
HBRUSH SAccount::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void SAccount::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}

void SAccount::OnBnClickedSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CRecordset* recSet; //레코드셋을 받을 포인터
	CString strSQL; //쿼리문을 저장할 변수

	if (m_account.GetLength() == 0)
	{
		AfxMessageBox("계좌를 입력해주세요");
		return;
	}
	else
	{
		strSQL.Format("SELECT * FROM [Member] WHERE AccountNum='%s'", m_account);

		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);
		if (recSet->GetRecordCount() != 0) //같은 이름 값이 있다면
		{	
			CString strAccountNum; //계좌 번호
			CString strName;  //이름
			CString strID; //아이디
			CString strPassword; //아이디
			CString strPhoneNum; //휴대폰 번호
	
			CString strMoney; //계좌 금액

			int nIndex = 0;

			while (!recSet->IsEOF())
			{		
				recSet->GetFieldValue(_T("AccountNum"), strAccountNum);
				recSet->GetFieldValue(_T("ClientName"), strName);
				recSet->GetFieldValue(_T("ID"), strID);
				recSet->GetFieldValue(_T("PassWord"), strPassword);
				recSet->GetFieldValue(_T("PhoneNum"), strPhoneNum);
				recSet->GetFieldValue(_T("Money"), strMoney);

				m_MemberList.InsertItem(nIndex, strAccountNum, 1);
				m_MemberList.SetItemText(nIndex, 1, strName);
				m_MemberList.SetItemText(nIndex, 2, strID);
				m_MemberList.SetItemText(nIndex, 3, strPassword);
				m_MemberList.SetItemText(nIndex, 4, strPhoneNum);
				m_MemberList.SetItemText(nIndex, 5, strMoney);

				nIndex++;

				recSet->MoveNext();
			}
			recSet->Close();
		}
		else
		{
			AfxMessageBox("일치하는 계좌가 없습니다");
		}
	}
	// 데이터 베이스에 내에서 Update해야 함.
}
