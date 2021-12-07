
// BankManagerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "BankManager.h"
#include "BankManagerDlg.h"
#include "afxdialogex.h"
#include"Menu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int vitualnumber = 1555522345; //전역변수[예금계좌번호]
Menu* m = new Menu;
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	//	virtual BOOL OnInitDialog();
	//	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBankManagerDlg 대화 상자



CBankManagerDlg::CBankManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BANKMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strID = _T("");
	m_strTime = _T("");
	m_strMoney = _T("");
}

void CBankManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBankManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBankManagerDlg::OnBnClickedOk)
	ON_MESSAGE(UM_RECEIVE, &CBankManagerDlg::OnReceive)
	ON_MESSAGE(UM_ACCEPT, &CBankManagerDlg::OnAccept)
END_MESSAGE_MAP()


// CBankManagerDlg 메시지 처리기

BOOL CBankManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetBackgroundColor(RGB(125, 102, 102));

	m_socCom = NULL;
	//서버 소켓을 생성 (포트번호 5000)
	m_socServer.Create(5000);
	//클라이언트의 접속을 기다린다.
	m_socServer.Listen();
	//소켓 클래스와 메인 윈도우(여기에서는 CChatServerDig)를 연결한다
	m_socServer.Init(this->m_hWnd);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CBankManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBankManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBankManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBankManagerDlg::OnBnClickedOk() //로그인 버튼 클릭 시, MENU창으로 이동
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//Menu* m = new Menu;

	m->DoModal();
	CDialogEx::OnOK();
	
}




//LPARAM CBankManagerDlg::OnAccept(UINT wParam, LPARAM IParam) {
	////클라이언트에서 접속 요청이 왔을 때
 //  // m_strStatus = "접속성공";

	////통신용 소켓을 생성한뒤
	//m_socCom = new CSocCom;
	////서버소켓과 통신소켓을 연결한다.
	//m_socCom = m_socServer.GetAcceptSocCom();
	//m_socCom->Init(this->m_hWnd);

	//m_socCom->Send("접속성공", 256);

	//UpdateData(FALSE);
	//return TRUE;
//}



