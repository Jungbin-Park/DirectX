#include "pch.h"
#include "CSpawnerScript.h"

CSpawnerScript::CSpawnerScript()
	: CScript(SCRIPT_TYPE::SPAWNERSCRIPT)
	, m_Finish(false)
	, m_GhoulPref(nullptr)
{
}

CSpawnerScript::~CSpawnerScript()
{
}

void CSpawnerScript::Begin()
{
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\SpawnMonster.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 10, false);

	m_GhoulPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\Ghoul.pref");
}

void CSpawnerScript::Tick()
{
	if (FlipBookComponent()->IsFinish() && !m_Finish)
	{
		m_Finish = true;

		Instantiate(m_GhoulPref, 4, Transform()->GetRelativePos(), L"Slash");

		DeleteObject(GetOwner());
	}
}

void CSpawnerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CSpawnerScript::SaveToFile(FILE* _File)
{
}

void CSpawnerScript::LoadFromFile(FILE* _File)
{
}



