#include "pch.h"
#include "CPlayerScript.h"

#include "CSlashScript.h"
#include <Engine/CFlipBookComponent.h>
#include <Engine/CTransform.h>


CPlayerScript::CPlayerScript()
	: CScript(UINT(SCRIPT_TYPE::PLAYERSCRIPT))
	, m_Speed(400.f)
	, m_DashSpeed(2000.f)
	, m_DashTime(0.f)
	, m_DashDuration(0.2f)
	, m_Attribute(0)
	, m_AtkState(AtkState::NONE)
	, m_State(eState::IDLE)
	, m_Direction(eDirection::DOWN)
	, m_AtkDashSpeed(1000.f)
	, m_AtkDashTime(0.f)
	, m_AtkDashDuration(0.2f)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Red", &m_Attribute);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "PlayerSpeed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "Slash", &m_SlashPref);
}

CPlayerScript::~CPlayerScript()
{
}



void CPlayerScript::Begin()
{
	m_SlashPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\Slash.pref");

	GetRenderComponent()->GetDynamicMaterial();

	LoadFlipBook();
}

void CPlayerScript::Tick()
{
	Move();

	Skill();
}

void CPlayerScript::Move()
{
	ChangeAttribute(m_Attribute);

	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_TAP(KEY::A))
	{
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
		FlipBookComponent()->Play(4, 10, true);
		m_State = eState::MOVE;
	}
	if (KEY_PRESSED(KEY::A))
	{
		m_Direction = eDirection::LEFT;
		vPos.x -= DT * m_Speed;
	}
	if (KEY_RELEASED(KEY::A))
	{
		FlipBookComponent()->Play(1, 10, true);
		m_State = eState::IDLE;
		m_Direction = eDirection::LEFT;
	}

	if (KEY_TAP(KEY::D))
	{
		Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		FlipBookComponent()->Play(4, 10, true);
		m_State = eState::MOVE;

	}
	if (KEY_PRESSED(KEY::D))
	{
		m_Direction = eDirection::RIGHT;
		vPos.x += DT * m_Speed;
	}
	if (KEY_RELEASED(KEY::D))
	{
		FlipBookComponent()->Play(1, 10, true);
		m_State = eState::IDLE;
		m_Direction = eDirection::RIGHT;

	}

	if (KEY_TAP(KEY::W))
	{
		FlipBookComponent()->Play(5, 10, true);
		m_State = eState::MOVE;

	}
	if (KEY_PRESSED(KEY::W))
	{
		m_Direction = eDirection::UP;
		vPos.y += DT * m_Speed;
	}
	if (KEY_RELEASED(KEY::W))
	{
		FlipBookComponent()->Play(2, 10, true);
		m_State = eState::IDLE;
		m_Direction = eDirection::UP;
	}

	if (KEY_TAP(KEY::S))
	{
		FlipBookComponent()->Play(3, 10, true);
		m_State = eState::MOVE;

	}
	if (KEY_PRESSED(KEY::S))
	{
		m_Direction = eDirection::DOWN;
		vPos.y -= DT * m_Speed;
	}
	if (KEY_RELEASED(KEY::S))
	{
		FlipBookComponent()->Play(0, 10, true);
		m_State = eState::IDLE;
		m_Direction = eDirection::DOWN;

	}

	if (m_State == eState::DASH)
	{
		if (m_DashTime >= m_DashDuration)
		{
			m_State = eState::IDLE;
			m_DashTime = 0.f;
		}
		else
		{
			switch (m_Direction)
			{
			case eDirection::UP:
				vPos.y += DT * m_DashSpeed;
				break;
			case eDirection::DOWN:
				vPos.y -= DT * m_DashSpeed;
				break;
			case eDirection::LEFT:
				vPos.x -= DT * m_DashSpeed;
				break;
			case eDirection::RIGHT:
				vPos.x += DT * m_DashSpeed;
				break;
			default:
				break;
			}

			m_DashTime += DT;
		}
	}

	if (KEY_TAP(KEY::LBTN))
	{
		if (m_AtkDashTime >= m_AtkDashDuration)
		{
			m_DashTime = 0.f;
		}
		else
		{
			switch (m_Direction)
			{
			case eDirection::UP:
				vPos.y += DT * m_AtkDashSpeed;
				break;
			case eDirection::DOWN:
				vPos.y -= DT * m_AtkDashSpeed;
				break;
			case eDirection::LEFT:
				vPos.x -= DT * m_AtkDashSpeed;
				break;
			case eDirection::RIGHT:
				vPos.x += DT * m_AtkDashSpeed;
				break;
			default:
				break;
			}

			m_DashTime += DT;
		}
	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_State = eState::DASH;
		m_DashTime = 0.f;
	}

	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::Skill()
{
	if (KEY_TAP(KEY::LBTN)) 
	{
		if (m_AtkState == AtkState::NONE)
			m_AtkState = AtkState::ATTACK1;
		else if (m_AtkState == AtkState::ATTACK1)
			m_AtkState = AtkState::ATTACK2;
		else if (m_AtkState == AtkState::ATTACK2)
			m_AtkState = AtkState::ATTACK1;

		Instantiate(m_SlashPref, 5, Transform()->GetRelativePos(), L"Slash");

		switch (m_AtkState)
		{
		case CPlayerScript::AtkState::ATTACK1:
		{
			switch (m_Direction)
			{
			case eDirection::UP:
				FlipBookComponent()->Play(10, 15, false);
				break;
			case eDirection::DOWN:
				FlipBookComponent()->Play(6, 15, false);
				break;
			case eDirection::LEFT:
				FlipBookComponent()->Play(8, 15, false);
				break;
			case eDirection::RIGHT:
				FlipBookComponent()->Play(8, 15, false);
				break;
			default:
				break;
			}
		}
			break;
		case CPlayerScript::AtkState::ATTACK2:
		{
			switch (m_Direction)
			{
			case eDirection::UP:
				FlipBookComponent()->Play(11, 15, false);
				break;
			case eDirection::DOWN:
				FlipBookComponent()->Play(7, 15, false);
				break;
			case eDirection::LEFT:
				FlipBookComponent()->Play(9, 15, false);
				break;
			case eDirection::RIGHT:
				FlipBookComponent()->Play(9, 15, false);
				break;
			default:
				break;
			}
		}
			break;
		default:
			break;
		}


	}
}

