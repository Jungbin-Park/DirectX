#include "pch.h"
#include "CBossScript.h"

#include <Engine/CState.h>
#include <Engine/CFSM.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <States/BSpawnState.h>
#include <States/BIdleState.h>
#include <States/BReadyState.h>
#include <States/BDashState.h>
#include <States/BLanceState.h>
#include <States/BWaterState.h>
#include <States/BSlashState.h>
#include <States/BHitState.h>
#include <States/BDeadState.h>

#include "CPlayerScript.h"
#include "CManagerScript.h"

#include "CWaterScript.h"
#include "CLanceScript.h"


CBossScript::CBossScript()
	: CScript(SCRIPT_TYPE::BOSSSCRIPT)
	, m_CrystalPref(nullptr)
	, m_Target(nullptr)
	, m_Dead(false)
	, m_HP(200.f)
	, m_Angle(0.f)
{
}

CBossScript::~CBossScript()
{
}

void CBossScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	SetName(L"CBossScript");

	FSM()->AddState(L"BSpawnState", new BSpawnState);
	FSM()->AddState(L"BIdleState", new BIdleState);
	FSM()->AddState(L"BReadyState", new BReadyState);
	FSM()->AddState(L"BDashState", new BDashState);
	FSM()->AddState(L"BLanceState", new BLanceState);
	FSM()->AddState(L"BWaterState", new BWaterState);
	FSM()->AddState(L"BSlashState", new BSlashState);
	FSM()->AddState(L"BHitState", new BHitState);
	FSM()->AddState(L"BDeadState", new BDeadState);

	LoadAnimation();

	m_CrystalPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\Crystal.pref");
	Instantiate(m_CrystalPref, 3, Transform()->GetRelativePos(), L"Crystal");

	CGameObject* pTarget = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	if (pTarget != nullptr)
		m_Target = pTarget;


	FSM()->ChangeState(L"BSpawnState");
	Collider2D()->SetActive(true);
}

void CBossScript::Tick()
{
	Vec3 vTargetPos = m_Target->Transform()->GetRelativePos();
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vDir = vTargetPos - vPos;
	float Dist = sqrt(vDir.x * vDir.x + vDir.y * vDir.y);
	vDir.Normalize();

	if (vDir.x > 0)
	{
		Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	}
	else
	{
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}



}

void CBossScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (!m_Dead)
	{
		if (_OtherObject->GetLayerIdx() == 5)
		{
			if (_OtherObject->GetName() == L"Slash")
			{
				CPlayerScript* TargetScript = nullptr;
				TargetScript = (CPlayerScript*)m_Target->GetScriptByName(L"CPlayerScript");
				int slashDmg = TargetScript->GetSlashDamage();
				m_HP -= slashDmg;
			}

			if (_OtherObject->GetName() == L"FireDragon")
			{
				m_HP -= 10;
			}

			if (_OtherObject->GetName() == L"FireBall")
			{
				m_HP -= 20;
			}

			if (m_HP <= 0.f)
			{
				FSM()->ChangeState(L"BDeadState");
				m_Dead = true;
				/*CGameObject* pManager = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"GameManager");
				CManagerScript* pScript = (CManagerScript*)pManager->GetScriptByName(L"ManagerScript");
				pScript->AddScore(1);*/
			}
			else
			{
				FSM()->ChangeState(L"BHitState");
			}
		}
	}
}

void CBossScript::LoadAnimation()
{
	// Spawn
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BSpawn.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);

	// Idle
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BIdle.flip");
	FlipBookComponent()->AddFlipBook(1, pFlipBook);

	// Hit
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BHit.flip");
	FlipBookComponent()->AddFlipBook(2, pFlipBook);

	// Dead
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BDead.flip");
	FlipBookComponent()->AddFlipBook(3, pFlipBook);

	// Dash
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BDashReady.flip");
	FlipBookComponent()->AddFlipBook(4, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BDashDown.flip");
	FlipBookComponent()->AddFlipBook(5, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BDashRight.flip");
	FlipBookComponent()->AddFlipBook(6, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BDashUp.flip");
	FlipBookComponent()->AddFlipBook(7, pFlipBook);

	// Lance
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BLanceDown1.flip");
	FlipBookComponent()->AddFlipBook(8, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BLanceDown2.flip");
	FlipBookComponent()->AddFlipBook(9, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BLanceRight1.flip");
	FlipBookComponent()->AddFlipBook(10, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BLanceRight2.flip");
	FlipBookComponent()->AddFlipBook(11, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BLanceUp1.flip");
	FlipBookComponent()->AddFlipBook(12, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BLanceUp2.flip");
	FlipBookComponent()->AddFlipBook(13, pFlipBook);

	// Slash
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BSlash1.flip");
	FlipBookComponent()->AddFlipBook(14, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BSlash2.flip");
	FlipBookComponent()->AddFlipBook(15, pFlipBook);

	// Water
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BWater1.flip");
	FlipBookComponent()->AddFlipBook(16, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\BWater2.flip");
	FlipBookComponent()->AddFlipBook(17, pFlipBook);
}

void CBossScript::SaveToFile(FILE* _File)
{
}

void CBossScript::LoadFromFile(FILE* _File)
{
}