void CBankManagerDlg::Sendinfo(int iType)
{
	// TODO: 여기에 구현 코드 추가.
	char pTmp[256];
	int IDLength;
	UpdateData(TRUE);

	//pTmp에 전송할 데이터 입력
	memset(pTmp, '\0', 256);
	//AfxMessageBox(pTmp);
	if (iType == SOC_LOGIN) // 로그인
	{
		//if ((m_strID.Compare("admin") == 0) && (m_strPassword.Compare("0000") == 0))//로그인 성공시 //데이터 베이스를 이용해서 값을 변경해주어야 함!
		//{
		//   sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "1");
		//}
		//else// 로그인 실패시
		//{
		//   sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "0");
		//}

		CRecordset* recSet; //레코드셋을 받을 포인터
		CString strSQL; //쿼리문을 저장할 변수

		strSQL.Format("SELECT * FROM [Member] WHERE ID='%s' AND PassWord= '%s'", m_strID, m_strPassword);

		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);

		if (recSet->GetRecordCount() == 0)
		{
			sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "0");
			 m_socCom->Send(pTmp, 256);
			recSet->Close();

		}
		else {
			sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "1");
			 m_socCom->Send(pTmp, 256);
			recSet->Close();
		}
	}
	else if (iType == SOC_REGISTER) // 회원 가입
	{
		CString strSQL;

		strSQL.Format("INSERT INTO [Member] VALUES('%s', '%s', '%s', '%s', '%s','0','0','100000')", m_strID, m_strPassword, m_strName, m_strPhone_number, m_strAccount_number);

		g_dbAlbum.ExecuteSQL(strSQL);
		//위에 있는 값들을 데이터 베이스에 넣기 
		//str_ID = ;
		sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "1");
		m_socCom->Send(pTmp, 256);
	}
	else if (iType == SOC_IDCHECK)// ID중복 체크
	{
		//""안에 데이터 베이스를 검색(select 할 부분)이 있어야 함 // 

		CString strSQL;
		CRecordset* recSet;

		strSQL.Format("SELECT * FROM [Member] WHERE ID='%s'", m_strID);
		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);


		if (recSet->GetRecordCount() == 0)
		{
			sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "1");// ID 중복 X

			recSet->Close();

		}
		else {
			sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "0");//ID 중복

			recSet->Close();
		}
		m_socCom->Send(pTmp, 256);
	}
	else if (iType == SOC_ACCOUNT_INFO)// 정보를 보내 주기 위해서 사용함.
	{

		CTime data = CTime::GetCurrentTime();
		m_strTime.Format(_T("%d_%d_%d_%d_%d_%d"), data.GetYear(), data.GetMonth(), data.GetDay(),
			data.GetHour(), data.GetMinute(), data.GetSecond());
		int MoneyLength = m_strMoney.GetLength();
		int TimeLength = m_strTime.GetLength();
		int AccountNameLength = m_strAccount_Name.GetLength();
		sprintf_s(pTmp, "%d%d%d%d%d%s%s%s", iType, 0, MoneyLength, TimeLength, AccountNameLength, m_strMoney, m_strTime, m_strAccount_Name);
		 m_socCom->Send(pTmp, 256);
		 m_strTime = "";
		 store_time = "";
	}
	else if (iType == SOC_ACCOUNT_MOVE)
	{
		//데이터 베이스에서 확인 하기 

		CString strSQL;
		CRecordset* recSet;

		// 상대방 아이디와 계좌번호가 데이터베이스에 있으면 밑에 Identification != "" 조건문 실행 없으면 else문 실행

		/*strSQL.Format(" UPDATE [Member] SET [Money] = [Money]-'%s' WHERE [ID]='%s' ", m_strMoney, m_strID);
		g_dbAlbum.ExecuteSQL(strSQL);
		strSQL.Format("UPDATE [Member] SET [Money] = [Money]+'%s' WHERE [AccountNum] = '%s'", m_strMoney, m_strAccount_number);
		g_dbAlbum.ExecuteSQL(strSQL);*/

		//strSQL.Format("SELECT * FROM [Member] WHERE ID = '%s' ", m_strID);
		//recSet = new CRecordset(&g_dbAlbum);
		//recSet->Open(CRecordset::forwardOnly, strSQL);

		//이부분에서 DB와 연동을 해주어야 할거 같습니다.
		CString tmpmoney;
		int tmp;
		strSQL.Format("SELECT Money FROM [Member] WHERE ID='%s'", m_strID);
		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);


		while (!recSet->IsEOF()) {
			recSet->GetFieldValue("Money", tmpmoney);
			recSet->MoveNext();
		}


		if (atoi(tmpmoney) < atoi(m_strMoney)) // 잔액이 적을 때 전송을 못하게 세팅 해줌
		{
			sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "0");// 잘못된 메시지를 띄위기 위해서 사용
			m_socCom->Send(pTmp, 256);
		}

		else if (recSet->GetRecordCount() == 0)
		{
			sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "0");
			m_socCom->Send(pTmp, 256);
		}
		else // 그외는 편집 하게 해줌
		{
			strSQL.Format(" UPDATE [Member] SET [Money] = [Money]-'%s' WHERE [ID]='%s' ", m_strMoney, m_strID);
			g_dbAlbum.ExecuteSQL(strSQL);
			strSQL.Format("UPDATE [Member] SET [Money] = [Money]+'%s' WHERE [AccountNum] = '%s'", m_strMoney, m_strAccount_number);
			g_dbAlbum.ExecuteSQL(strSQL);

			sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "1");
			m_socCom->Send(pTmp, 256);
			// 데이터 베이스에 내에서 Update해야 함.
		}
		recSet->Close();
	}
	else if (iType == SOC_Deposit_Application)
	{
		CString strSQL;
		vitualnumber += 333;  //나중에 1:n 이 될경우 랜덤함수로 대체
		m_acctmp.Format("%d", vitualnumber);

		strSQL.Format("INSERT INTO [DepositAccount] VALUES('%s','%s','%s','%s')", m_strID, m_strTime, m_acctmp, m_strMoney);
		g_dbAlbum.ExecuteSQL(strSQL);

		sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "1"); // 완료 되었다는 것을 client에 보냄
	    m_socCom->Send(pTmp, 256);
		m_strTime = "";
		store_time = "";
	}
	else if (iType == SOC_Deposit_Delete)
	{


		sprintf_s(pTmp, "%d%c%d%d%s", iType, 'p', 0, 1, "1"); // 정상적으로 수행 되었다는 사실을 보냄

	  //  m_socCom->Send(pTmp, 256);
		//sprintf_s(pTmp, "%d%c%d%d%s",iType,'p',0,1,"0");// 잘못된 메시지를 띄위기 위해서 사용


	}

	else if (iType == SOC_Saving_Application)
	{
		/*데이터 베이스에 계좌 종류 "002" insert해주기 */
		//계좌 번호는 무작위로 10자 이상으로 insert 해주기;
		CString strSQL;
		vitualnumber += 333;  //나중에 1:n 이 될경우 랜덤함수로 대체
		m_acctmp.Format("%d", vitualnumber);

		strSQL.Format("INSERT INTO [SavingAccount] VALUES('%s','%s','%s','%s')", m_strID, m_strTime, m_acctmp, m_strMoney);
		g_dbAlbum.ExecuteSQL(strSQL);

		sprintf_s(pTmp, "%d%d%d%s", iType, 0, 1, "1"); // 완료 되었다는 것을 client에 보냄
	   // m_socCom->Send(pTmp, 256);
		m_strTime = "";
		store_time = "";
	}
	else if (iType == SOC_Saving_Delete)
	{


		sprintf_s(pTmp, "%d%c%d%d%s", iType, 'p', 0, 1, "1"); // 정상적으로 수행 되었다는 사실을 보냄

		//m_socCom->Send(pTmp, 256);
	}
	else if (iType == SOC_Loan)
	{
		int money;
		money = atoi(m_strMoney);

		CString strSQL;
		CRecordset* recSet;
		CString moneytmp;
		strSQL.Format("SELECT Money FROM [Member] WHERE ID='%s'", m_strID);


		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);

		while (!recSet->IsEOF()) {

			recSet->GetFieldValue("Money", moneytmp);

			recSet->MoveNext();
		}
		recSet->Close();


		if (money > atoi(moneytmp)) //데이터베이스에 있는 금액)
		{
			sprintf_s(pTmp, "%c%d%d%s", 'L', 0, 1, "0"); // 대출 불가능한 것을 보냄
		    m_socCom->Send(pTmp, 256);
		}
		else
		{
			// database에 대출 처리 해주기
			sprintf_s(pTmp, "%c%d%d%s", 'L', 0, 1, "1"); // 대출 가능
			strSQL.Format("INSERT INTO [Loan] VALUES('%s','%s')", m_strID, m_strMoney);
			g_dbAlbum.ExecuteSQL(strSQL);
			 m_socCom->Send(pTmp, 256);
		}
	}
	else if (iType == SOC_Loan_Delete)
	{
		//데이터 베이스에서 확인 하기 
		

		CString strSQL;
		CRecordset* recSet;
		CString tmpmoney;
		int tmp;

		strSQL.Format("UPDATE [Loan] SET [Loan]=[Loan]-'%s' WHERE [ID]='%s' ", m_strMoney, m_strID);
		g_dbAlbum.ExecuteSQL(strSQL);

		sprintf_s(pTmp, "%c%d%d%s", 'T', 0, 1, "1"); // 상환 가능한 것을 보냄
	    m_socCom->Send(pTmp, 256);
	}

	//m_socCom->Send(pTmp, 256);
}

