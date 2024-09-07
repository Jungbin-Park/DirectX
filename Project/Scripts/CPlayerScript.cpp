#include "pch.h"
#include "CPlayerScript.h"

#include "CMissileScript.h"
#include <Engine/CFlipBookComponent.h>


CPlayerScript::CPlayerScript()
	: CScript(UINT(SCRIPT_TYPE::PLAYERSCRIPT))
	, m_Speed(400.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "PlayerSpeed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "Missile", &m_MissilePref);
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Begin()
{
	GetRenderComponent()->GetDynamicMaterial();
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\idle.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\moveup.flip");
	FlipBookComponent()->AddFlipBook(1, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\movedown.flip");
	FlipBookComponent()->AddFlipBook(2, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\moveright.flip");
	FlipBookComponent()->AddFlipBook(3, pFlipBook);
	//m_MissilePref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"MissilePref");
}

void CPlayerScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	
	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::D))
	{
		FlipBookComponent()->FindFlipBook(L"moveright");
		FlipBookComponent()->Play(3, 10, true);
		vPos.x += DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::W))
	{
		FlipBookComponent()->FindFlipBook(L"moveup");
		FlipBookComponent()->Play(1, 10, true);
		vPos.y += DT * m_Speed;
	}
	if (KEY_PRESSED(KEY::S))
	{
		FlipBookComponent()->FindFlipBook(L"movedown");
		FlipBookComponent()->Play(2, 10, true);
		vPos.y -= DT * m_Speed;
	}
	else
	{

	}
		


	//if (KEY_TAP(KEY::SPACE))
	//{
	//	// 미사일 발사
	//	if (nullptr != m_MissilePref)
	//	{
	//		Instantiate(m_MissilePref, 5, Transform()->GetWorldPos(), L"Missile");
	//	}
	//}

	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	DeleteObject(_OtherObject);

	Vec3 vScale = Transform()->GetRelativeScale();

	vScale += Vec3(10.f, 10.f, 0.f);
	Collider2D()->SetScale(Collider2D()->GetScale() + Vec3(10.f, 10.f, 0.f));

	Transform()->SetRelativeScale(vScale);
}

void CPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
	SaveAssetRef(m_Texture, _File);
	SaveAssetRef(m_MissilePref, _File);
}

void CPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
	LoadAssetRef(m_Texture, _File);
	LoadAssetRef(m_MissilePref, _File);
}