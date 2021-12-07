﻿// CSocServer.cpp: 구현 파일
//

#include "pch.h"
#include "BankManager.h"
#include "CSocServer.h"
#include <afxsock.h>
#include "BankManagerDlg.h"

// CSocServer

CSocServer::CSocServer()
{
}

CSocServer::~CSocServer()
{
}
void CSocServer::Init(HWND hWnd) {
	//메인 윈도우 포인터받기
	m_hWnd = hWnd;
}

void CSocServer::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Accept(m_socCom);
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);
	CSocket::OnAccept(nErrorCode);
}

CSocCom* CSocServer::GetAcceptSocCom() {
	return &m_socCom;
}