void CPlayerScript::CursorDirCheck()
{
}

void CPlayerScript::LoadFlipBook()
{
	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\idledown.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\idleright.flip");
	FlipBookComponent()->AddFlipBook(1, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\idleup.flip");
	FlipBookComponent()->AddFlipBook(2, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\movedown.flip");
	FlipBookComponent()->AddFlipBook(3, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\moveright.flip");
	FlipBookComponent()->AddFlipBook(4, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\moveup.flip");
	FlipBookComponent()->AddFlipBook(5, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\AttackD1.flip");
	FlipBookComponent()->AddFlipBook(6, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\AttackD2.flip");
	FlipBookComponent()->AddFlipBook(7, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\AttackR1.flip");
	FlipBookComponent()->AddFlipBook(8, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\AttackR2.flip");
	FlipBookComponent()->AddFlipBook(9, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\AttackU1.flip");
	FlipBookComponent()->AddFlipBook(10, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\AttackU2.flip");
	FlipBookComponent()->AddFlipBook(11, pFlipBook);

}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	DeleteObject(_OtherObject);

	Vec3 vScale = Transform()->GetRelativeScale();

	vScale += Vec3(10.f, 10.f, 0.f);
	Collider2D()->SetScale(Collider2D()->GetScale() + Vec3(10.f, 10.f, 0.f));

	Transform()->SetRelativeScale(vScale);
}

void CPlayerScript::ChangeAttribute(int _data)
{
	GetOwner()->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, _data);
}



void CPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
	SaveAssetRef(m_Texture, _File);
	SaveAssetRef(m_SlashPref, _File);
	//fwrite(&m_FlipBookComponent, sizeof(CFlipBookComponent), 1, _File);
}

void CPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
	LoadAssetRef(m_Texture, _File);
	LoadAssetRef(m_SlashPref, _File);
	//fread(&m_FlipBookComponent, sizeof(CFlipBookComponent), 1, _File);
}