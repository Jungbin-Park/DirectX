#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"



CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{
}

CEngine::~CEngine()
{

}

int CEngine::Init(HWND _wnd, POINT _ptResolution)
{
	m_hWnd = _wnd;
	m_ptResolution = _ptResolution;
	ChangeWindowScale(_ptResolution.x, _ptResolution.y);

	if (FAILED(CDevice::GetInst()->Init(m_hWnd, m_ptResolution.x, m_ptResolution.y)))
	{
		MessageBox(nullptr, L"장치 초기화 실패", L"CDevice 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Manager 초기화
	CPathMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CAssetMgr::GetInst()->Init();
	CLevelMgr::GetInst()->Init();
	CRenderMgr::GetInst()->Init();

	return S_OK;
}



void CEngine::Progress()
{
	// Manager
	CKeyMgr::GetInst()->Tick();
	CTimeMgr::GetInst()->Tick();
	CLevelMgr::GetInst()->Progress();

	// Collision
	CCollisionMgr::GetInst()->Tick();

	// Render
	CDevice::GetInst()->Clear();
	CRenderMgr::GetInst()->Tick();
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