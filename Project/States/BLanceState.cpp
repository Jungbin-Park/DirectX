#include "pch.h"
#include "BLanceState.h"

#include <Engine/CTransform.h>
#include <Engine/CGameObject.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CAssetMgr.h>

BLanceState::BLanceState()
	: CState(STATE_TYPE::BOSSLANCESTATE)
	, m_vecSpawnedLance{}
	, m_LancePref(nullptr)
	, m_LanceSpacing(100.f)
	, m_LanceCount(3)
{
}

BLanceState::~BLanceState()
{
}

void BLanceState::Enter()
{
	// Lance
	m_LancePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\IceLance.pref");

	CGameObject* pTarget = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	if (pTarget != nullptr)
		m_Target = pTarget;

	InitLance();
}

void BLanceState::FinalTick()
{
}

void BLanceState::InitLance()
{
	GetOwner()->FlipBookComponent()->Play(8, 5, false);
	//GetOwner()->FlipBookComponent()->Play(10, 5, false);
	//GetOwner()->FlipBookComponent()->Play(12, 5, false);

	m_vecSpawnedLance.clear();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();

	float angle = 0.f;
	float xPos = vPos.x - 100.f;
	float yPos = vPos.y;

	for (int i = 0; i < m_LanceCount; i++)
	{
		CGameObject* pLance = InstantiateSkill(m_LancePref, 2, Vec3(xPos, yPos, 100.f), L"IceLance");
		m_vecSpawnedLance.push_back(pLance);
		xPos += 100.f;
		//angle += (XM_2PI / (float)m_LanceCount);
	}
}

void BLanceState::ShootLance()
{
	GetOwner()->FlipBookComponent()->Play(9, 5, false);
	//GetOwner()->FlipBookComponent()->Play(11, 5, false);
	//GetOwner()->FlipBookComponent()->Play(13, 5, false);


}

void BLanceState::Exit()
{
}


