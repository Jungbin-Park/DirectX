#include "pch.h"
#include "CSlashScript.h"

CSlashScript::CSlashScript()
	: CScript(UINT(SCRIPT_TYPE::SLASHSCRIPT))
	, m_Speed(1000.f)
	, m_Life(1.f)
	, m_Age(0.f)
{
}

CSlashScript::~CSlashScript()
{
}

void CSlashScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	Ptr<CMaterial> pMtrl = GetRenderComponent()->GetMaterial();

	if (nullptr != pMtrl)
	{
		Ptr<CTexture> pTexture = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Idle_Left.bmp", L"texture\\Idle_Left.bmp");
		pMtrl->SetTexParam(TEX_0, pTexture);
	}
}

void CSlashScript::Tick()
{
	m_Age += DT;
	if (m_Age >= m_Life)
		DeleteObject(GetOwner());
}

void CSlashScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	DeleteObject(_OtherObject);
}

void CSlashScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, 4, 1, _File);
}

void CSlashScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, 4, 1, _File);
}