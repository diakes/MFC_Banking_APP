#pragma once

// CSocCom 명령 대상

class CSocCom : public CSocket
{
	HWND m_hWnd; //메인 윈도우 핸들
public:
	CSocCom();
	virtual ~CSocCom();
	void Init(HWND hWhd);
	virtual void OnReceive(int nErrorCode);
};


