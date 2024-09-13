#include "pch.h"
#include "CSlashScript.h"

#include <Engine/CFlipBookComponent.h>
#include <Engine/CFlipBook.h>

int CSlashScript::m_SlashIdx = 1;

CSlashScript::CSlashScript()
	: CScript(UINT(SCRIPT_TYPE::SLASHSCRIPT))
	, m_Speed(1000.f)
{
}

CSlashScript::~CSlashScript()
{
}

void CSlashScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\WindSlash1.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\WindSlash2.flip");
	FlipBookComponent()->AddFlipBook(1, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\WindSlash3.flip");
	FlipBookComponent()->AddFlipBook(2, pFlipBook);


	FlipBookComponent()->Play(m_SlashIdx, 20, false);

	if (m_SlashIdx == 1)
		m_SlashIdx = 2;
	else
		m_SlashIdx = 1;
}

void CSlashScript::Tick()
{
	if (FlipBookComponent()->IsFinish())
		DeleteObject(GetOwner());
}

void CSlashScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	//DeleteObject(_OtherObject);
}

void CSlashScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, 4, 1, _File);
}

void CSlashScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, 4, 1, _File);
}