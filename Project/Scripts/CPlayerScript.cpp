#include "pch.h"
#include "CPlayerScript.h"

#include "CSlashScript.h"

#include <Engine/CDevice.h>
#include <Engine/CFlipBookComponent.h>
#include <Engine/CTransform.h>


CPlayerScript::CPlayerScript()
	: CScript(UINT(SCRIPT_TYPE::PLAYERSCRIPT))
	, m_Speed(400.f)
	, m_DashSpeed(1500.f)
	, m_DashTime(0.f)
	, m_DashDuration(0.2f)
	, m_Attribute(0)
	, m_AtkState(AtkState::NONE)
	, m_State(eState::IDLE)
	, m_Direction(eDirection::DOWN)
	, m_AttackDir(eDirection::RIGHT)
	, m_AtkDashSpeed(1000.f)
	, m_AtkDashTime(0.f)
	, m_AtkDashDuration(0.5f)
	, m_AttackFinish(true)
	, m_DashFinish(true)
	, m_KeyTapCount(0)
	, m_AttackCount(0)
	, m_SlashPos(Vec3(0.f, 0.f, 0.f))
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
	KeyInput();

	switch (m_State)
	{
	case CPlayerScript::eState::IDLE:
		Idle();
		break;
	case CPlayerScript::eState::MOVE:
		Move();
		break;
	case CPlayerScript::eState::ATTACK:
		Attack();
		break;
	case CPlayerScript::eState::DASH:
		Dash();
		break;
	default:
		break;
	}

	if (m_Direction == eDirection::LEFT ||
		m_Direction == eDirection::UP_LEFT ||
		m_Direction == eDirection::DOWN_LEFT)
	{
		Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
	}
	else
	{
		Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	}

}

