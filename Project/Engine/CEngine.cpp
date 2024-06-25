#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"

#include "Temp.h"


CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{
}

CEngine::~CEngine()
{
	TempRelease();
}

int CEngine::Init(HWND _wnd, POINT _ptResolution)
{
	m_hWnd = _wnd;
	m_ptResolution = _ptResolution;
	ChangeWindowScale(_ptResolution.x, _ptResolution.y);

	if (FAILED(CDevice::GetInst()->Init(m_hWnd, m_ptResolution.x, m_ptResolution.y)))
	{
		MessageBox(nullptr, L"��ġ �ʱ�ȭ ����", L"CDevice �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CAssetMgr::GetInst()->Init();
	CLevelMgr::GetInst()->Init();


	if (FAILED(TempInit()))
	{
		MessageBox(nullptr, L"TempInit ����", L"CEngine �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}



void CEngine::Progress()
{
	// Manager
	CKeyMgr::GetInst()->Tick();
	CTimeMgr::GetInst()->Tick();

	CLevelMgr::GetInst()->Progress();
	TempTick();

	// Render
	CDevice::GetInst()->Clear();

	CLevelMgr::GetInst()->Render();
	TempRender();

	CDevice::GetInst()->Present();
}

void CEngine::ChangeWindowScale(UINT _Width, UINT _Height)
{
	bool bMenu = false;
	if (GetMenu(m_hWnd))
		bMenu = true;

	RECT rt = { 0, 0, (int)_Width, (int)_Height };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, bMenu);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}