#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"

#include "CRenderMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTransform.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_Priority(-1)
	, m_LayerCheck(0)
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_Width(0)
	, m_Height(0)
	, m_Far(500)
	, m_FOV(XM_PI / 2.f)
{
	Vec2 vResolution = CDevice::GetInst()->GetResolution();
	m_Width = vResolution.x;
	m_Height = vResolution.y;
}

CCamera::~CCamera()
{
}

void CCamera::Begin()
{
	// 카메라 등록
	if (-1 != m_Priority)
	{
		CRenderMgr::GetInst()->RegisterCamera(this, m_Priority);
	}
	
}

void CCamera::FinalTick()
{
	/*Vec3 vWorldPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::LEFT))
		vWorldPos.x -= DT * 1.f;
	if (KEY_PRESSED(KEY::RIGHT))
		vWorldPos.x += DT * 1.f;

	Transform()->SetRelativePos(vWorldPos);*/

	// View Space
	// 1. 카메라가 원점에 존재 (카메라가 기준이 되는 좌표계)
	// 2. 카메라가 바라보는 방향이 z 축
	// 
	// View 행렬을 계산한다.
	// View 행렬은 World Space -> View Space로 변경할 때 사용하는 행렬
	m_matView = XMMatrixTranslation(-Transform()->GetRelativePos().x, -Transform()->GetRelativePos().y, -Transform()->GetRelativePos().z);


	// Projection Space 투영 좌표계 (NDC)
	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		// 1. 직교투영 (Orthographic)
		// 투영을 일직선으로
		// 시야 범위를 NDC 로 압축
		m_matProj = XMMatrixOrthographicLH(m_Width, m_Height, 1.f, m_Far);
	}
	
	else
	{
		// 2. 원근투영 (Perspective)
		float AspectRatio = m_Height / m_Width;
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, AspectRatio, 1.f, m_Far);
	}

}

void CCamera::Render()
{
	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;

	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (false == (m_LayerCheck & (1 << i)))
			continue;

		CLayer* pLayer = pLevel->GetLayer(i);

		const vector<CGameObject*>& vecObjects = pLayer->GetParentObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			vecObjects[j]->Render();
		}
	}
}