void CPlayerScript::KeyInput()
{
	if (KEY_TAP(KEY::A))
	{
		m_KeyTapCount += 1;

		m_State = eState::MOVE;

		if (m_KeyTapCount == 2)
		{
			if (m_PrevDirection == eDirection::UP) m_Direction = eDirection::UP_LEFT;
			if (m_PrevDirection == eDirection::DOWN) m_Direction = eDirection::DOWN_LEFT;
			m_PrevDirection = m_Direction;
		}
		else
		{
			m_Direction = eDirection::LEFT;
			m_PrevDirection = m_Direction;
		}
		FlipBookComponent()->Play(4, 10, true);
	}
	if (KEY_RELEASED(KEY::A))
	{
		m_KeyTapCount -= 1;

		if (m_KeyTapCount == 0)
		{
			m_State = eState::IDLE;
			m_Direction = eDirection::LEFT;
			m_PrevDirection = m_Direction;
			FlipBookComponent()->Play(1, 10, true);
		}
		if (m_KeyTapCount == 1)
		{
			if (m_Direction == eDirection::UP_LEFT)
			{
				m_Direction = eDirection::UP;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(5, 10, true);
			}
			if (m_Direction == eDirection::DOWN_LEFT)
			{
				m_Direction = eDirection::DOWN;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(3, 10, true);
			}
		}
	}

	if (KEY_TAP(KEY::D))
	{
		m_KeyTapCount += 1;

		m_State = eState::MOVE;

		if (m_KeyTapCount == 2)
		{
			if (m_PrevDirection == eDirection::UP) m_Direction = eDirection::UP_RIGHT;
			if (m_PrevDirection == eDirection::DOWN) m_Direction = eDirection::DOWN_RIGHT;
			m_PrevDirection = m_Direction;
		}
		else
		{
			m_Direction = eDirection::RIGHT;
			m_PrevDirection = m_Direction;
		}
		FlipBookComponent()->Play(4, 10, true);
	}
	if (KEY_RELEASED(KEY::D))
	{
		m_KeyTapCount -= 1;

		if (m_KeyTapCount == 0)
		{
			m_State = eState::IDLE;
			m_Direction = eDirection::RIGHT;
			m_PrevDirection = m_Direction;
			FlipBookComponent()->Play(1, 10, true);
		}
		if (m_KeyTapCount == 1)
		{
			if (m_Direction == eDirection::UP_RIGHT)
			{
				m_Direction = eDirection::UP;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(5, 10, true);
			}
			if (m_Direction == eDirection::DOWN_RIGHT)
			{
				m_Direction = eDirection::DOWN;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(3, 10, true);
			}
		}
	}

	if (KEY_TAP(KEY::W))
	{
		m_KeyTapCount += 1;

		m_State = eState::MOVE;

		if (m_KeyTapCount == 2)
		{
			if (m_PrevDirection == eDirection::RIGHT) m_Direction = eDirection::UP_RIGHT;
			if (m_PrevDirection == eDirection::LEFT) m_Direction = eDirection::UP_LEFT;
		}
		else
		{
			m_Direction = eDirection::UP;
			m_PrevDirection = m_Direction;
		}

		if (m_KeyTapCount == 1)
			FlipBookComponent()->Play(5, 10, true);
	}
	if (KEY_RELEASED(KEY::W))
	{
		m_KeyTapCount -= 1;

		if (m_KeyTapCount == 0)
		{
			m_State = eState::IDLE;
			m_Direction = eDirection::UP;
			m_PrevDirection = m_Direction;
			FlipBookComponent()->Play(2, 10, true);
		}
		if (m_KeyTapCount == 1)
		{
			if (m_Direction == eDirection::UP_RIGHT)
			{
				m_Direction = eDirection::RIGHT;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(4, 10, true);
			}
			if (m_Direction == eDirection::UP_LEFT)
			{
				m_Direction = eDirection::LEFT;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(4, 10, true);
			}
		}
	}

	if (KEY_TAP(KEY::S))
	{
		m_KeyTapCount += 1;

		m_State = eState::MOVE;

		if (m_KeyTapCount == 2)
		{
			if (m_PrevDirection == eDirection::RIGHT) m_Direction = eDirection::DOWN_RIGHT;
			if (m_PrevDirection == eDirection::LEFT) m_Direction = eDirection::DOWN_LEFT;
		}
		else
		{
			m_Direction = eDirection::DOWN;
			m_PrevDirection = m_Direction;
		}

		if (m_KeyTapCount == 1)
			FlipBookComponent()->Play(3, 10, true);

	}
	if (KEY_RELEASED(KEY::S))
	{
		m_KeyTapCount -= 1;

		if (m_KeyTapCount == 0)
		{
			m_State = eState::IDLE;
			m_Direction = eDirection::DOWN;
			FlipBookComponent()->Play(0, 10, true);
		}
		if (m_KeyTapCount == 1)
		{
			if (m_Direction == eDirection::DOWN_RIGHT)
			{
				m_Direction = eDirection::RIGHT;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(4, 10, true);
			}
			if (m_Direction == eDirection::DOWN_LEFT)
			{
				m_Direction = eDirection::LEFT;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(4, 10, true);
			}
		}
	}

	if (KEY_TAP(KEY::LBTN))
	{
		MousePosCheck();

		m_State = eState::ATTACK;

		m_AtkDashTime = 0.f;

		if (m_AtkState == AtkState::NONE) m_AtkState = AtkState::ATTACK1;
		else if (m_AtkState == AtkState::ATTACK1) m_AtkState = AtkState::ATTACK2;
		else if (m_AtkState == AtkState::ATTACK2) m_AtkState = AtkState::ATTACK1;

		Instantiate(m_SlashPref, 5, Transform()->GetRelativePos(), L"Slash");

		switch (m_AtkState)
		{
		case CPlayerScript::AtkState::ATTACK1:
		{
			switch (m_AttackDir)
			{
			case eDirection::UP:
				FlipBookComponent()->Play(10, 40, false);
				break;
			case eDirection::DOWN:
				FlipBookComponent()->Play(6, 40, false);
				break;
			case eDirection::LEFT:
				Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
				FlipBookComponent()->Play(8, 40, false);
				break;
			case eDirection::RIGHT:
				FlipBookComponent()->Play(8, 40, false);
				break;
			default:
				break;
			}
		}
		break;
		case CPlayerScript::AtkState::ATTACK2:
		{
			switch (m_AttackDir)
			{
			case eDirection::UP:
				FlipBookComponent()->Play(11, 40, false);
				break;
			case eDirection::DOWN:
				FlipBookComponent()->Play(7, 40, false);
				break;
			case eDirection::LEFT:
				Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
				FlipBookComponent()->Play(9, 40, false);
				break;
			case eDirection::RIGHT:
				FlipBookComponent()->Play(9, 40, false);
				break;
			default:
				break;
			}
		}
		break;
		}
	}

	if (KEY_TAP(KEY::SPACE))
	{
		m_State = eState::DASH;
		m_DashFinish = false;

		m_DashTime = 0.f;

		switch (m_Direction)
		{
		case eDirection::UP:
			FlipBookComponent()->Play(14, 40, false);
			break;
		case eDirection::DOWN:
			FlipBookComponent()->Play(12, 40, false);
			break;
		case eDirection::LEFT:
		case eDirection::UP_LEFT:
		case eDirection::DOWN_LEFT:
			FlipBookComponent()->Play(13, 40, false);
			break;
		case eDirection::RIGHT:
		case eDirection::UP_RIGHT:
		case eDirection::DOWN_RIGHT:
			FlipBookComponent()->Play(13, 40, false);
			break;
		}
	}
}