int CBankManagerDlg::checkcount(char fnum, char snum)// 헤더 안에 있는 변수 크기 추출 하기 위해서 사용
{
	CString pfnum, psnum;
	pfnum.Format("%c", fnum); // 아이디 
	psnum.Format("%c", snum);

	int count = atoi(pfnum) * 10 + atoi(psnum);

	return count;
}

void CBankManagerDlg::sendcountinfo(int iType)
{
	// TODO: 여기에 구현 코드 추가.
	//데이터 베이스로 계좌 갯수의  

	CString strSQL;
	CRecordset* recSet;
	CString AccNum;
	CString Money;
	char pTmp[256];
	memset(pTmp, '\0', 256);

	if (iType == SOC_Deposit_Delete) {
		strSQL.Format("SELECT DepositAccount FROM [DepositAccount] WHERE ID='%s'", m_strID);
		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);
		while (!recSet->IsEOF()) {
			AccNum = "";
			memset(pTmp, '\0', 256);
			recSet->GetFieldValue("DepositAccount", AccNum);

			sprintf_s(pTmp, "%d%c%s", iType, 'c', AccNum);

			m_socCom->Send(pTmp, 256);
			recSet->MoveNext();
		}
		recSet->Close();
	}

	else if (iType == SOC_Saving_Delete) {
		strSQL.Format("SELECT SavingAccount FROM [SavingAccount] WHERE ID='%s'", m_strID);
		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);
		while (!recSet->IsEOF()) {
			AccNum = "";
			memset(pTmp, '\0', 256);
			recSet->GetFieldValue("SavingAccount", AccNum);

			sprintf_s(pTmp, "%d%c%s", iType, 'c', AccNum);

			m_socCom->Send(pTmp, 256);
			recSet->MoveNext();
		}
		recSet->Close();
	}

	//m_socCom->Send(pTmp, 256);
}

