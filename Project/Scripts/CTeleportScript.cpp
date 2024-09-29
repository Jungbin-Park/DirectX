#include "pch.h"
#include "CTeleportScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLayer.h>
#include <Engine/assets.h>


CTeleportScript::CTeleportScript()
	: CScript(SCRIPT_TYPE::TELEPORTSCRIPT)
{
}

CTeleportScript::~CTeleportScript()
{
	if(m_TPSound != nullptr)
 		m_TPSound->Stop();
}

void CTeleportScript::Begin()
{
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\TP.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	FlipBookComponent()->Play(0, 10, false);

	m_TPSound = CAssetMgr::GetInst()->FindAsset<CSound>(L"sound\\Teleport.mp3");
	m_TPSound->Play(1, 1, false);
}

void CTeleportScript::Tick()
{
	if (FlipBookComponent()->IsFinish())
	{
		DeleteObject(GetOwner());
	}
}


void CTeleportScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CTeleportScript::SaveToFile(FILE* _File)
{
}

void CTeleportScript::LoadFromFile(FILE* _File)
{
}