void CPlayerScript::Idle()
{
	switch (m_Direction)
	{
	case eDirection::UP:
		FlipBookComponent()->Play(2, 10, true);
		break;
	case eDirection::DOWN:
		FlipBookComponent()->Play(0, 10, true);
		break;
	case eDirection::LEFT:
	case eDirection::UP_LEFT:
	case eDirection::DOWN_LEFT:
		FlipBookComponent()->Play(1, 10, true);
		break;
	case eDirection::RIGHT:
	case eDirection::UP_RIGHT:
	case eDirection::DOWN_RIGHT:
		FlipBookComponent()->Play(1, 10, true);
		break;
	default:
		break;
	}
}

void CPlayerScript::Move()
{
	ChangeAttribute(m_Attribute);

	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::A))
	{
		//m_Direction = eDirection::LEFT;
		m_State = eState::MOVE;
		vPos.x -= DT * m_Speed;
	}
	
	if (KEY_PRESSED(KEY::D))
	{
		//m_Direction = eDirection::RIGHT;
		m_State = eState::MOVE;
		vPos.x += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::W))
	{
		//m_Direction = eDirection::UP;
		m_State = eState::MOVE;
		vPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		//m_Direction = eDirection::DOWN;
		m_State = eState::MOVE;
		vPos.y -= DT * m_Speed;
	}


	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::Attack()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	m_AttackFinish = false;

	// 공격 끝났을 때
	if (m_AtkDashTime >= m_AtkDashDuration)
	{
		m_AtkDashTime = 0.f;

		if (FlipBookComponent()->IsFinish())
		{
			m_AttackFinish = true;

			// 누르고 있는 키가 없으면
			if (m_KeyTapCount == 0)
			{
				m_State = eState::IDLE;
				//FlipBookComponent()->Play(1, 10, true);
			}
			// 다른 키를 누르고 있을 경우
			else
			{
				m_State = eState::MOVE;

				switch (m_Direction)
				{
				case eDirection::UP:
					FlipBookComponent()->Play(5, 10, true);
					break;
				case eDirection::DOWN:
					FlipBookComponent()->Play(3, 10, true);
					break;
				case eDirection::LEFT:
					FlipBookComponent()->Play(4, 10, true);
					break;
				case eDirection::RIGHT:
					FlipBookComponent()->Play(4, 10, true);
					break;
				default:
					break;
				}
			}

		}
	}
	// 공격 시
	else
	{
		// 공격 방향으로 살짝 이동
		switch (m_AttackDir)
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

		m_AtkDashTime += DT;
	}

	

	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::Dash()
{
	Vec3 vPos = Transform()->GetRelativePos();

	// 대쉬 끝났을 때
	if (m_DashTime >= m_DashDuration)
	{
		m_DashTime = 0.f;

		if (FlipBookComponent()->IsFinish())
		{
			m_DashFinish = true;

			// 아무 키도 안눌려 있으면
			if (m_KeyTapCount == 0)
				m_State = eState::IDLE;
			// 다른 키를 누르고 있으면
			else
			{
				m_State = eState::MOVE;

				switch (m_Direction)
				{
				case eDirection::UP:
					FlipBookComponent()->Play(5, 10, true);
					break;
				case eDirection::DOWN:
					FlipBookComponent()->Play(3, 10, true);
					break;
				case eDirection::LEFT:
				case eDirection::UP_LEFT:
				case eDirection::DOWN_LEFT:
					FlipBookComponent()->Play(4, 10, true);
					break;
				case eDirection::RIGHT:
				case eDirection::UP_RIGHT:
				case eDirection::DOWN_RIGHT:
					FlipBookComponent()->Play(4, 10, true);
					break;
				default:
					break;
				}
			}
		}
		
	}
	else
	{
		if(m_Direction == eDirection::UP) vPos.y += DT * m_DashSpeed;
		if(m_Direction == eDirection::DOWN) vPos.y -= DT * m_DashSpeed;
		if(m_Direction == eDirection::LEFT) vPos.x -= DT * m_DashSpeed;
		if(m_Direction == eDirection::RIGHT) vPos.x += DT * m_DashSpeed;

		// 대각선 방향
		if (m_Direction == eDirection::UP_LEFT)
		{
			vPos.y += DT * m_DashSpeed * 0.707f;  // 45도일 때 √2/2 ≈ 0.707
			vPos.x -= DT * m_DashSpeed * 0.707f;
		}
		if (m_Direction == eDirection::UP_RIGHT)
		{
			vPos.y += DT * m_DashSpeed * 0.707f;
			vPos.x += DT * m_DashSpeed * 0.707f;
		}
		if (m_Direction == eDirection::DOWN_LEFT)
		{
			vPos.y -= DT * m_DashSpeed * 0.707f;
			vPos.x -= DT * m_DashSpeed * 0.707f;
		}
		if (m_Direction == eDirection::DOWN_RIGHT)
		{
			vPos.y -= DT * m_DashSpeed * 0.707f;
			vPos.x += DT * m_DashSpeed * 0.707f;
		}

		m_DashTime += DT;
	}

	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::MousePosCheck()
{
	CKeyMgr::GetInst()->MouseCapture(true);

	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 vResoltuion = CDevice::GetInst()->GetResolution();

	vMousePos -= Vec2(vResoltuion.x / 2.f, vResoltuion.y / 2.f);
	vMousePos = Vec2(vMousePos.x, -vMousePos.y);

	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	Vec2 pPos = Vec2(vPos.x, vPos.y);
	vMousePos += pPos;

	Vec2 vMouseDir = vMousePos - pPos;
	vMouseDir.Normalize();

	float angle;

	if (vRot.y == XM_PI)
		angle = atan2(vMouseDir.y, -vMouseDir.x);
	else
		angle = atan2(vMouseDir.y, vMouseDir.x);

	// 라디안 -> 도
	angle = angle * (180.f / XM_PI);

	if (angle < 0)
		angle += 360.0f;

	// 각도에 따른 공격 방향 설정
	if (angle >= 45.0f && angle < 135.0f)
		m_AttackDir = eDirection::UP;
	else if (angle >= 135.0f && angle < 225.0f)
		m_AttackDir = eDirection::LEFT;
	else if (angle >= 225.0f && angle < 315.0f)
		m_AttackDir = eDirection::DOWN;
	else
		m_AttackDir = eDirection::RIGHT;  

	//vRot.z = angle;

	//Transform()->SetRelativeRotation(vRot);
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
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\DashDown.flip");
	FlipBookComponent()->AddFlipBook(12, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\DashRight.flip");
	FlipBookComponent()->AddFlipBook(13, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\DashUp.flip");
	FlipBookComponent()->AddFlipBook(14, pFlipBook);

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