afx_msg LRESULT CBankManagerDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	char pTmp[256];
	int iType;
	CString strTmp = "", str = "", id = "", password, name, account_number="", phone_number="", money = "";
	int lengh;
	memset(pTmp, '\0', 256);// 이것은 데이터의 끝이 256까지 아닐때를 대비 즉 데이터의 크기를 맞추어주는 것을 의미한다.

	m_socCom->Receive(pTmp, 256);//pTmp가 받는 대상의 크기이다.
	
	int i = m->m_list.GetCount();
	m->m_list.InsertString(i, pTmp);
	

	strTmp.Format("%c", pTmp[0]);
	//AfxMessageBox(strTmp);
	if (strTmp == "L")
		iType = 10;
	else if (strTmp == "T")
		iType = 11;
	else {
		iType = atoi(strTmp);
	}

	if (iType == SOC_LOGIN)
	{

		lengh = checkcount(pTmp[1], pTmp[2]); // 아이디 문자열 크기

		for (int i = 0; i < lengh; i++)
		{
			str.Format("%c", pTmp[i + 3]);
			id += str;
		}

		m_strID = id;

		password.Format("%s", pTmp + (lengh + 3));
		m_strPassword = password;



		Sendinfo(SOC_LOGIN);
	}
	else if (iType == SOC_REGISTER)
	{

		lengh = checkcount(pTmp[1], pTmp[2]); // ID

		for (int i = 0; i < lengh; i++)
		{
			str.Format("%c", pTmp[i + 11]);
			id += str;
		}

		m_strID = id;

		int lengh2 = checkcount(pTmp[3], pTmp[4]); // 비밀번호

		for (int i = 0; i < lengh2; i++)
		{
			str.Format("%c", pTmp[i + 11 + lengh]);
			password += str;
		}

		m_strPassword = password;

		int lengh3 = checkcount(pTmp[5], pTmp[6]);// 이름

		for (int i = 0; i < lengh3; i++)
		{
			str.Format("%c", pTmp[i + 11 + lengh + lengh2]);
			name += str;
		}

		m_strName = name;

		int lengh4 = checkcount(pTmp[7], pTmp[8]);// 계좌 번호

		for (int i = 0; i < lengh4; i++)
		{
			str.Format("%c", pTmp[i + 11 + lengh + lengh2 + lengh3]);
			account_number += str;
		}

		m_strAccount_number = account_number;

		str.Format("%s", pTmp + 11 + lengh + lengh2 + lengh3 + lengh4);   // 휴대폰 정보 확인
		phone_number = str;
		m_strPhone_number = phone_number;

		UpdateData(false);
		Sendinfo(SOC_REGISTER);
	}

	else if (iType == SOC_IDCHECK)
	{
		// ID전체를 보내줌

		str.Format("%s", pTmp + 1);
		id = str;

		m_strID = id;
		Sendinfo(SOC_IDCHECK);

	}
	else if (iType == SOC_ACCOUNT_INFO)
	{
		str.Format("%s", pTmp + 1);
		id = str;
		CString strTmp;


		m_strID = id;

		CString strSQL;
		CRecordset* recSet;
		CString AccNum;
		CString Money;
		// ID가 memberId인 사람의 계좌를 찾습니다.
		strSQL.Format("SELECT AccountNum,Money FROM [Member] WHERE ID='%s'", m_strID);
		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);


		while (!recSet->IsEOF()) {
			AccNum = "";
			Money = "";
			recSet->GetFieldValue("AccountNum", AccNum);
			recSet->GetFieldValue("Money", Money);

			m_strMoney = Money;
			m_strAccount_Name = AccNum;

			Sendinfo(SOC_ACCOUNT_INFO);

			recSet->MoveNext();
		}
		recSet->Close();


		// 적금 데이터베이스에서 id가 savingId인 사람의 계좌정보를 가져옴

		strSQL.Format("SELECT SavingAccount,Money FROM [SavingAccount] WHERE ID='%s'", m_strID);
		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);

		while (!recSet->IsEOF()) {
			AccNum = "";
			Money = "";
			recSet->GetFieldValue("SavingAccount", AccNum);
			recSet->GetFieldValue("Money", Money);

			m_strMoney = Money;
			m_strAccount_Name = AccNum;

			Sendinfo(SOC_ACCOUNT_INFO);

			recSet->MoveNext();
		}
		recSet->Close();

		// 예금 데이터베이스에서 id가 depositId인 사람의 계좌정보를 가져옴
		strSQL.Format("SELECT DepositAccount,Money FROM [DepositAccount] WHERE ID='%s'", m_strID);
		recSet = new CRecordset(&g_dbAlbum);
		recSet->Open(CRecordset::forwardOnly, strSQL);
		while (!recSet->IsEOF()) {
			AccNum = "";
			Money = "";
			recSet->GetFieldValue("DepositAccount", AccNum);
			recSet->GetFieldValue("Money", Money);

			m_strMoney = Money;
			m_strAccount_Name = AccNum;

			Sendinfo(SOC_ACCOUNT_INFO);

			recSet->MoveNext();
		}
		recSet->Close();

	}


	else if (iType == SOC_ACCOUNT_MOVE)
	{
		lengh = checkcount(pTmp[1], pTmp[2]); // ID

		for (int i = 0; i < lengh; i++)
		{
			str.Format("%c", pTmp[i + 5]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
			id += str;
		}

		m_strID = id;

		int lengh2 = checkcount(pTmp[3], pTmp[4]); // 이름

		for (int i = 0; i < lengh2; i++)
		{
			str.Format("%c", pTmp[i + 5 + lengh]);
			account_number += str;
		}

		m_strAccount_number = account_number;

		str.Format("%s", pTmp + 5 + lengh + lengh2);
		money = str;
		m_strMoney = money;//금액 정보 확인

		UpdateData(false);


		Sendinfo(SOC_ACCOUNT_MOVE);
	}


	else if (iType == SOC_Deposit_Application)// 예금 신청
	{
		//바위
		lengh = checkcount(pTmp[1], pTmp[2]); // ID

		for (int i = 0; i < lengh; i++)
		{
			str.Format("%c", pTmp[i + 4]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
			id += str;
		}

		m_strID = id;

		int lengh2 = pTmp[3] - '0'; // 시간

		for (int i = 0; i < lengh2; i++)
		{
			str.Format("%c", pTmp[i + 4 + lengh]);
			store_time += str;
		}

		m_strTime = store_time;

		str.Format("%s", pTmp + 4 + lengh + lengh2);
		money = str;
		m_strMoney = money;//금액 정보 확인

		UpdateData(false);

		Sendinfo(SOC_Deposit_Application);

	}
	else if (iType == SOC_Deposit_Delete)// 예금 삭제
	{
		//돌 receive
		str.Format("%c", pTmp[1]);
		if (str == 'i')
		{
			id_check.Format("%s", pTmp + 2);
			id = id_check;
			m_strID = id;
			sendcountinfo(iType);
		}
		else if (str == 'p')//이거 부분 때문에 안될시 str == 's' 를 str.Compare(str,"s") == 0 로 변경
		{
			lengh = checkcount(pTmp[2], pTmp[3]); // ID

			for (int i = 0; i < lengh; i++)
			{
				id_check.Format("%c", pTmp[i + 4]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
				id += id_check;
			}
			m_strID = id;

			CString a;
			a.Format("%s", pTmp + 4 + lengh);
			account_number = a;
			m_strAccount_number = account_number;

		
			CString strSQL;
			CRecordset* recSet;
			CString AccNum;
			strSQL.Format("SELECT Money FROM [DepositAccount] WHERE ID='%s' AND DepositAccount = '%s'", m_strID, m_strAccount_number);
			recSet = new CRecordset(&g_dbAlbum);
			recSet->Open(CRecordset::forwardOnly, strSQL);
			while (!recSet->IsEOF()) {
				recSet->GetFieldValue("Money", AccNum);

				recSet->MoveNext();
			}
			recSet->Close();

			strSQL.Format("UPDATE [Member] SET [Money] = [Money]+'%s' WHERE [ID] = '%s'", AccNum, m_strID);
			g_dbAlbum.ExecuteSQL(strSQL);
			strSQL.Format("DELETE FROM DepositAccount WHERE ID='%s' AND DepositAccount ='%s'", m_strID, m_strAccount_number);
			g_dbAlbum.ExecuteSQL(strSQL);

			Sendinfo(SOC_Deposit_Delete);
			UpdateData(false);
		}
	}
	else if (iType == SOC_Saving_Application)// 적금 신청
	{
		lengh = checkcount(pTmp[1], pTmp[2]); // ID

		for (int i = 0; i < lengh; i++)
		{
			str.Format("%c", pTmp[i + 4]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
			id += str;
		}

		m_strID = id;

		int lengh2 = pTmp[3] - '0'; // 시간

		for (int i = 0; i < lengh2; i++)
		{
			str.Format("%c", pTmp[i + 4 + lengh]);
			store_time += str;
		}

		m_strTime = store_time;

		str.Format("%s", pTmp + 4 + lengh + lengh2);
		money = str;
		m_strMoney = money;//금액 정보 확인

		UpdateData(false);

		Sendinfo(SOC_Saving_Application);
	}
	else if (iType == SOC_Saving_Delete)// 적금 삭제
	{
		str.Format("%c", pTmp[1]);
		if (str == 'i')
		{
			id_check.Format("%s", pTmp + 2);
			id = id_check;
			m_strID = id;
			sendcountinfo(iType);
		}
		else if (str == 'p')//이거 부분 때문에 안될시 str == 's' 를 str.Compare(str,"s") == 0 로 변경
		{
			lengh = checkcount(pTmp[2], pTmp[3]); // ID

			for (int i = 0; i < lengh; i++)
			{
				id_check.Format("%c", pTmp[i + 4]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
				id += id_check;
			}
			m_strID = id;

			CString a;
			a.Format("%s", pTmp + 4 + lengh);
			account_number = a;
			m_strAccount_number = account_number;

		
			CString strSQL;
			CRecordset* recSet;
			CString AccNum;
			strSQL.Format("SELECT Money FROM [SavingAccount] WHERE ID='%s' AND SavingAccount = '%s'", m_strID, m_strAccount_number);
			recSet = new CRecordset(&g_dbAlbum);
			recSet->Open(CRecordset::forwardOnly, strSQL);
			while (!recSet->IsEOF()) {
				recSet->GetFieldValue("Money", AccNum);

				recSet->MoveNext();
			}
			recSet->Close();

			strSQL.Format("UPDATE [Member] SET [Money] = [Money]+'%s' WHERE [ID] = '%s'", AccNum, m_strID);
			g_dbAlbum.ExecuteSQL(strSQL);
			strSQL.Format("DELETE FROM SavingAccount WHERE ID='%s' AND SavingAccount ='%s'", m_strID, m_strAccount_number);
			g_dbAlbum.ExecuteSQL(strSQL);

			Sendinfo(SOC_Saving_Delete);
			UpdateData(false);
		}
	}
	else if (iType == SOC_Loan)
	{
		lengh = checkcount(pTmp[1], pTmp[2]); // ID

		for (int i = 0; i < lengh; i++)
		{
			str.Format("%c", pTmp[i + 3]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
			id += str;
		}
		m_strID = id;
		str.Format("%s", pTmp + 3 + lengh);
		money = str;
		m_strMoney = money;


		Sendinfo(SOC_Loan);
	}
	else if (iType == SOC_Loan_Delete)
	{
		lengh = checkcount(pTmp[1], pTmp[2]); // ID

		for (int i = 0; i < lengh; i++)
		{
			str.Format("%c", pTmp[i + 3]); // 시작 위치는 최종 개수 +1 즉, 필요로한 갯수*2 -1로 함
			id += str;
		}
		m_strID = id;
		str.Format("%s", pTmp + 3 + lengh);
		money = str;
		m_strMoney = money;

		Sendinfo(SOC_Loan_Delete);
	}

	UpdateData(false);
	return 0;

}


afx_msg LRESULT CBankManagerDlg::OnAccept(WPARAM wParam, LPARAM lParam)
{
	//클라이언트에서 접속 요청이 왔을 때
// m_strStatus = "접속성공";

 //통신용 소켓을 생성한뒤
	m_socCom = new CSocCom;
	//서버소켓과 통신소켓을 연결한다.
	m_socCom = m_socServer.GetAcceptSocCom();
	m_socCom->Init(this->m_hWnd);

	m_socCom->Send("접속성공", 256);

	UpdateData(FALSE);
	return TRUE;
}
