#pragma once
#include <afxsock.h>
#include "CSocCom.h"

// CSocServer 명령 대상

class CSocServer : public CSocket
{
	
public:
	CSocServer();
	virtual ~CSocServer();
	HWND m_hWnd; //메인 윈도우 핸들
	CSocCom m_socCom; 
	void Init(HWND hWhd);
//	void OnAccept(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	CSocCom* GetAcceptSocCom();
};


