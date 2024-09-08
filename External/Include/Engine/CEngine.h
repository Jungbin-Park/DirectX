#pragma once

typedef void(*OBJECT_SAVE)(FILE*, class CGameObject*);
typedef CGameObject* (*OBJECT_LOAD)(FILE*);

class CEngine
	: public CSingleton<CEngine>
{
	SINGLE(CEngine);
private:
	HWND			m_hWnd;
	POINT			m_ptResolution;

public:
	HWND GetMainWnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }

public:
	int Init(HWND _wnd, POINT _ptResolution, OBJECT_SAVE _SaveFunc, OBJECT_LOAD _LoadFunc);
	void Progress();
	void ChangeWindowScale(UINT _Width, UINT _Height);
};

