#include "pch.h"
#include "CPlayerScript.h"

#include "CSlashScript.h"
#include "CPlatformScript.h"

#include <Engine/CDevice.h>
#include <Engine/CFlipBookComponent.h>
#include <Engine/CTransform.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <States/PDeadState.h>

#include "CFireDragonScript.h"


CPlayerScript::CPlayerScript()
	: CScript(UINT(SCRIPT_TYPE::PLAYERSCRIPT))
	, m_Speed(400.f)
	, m_DashSpeed(1700.f)
	, m_DashTime(0.f)
	, m_DashDuration(0.2f)
	, m_Attribute(0)
	, m_AtkState(AtkState::NONE)
	, m_State(eState::IDLE)
	, m_Direction(eDIR::DOWN)
	, m_AttackDir(eDIR::RIGHT)
	, m_AtkDashSpeed(150.f)
	, m_AtkDashTime(0.f)
	, m_AtkDashDuration(0.3f)
	, m_AttackFinish(true)
	, m_DashFinish(true)
	, m_KeyTapCount(0)
	, m_AttackCount(0)
	, m_SlashPos(Vec3(0.f, 0.f, 0.f))
	, m_MovedPos(Vec2(0.f, 0.f))
	, m_SlashRot(Vec3(0.f, 0.f, 0.f))
	, m_CollisionDir(CollisionDir::NONE)
	, m_CollisionCount(0)
	, m_AttackCooldown(0.f)
	, m_SlashDmg(10)
	, m_IsDead(false)
	, m_HitTime(0.f)
	, m_KnockBackSpeed(100.f)
	, m_KnockBackTime(0.2f)
	, m_KnockBackAge(0.f)
	, m_HP(100.f)
    , m_MP(100.f)
	, m_FireDragonCount(0)
	, m_SkillAnimCount(0)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Red", &m_Attribute);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "PlayerSpeed", &m_Speed);
	AddScriptParam(SCRIPT_PARAM::TEXTURE, "Test", &m_Texture);
	AddScriptParam(SCRIPT_PARAM::PREFAB, "Slash", &m_SlashPref);
	SetName(L"CPlayerScript");
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Begin()
{
	m_SlashPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\Slash.pref");
	m_TeleportPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\Teleport.pref");
	m_FireDragonPref = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"prefab\\FireDragon.pref");

	GetRenderComponent()->GetDynamicMaterial();

	LoadFlipBook();

	Vec3 vPos = Transform()->GetRelativePos();
	vPos.x += 10.f;
	vPos.y += 250.f;
	Instantiate(m_TeleportPref, 0, vPos, L"Teleport");

	//FSM()->AddState(L"PDeadState", new PDeadState);
}

void CPlayerScript::Tick()
{
	if (m_State != eState::DEAD)
	{
		KeyInput();
	}

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
	case CPlayerScript::eState::HIT:
		KnockBack();
		break;
	case CPlayerScript::eState::FIREDRAGON:
		FireDragon();
		break;
	case CPlayerScript::eState::DEAD:
		break;
	default:
		break;
	}

	if (m_Direction == eDIR::LEFT ||
		m_Direction == eDIR::UP_LEFT ||
		m_Direction == eDIR::DOWN_LEFT)
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
	// W,S,A,D
	if (KEY_TAP(KEY::A) || KEY_TAP(KEY::D) || KEY_TAP(KEY::W) || KEY_TAP(KEY::S))
	{
		m_KeyTapCount += 1;
	}
	if (KEY_RELEASED(KEY::A) || KEY_RELEASED(KEY::D) || KEY_RELEASED(KEY::W) || KEY_RELEASED(KEY::S))
	{
		m_KeyTapCount -= 1;
	}


	if(m_State != eState::HIT)
	{
		if (KEY_TAP(KEY::A))
		{
			m_State = eState::MOVE;

			if (m_KeyTapCount == 2)
			{
				if (m_PrevDirection == eDIR::UP) m_Direction = eDIR::UP_LEFT;
				if (m_PrevDirection == eDIR::DOWN) m_Direction = eDIR::DOWN_LEFT;
				m_PrevDirection = m_Direction;
			}
			else
			{
				m_Direction = eDIR::LEFT;
				m_PrevDirection = m_Direction;
			}
			FlipBookComponent()->Play(4, 10, true);
		}
		if (KEY_RELEASED(KEY::A))
		{
			if (m_KeyTapCount == 0)
			{
				m_State = eState::IDLE;
				m_Direction = eDIR::LEFT;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(1, 10, true);
			}
			else if (m_KeyTapCount == 1)
			{
				if (m_Direction == eDIR::UP_LEFT)
				{
					m_Direction = eDIR::UP;
					m_PrevDirection = m_Direction;
					FlipBookComponent()->Play(5, 10, true);
				}
				if (m_Direction == eDIR::DOWN_LEFT)
				{
					m_Direction = eDIR::DOWN;
					m_PrevDirection = m_Direction;
					FlipBookComponent()->Play(3, 10, true);
				}
			}
		}

		if (KEY_TAP(KEY::D))
		{
			m_State = eState::MOVE;

			if (m_KeyTapCount == 2)
			{
				if (m_PrevDirection == eDIR::UP) m_Direction = eDIR::UP_RIGHT;
				if (m_PrevDirection == eDIR::DOWN) m_Direction = eDIR::DOWN_RIGHT;
				m_PrevDirection = m_Direction;
			}
			else
			{
				m_Direction = eDIR::RIGHT;
				m_PrevDirection = m_Direction;
			}
			FlipBookComponent()->Play(4, 10, true);
		}
		if (KEY_RELEASED(KEY::D))
		{
			if (m_KeyTapCount == 0)
			{
				m_State = eState::IDLE;
				m_Direction = eDIR::RIGHT;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(1, 10, true);
			}
			else if (m_KeyTapCount == 1)
			{
				if (m_Direction == eDIR::UP_RIGHT)
				{
					m_Direction = eDIR::UP;
					m_PrevDirection = m_Direction;
					FlipBookComponent()->Play(5, 10, true);
				}
				if (m_Direction == eDIR::DOWN_RIGHT)
				{
					m_Direction = eDIR::DOWN;
					m_PrevDirection = m_Direction;
					FlipBookComponent()->Play(3, 10, true);
				}
			}
		}

		if (KEY_TAP(KEY::W))
		{
			m_State = eState::MOVE;

			if (m_KeyTapCount == 2)
			{
				if (m_PrevDirection == eDIR::RIGHT) m_Direction = eDIR::UP_RIGHT;
				if (m_PrevDirection == eDIR::LEFT) m_Direction = eDIR::UP_LEFT;
			}
			else
			{
				m_Direction = eDIR::UP;
				m_PrevDirection = m_Direction;
			}

			if (m_KeyTapCount == 1)
				FlipBookComponent()->Play(5, 10, true);
		}
		if (KEY_RELEASED(KEY::W))
		{
			if (m_KeyTapCount == 0)
			{
				m_State = eState::IDLE;
				m_Direction = eDIR::UP;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(2, 10, true);
			}
			else if (m_KeyTapCount == 1)
			{
				if (m_Direction == eDIR::UP_RIGHT)
				{
					m_Direction = eDIR::RIGHT;
					m_PrevDirection = m_Direction;
					FlipBookComponent()->Play(4, 10, true);
				}
				if (m_Direction == eDIR::UP_LEFT)
				{
					m_Direction = eDIR::LEFT;
					m_PrevDirection = m_Direction;
					FlipBookComponent()->Play(4, 10, true);
				}
			}
			
		}

		if (KEY_TAP(KEY::S))
		{
			m_State = eState::MOVE;

			if (m_KeyTapCount == 2)
			{
				if (m_PrevDirection == eDIR::RIGHT) m_Direction = eDIR::DOWN_RIGHT;
				if (m_PrevDirection == eDIR::LEFT) m_Direction = eDIR::DOWN_LEFT;
			}
			else
			{
				m_Direction = eDIR::DOWN;
				m_PrevDirection = m_Direction;
			}

			if (m_KeyTapCount == 1)
				FlipBookComponent()->Play(3, 10, true);

		}
		if (KEY_RELEASED(KEY::S))
		{
			if (m_KeyTapCount == 0)
			{
				m_State = eState::IDLE;
				m_Direction = eDIR::DOWN;
				m_PrevDirection = m_Direction;
				FlipBookComponent()->Play(0, 10, true);
			}
			else if (m_KeyTapCount == 1)
			{
				if (m_Direction == eDIR::DOWN_RIGHT)
				{
					m_Direction = eDIR::RIGHT;
					m_PrevDirection = m_Direction;
					FlipBookComponent()->Play(4, 10, true);
				}
				if (m_Direction == eDIR::DOWN_LEFT)
				{
					m_Direction = eDIR::LEFT;
					m_PrevDirection = m_Direction;
					FlipBookComponent()->Play(4, 10, true);
				}
			}
		}
	}


	// FireDragon
	if (KEY_TAP(KEY::RBTN))
	{
		m_State = eState::FIREDRAGON;
		MousePosCheck();
	}

	// Slash
	if(m_State != eState::HIT)
	{
		if (m_AttackCount >= 3)
		{
			m_AttackCooldown += DT;
			if (m_AttackCooldown >= 0.5f)
			{
				m_AttackCount = 0;
				m_AttackCooldown = 0.f;
			}

		}

		if (m_AttackCount < 3)
		{
			if (KEY_TAP(KEY::LBTN))
			{
				m_State = eState::ATTACK;

				MousePosCheck();

				m_AttackCount += 1;
				m_AtkDashTime = 0.f;

				// Attack State 변경 
				if (m_AtkState == AtkState::NONE) m_AtkState = AtkState::ATTACK1;
				else if (m_AtkState == AtkState::ATTACK1) m_AtkState = AtkState::ATTACK2;
				else if (m_AtkState == AtkState::ATTACK2) m_AtkState = AtkState::ATTACK1;

				// Slash 프리팹 생성
				m_SlashPos = Transform()->GetRelativePos() + (Vec3(m_MouseDir.x, m_MouseDir.y, 0.f) * 100.f);
				Instantiate(m_SlashPref, 5, m_SlashPos, m_SlashRot, L"Slash");

				// 애니메이션 재생
				switch (m_AtkState)
				{
				case CPlayerScript::AtkState::ATTACK1:
				{
					switch (m_AttackDir)
					{
					case eDIR::UP:
						m_Direction = eDIR::UP;
						FlipBookComponent()->Play(10, 15, false);
						break;
					case eDIR::DOWN:
						m_Direction = eDIR::DOWN;
						FlipBookComponent()->Play(6, 15, false);
						break;
					case eDIR::LEFT:
						m_Direction = eDIR::LEFT;
						FlipBookComponent()->Play(8, 15, false);
						break;
					case eDIR::RIGHT:
						m_Direction = eDIR::RIGHT;
						FlipBookComponent()->Play(8, 15, false);
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
					case eDIR::UP:
						m_Direction = eDIR::UP;
						FlipBookComponent()->Play(11, 15, false);
						break;
					case eDIR::DOWN:
						m_Direction = eDIR::DOWN;
						FlipBookComponent()->Play(7, 15, false);
						break;
					case eDIR::LEFT:
						m_Direction = eDIR::LEFT;
						FlipBookComponent()->Play(9, 15, false);
						break;
					case eDIR::RIGHT:
						m_Direction = eDIR::RIGHT;
						FlipBookComponent()->Play(9, 15, false);
						break;
					default:
						break;
					}
				}
				break;
				}
			}
		}
	}

	if (m_State != eState::DASH && m_State != eState::HIT)
	{
		if (KEY_TAP(KEY::SPACE))
		{
			m_State = eState::DASH;

			m_DashFinish = false;

			m_DashTime = 0.f;

			// 애니메이션 재생
			switch (m_Direction)
			{
			case eDIR::UP:
				FlipBookComponent()->Play(14, 30, false);
				break;
			case eDIR::DOWN:
				FlipBookComponent()->Play(12, 20, false);
				break;
			case eDIR::LEFT:
			case eDIR::UP_LEFT:
			case eDIR::DOWN_LEFT:
				FlipBookComponent()->Play(13, 20, false);
				break;
			case eDIR::RIGHT:
			case eDIR::UP_RIGHT:
			case eDIR::DOWN_RIGHT:
				FlipBookComponent()->Play(13, 30, false);
				break;
			}

			FlipBookComponent()->Reset();
		}
	}
	
}

void CPlayerScript::Idle()
{
	switch (m_Direction)
	{
	case eDIR::UP:
		FlipBookComponent()->Play(2, 10, true);
		break;
	case eDIR::DOWN:
		FlipBookComponent()->Play(0, 10, true);
		break;
	case eDIR::LEFT:
	case eDIR::UP_LEFT:
	case eDIR::DOWN_LEFT:
		FlipBookComponent()->Play(1, 10, true);
		break;
	case eDIR::RIGHT:
	case eDIR::UP_RIGHT:
	case eDIR::DOWN_RIGHT:
		FlipBookComponent()->Play(1, 10, true);
		break;
	default:
		break;
	}
}

void CPlayerScript::Move()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::A))
	{
		//m_Direction = eDIR::LEFT;
		m_State = eState::MOVE;
		if (m_CollisionDir != CollisionDir::RIGHT)
			vPos.x -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		//m_Direction = eDIR::RIGHT;
		m_State = eState::MOVE;
		if (m_CollisionDir != CollisionDir::LEFT)
			vPos.x += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::W))
	{
		//m_Direction = eDIR::UP;
		m_State = eState::MOVE;
		if (m_CollisionDir != CollisionDir::DOWN)
			vPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		//m_Direction = eDIR::DOWN;
		m_State = eState::MOVE;
		if (m_CollisionDir != CollisionDir::UP)
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

		m_AttackFinish = true;

		ExitState();
	}
	// 공격 시
	else
	{
		m_MouseDir.Normalize();

		switch (m_CollisionDir)
		{
		case CPlayerScript::CollisionDir::NONE:
			break;
		case CPlayerScript::CollisionDir::RIGHT:
			if (m_MouseDir.x < 0)
				m_MouseDir.x = 0;
			break;
		case CPlayerScript::CollisionDir::LEFT:
			if (m_MouseDir.x > 0)
				m_MouseDir.x = 0;
			break;
		case CPlayerScript::CollisionDir::UP:
			if (m_MouseDir.y < 0)
				m_MouseDir.y = 0;
			break;
		case CPlayerScript::CollisionDir::DOWN:
			if (m_MouseDir.y > 0)
				m_MouseDir.y = 0;
			break;
		default:
			break;
		}

		m_MovedPos = vPos + m_MouseDir * DT * m_AtkDashSpeed;

		m_AtkDashTime += DT;
	}

	Transform()->SetRelativePos(Vec3(m_MovedPos.x, m_MovedPos.y, vPos.z));
}

void CPlayerScript::Dash()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (m_DashTime >= m_DashDuration)
	{
		if (FlipBookComponent()->IsFinish())
		{
			m_DashTime = 0.f;
			m_DashFinish = true;

			ExitState();
		}
	}
	else
	{
		FlipBookComponent()->Reset();
		// 상하좌우
		if (m_Direction == eDIR::UP)
		{
			if (m_CollisionDir != CollisionDir::DOWN)
				vPos.y += DT * m_DashSpeed;
		}
		if (m_Direction == eDIR::DOWN)
		{
			if (m_CollisionDir != CollisionDir::UP)
				vPos.y -= DT * m_DashSpeed;
		}
		if (m_Direction == eDIR::LEFT)
		{
			if (m_CollisionDir != CollisionDir::RIGHT)
				vPos.x -= DT * m_DashSpeed;
		}
		if (m_Direction == eDIR::RIGHT)
		{
			if (m_CollisionDir != CollisionDir::LEFT)
				vPos.x += DT * m_DashSpeed;
		}

		// 대각선 방향
		if (m_Direction == eDIR::UP_LEFT)
		{
			if (m_CollisionDir != CollisionDir::DOWN)
				vPos.y += DT * m_DashSpeed * 0.7f;  // 45도일 때 √2/2 ≈ 0.707
			if (m_CollisionDir != CollisionDir::RIGHT)
				vPos.x -= DT * m_DashSpeed * 0.7f;
		}
		if (m_Direction == eDIR::UP_RIGHT)
		{
			if (m_CollisionDir != CollisionDir::DOWN)
				vPos.y += DT * m_DashSpeed * 0.7f;
			if (m_CollisionDir != CollisionDir::LEFT)
				vPos.x += DT * m_DashSpeed * 0.7f;
		}
		if (m_Direction == eDIR::DOWN_LEFT)
		{
			if (m_CollisionDir != CollisionDir::UP)
				vPos.y -= DT * m_DashSpeed * 0.7f;
			if (m_CollisionDir != CollisionDir::RIGHT)
				vPos.x -= DT * m_DashSpeed * 0.7f;
		}
		if (m_Direction == eDIR::DOWN_RIGHT)
		{
			if (m_CollisionDir != CollisionDir::UP)
				vPos.y -= DT * m_DashSpeed * 0.7f;
			if (m_CollisionDir != CollisionDir::LEFT)
				vPos.x += DT * m_DashSpeed * 0.7f;
		}

		m_DashTime += DT;
	}

	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::FireDragon()
{
	m_FireDragonCooldown += DT;

	if (m_FireDragonCooldown > 0.1f)
	{
		m_FireDragonCooldown = 0.f;
		m_FireDragonCount++;
		ShootFireDragon();

		if (m_FireDragonCount == 7)
		{
			m_FireDragonCount = 0;
			ExitState();
		}
	}
	
}

void CPlayerScript::ShootFireDragon()
{
	// ShootFireDragon 프리팹 생성
	m_FireDragonPos = Transform()->GetRelativePos() + (Vec3(m_MouseDir.x, m_MouseDir.y, 0.f) * 100.f);

	switch (m_AttackDir)
	{
	case eDIR::LEFT:
		m_FireDragonRot = Vec3(XM_PI, 0.f, 0.f);
		break;

	default:
		m_FireDragonRot = Vec3(0.f, 0.f, 0.f);
		break;
	}

	Instantiate(m_FireDragonPref, 5, m_FireDragonPos, m_FireDragonRot, L"FireDragon");

	if (m_SkillAnimCount == 0)
	{
		m_SkillAnimCount++;
		// animation
		switch (m_AttackDir)
		{
		case eDIR::UP:
			m_Direction = eDIR::UP;
			FlipBookComponent()->Play(10, 15, false);
			break;
		case eDIR::DOWN:
			m_Direction = eDIR::DOWN;
			FlipBookComponent()->Play(6, 15, false);
			break;
		case eDIR::LEFT:
			m_Direction = eDIR::LEFT;
			FlipBookComponent()->Play(8, 15, false);
			break;
		case eDIR::RIGHT:
			m_Direction = eDIR::RIGHT;
			FlipBookComponent()->Play(8, 15, false);
			break;
		default:
			break;
		}
	}
	else
	{
		m_SkillAnimCount--;
		// animation
		switch (m_AttackDir)
		{
		case eDIR::UP:
			m_Direction = eDIR::UP;
			FlipBookComponent()->Play(10, 15, false);
			break;
		case eDIR::DOWN:
			m_Direction = eDIR::DOWN;
			FlipBookComponent()->Play(6, 15, false);
			break;
		case eDIR::LEFT:
			m_Direction = eDIR::LEFT;
			FlipBookComponent()->Play(8, 15, false);
			break;
		case eDIR::RIGHT:
			m_Direction = eDIR::RIGHT;
			FlipBookComponent()->Play(8, 15, false);
			break;
		default:
			break;
		}
	}

	FlipBookComponent()->Reset();
}

void CPlayerScript::KnockBack()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (m_KnockBackAge < m_KnockBackTime)
	{
		m_KnockBackAge += DT;
		vPos -= m_HitDir * m_KnockBackSpeed * DT;
	}

	Transform()->SetRelativePos(vPos);

	m_HitTime += DT;

	if (m_HitTime > 0.1f)
		GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 0);

	if (m_HitTime > 0.3f)
	{
		ExitState();
	}

	FlipBookComponent()->Reset();
}

void CPlayerScript::ExitState()
{
	// 아무 키도 안눌려 있으면
	if (m_KeyTapCount == 0)
		m_State = eState::IDLE;
	// 다른 키를 누르고 있으면
	else
	{
		m_State = eState::MOVE;

		switch (m_Direction)
		{
		case eDIR::UP:
			FlipBookComponent()->Play(5, 10, true);
			break;
		case eDIR::DOWN:
			FlipBookComponent()->Play(3, 10, true);
			break;
		case eDIR::LEFT:
		case eDIR::UP_LEFT:
		case eDIR::DOWN_LEFT:
			FlipBookComponent()->Play(4, 10, true);
			break;
		case eDIR::RIGHT:
		case eDIR::UP_RIGHT:
		case eDIR::DOWN_RIGHT:
			FlipBookComponent()->Play(4, 10, true);
			break;
		default:
			break;
		}
	}
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

	// 마우스와 플레이어 사이의 방향 벡터
	Vec2 vMouseDir = vMousePos - pPos;
	vMouseDir.Normalize();
	m_MouseDir = vMouseDir;

	float angle;

	/*if (vRot.y == XM_PI)
		angle = atan2(vMouseDir.y, -vMouseDir.x);
	else
		angle = atan2(vMouseDir.y, vMouseDir.x);*/

	angle = atan2(vMouseDir.y, vMouseDir.x);
	m_SlashRot.z = angle - XM_PI / 2.f;
	m_FireDragonRot.z = angle;

	// 라디안 -> 도
	angle = angle * (180.f / XM_PI);

	if (angle < 0)
		angle += 360.0f;



	// 각도에 따른 공격 방향 설정
	if (angle >= 45.0f && angle < 135.0f)
		m_AttackDir = eDIR::UP;
	else if (angle >= 135.0f && angle < 225.0f)
		m_AttackDir = eDIR::LEFT;
	else if (angle >= 225.0f && angle < 315.0f)
		m_AttackDir = eDIR::DOWN;
	else
		m_AttackDir = eDIR::RIGHT;

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
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\pDashRight1.flip");
	FlipBookComponent()->AddFlipBook(13, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\DashUp.flip");
	FlipBookComponent()->AddFlipBook(14, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\Hit.flip");
	FlipBookComponent()->AddFlipBook(15, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\Dead.flip");
	FlipBookComponent()->AddFlipBook(16, pFlipBook);

}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	FlipBookComponent()->Reset();

	if (_OtherObject->GetName() == L"Platform")
	{
		m_CollisionCount += 1;
		Vec3 vWallPos = _OtherObject->Transform()->GetRelativePos();
		Vec3 vPos = Transform()->GetRelativePos();

		float halfColX = (Transform()->GetRelativeScale().x * _OwnCollider->GetScale().x) / 2;
		float halfColY = (Transform()->GetRelativeScale().y * _OwnCollider->GetScale().y) / 2;

		float fWallLeft = vWallPos.x - (_OtherObject->Transform()->GetRelativeScale().x / 2);
		float fWallRight = vWallPos.x + (_OtherObject->Transform()->GetRelativeScale().x / 2);
		float fWallUp = vWallPos.y + (_OtherObject->Transform()->GetRelativeScale().y / 2);
		float fWallDown = vWallPos.y - (_OtherObject->Transform()->GetRelativeScale().y / 2);

		// 플레이어가 벽 오른쪽
		if (vPos.x > vWallPos.x)
		{
			// 벽 아랫면
			if (floor(vPos.y + halfColY) <= fWallDown)
			{
				m_CollisionDir = CollisionDir::DOWN;
			}
			// 벽 윗면
			else if (ceil(vPos.y - halfColY) >= fWallUp)
			{
				m_CollisionDir = CollisionDir::UP;
			}
			// 오른쪽
			else
			{
				m_CollisionDir = CollisionDir::RIGHT;
			}
		}
		// 플레이어가 벽 왼쪽
		else
		{
			// 벽 아랫면
			if (floor(vPos.y + halfColY) <= fWallDown)
			{
				m_CollisionDir = CollisionDir::DOWN;
			}
			// 벽 윗면
			else if (ceil(vPos.y - halfColY) >= fWallUp)
			{
				m_CollisionDir = CollisionDir::UP;
			}
			// 왼쪽
			else
			{
				m_CollisionDir = CollisionDir::LEFT;
			}
		}
	}

	if (_OtherObject->GetLayerIdx() == 2 || _OtherObject->GetLayerIdx() == 6)
	{
		if (!m_IsDead)
		{
			m_HP -= 10;

			if (m_HP <= 0.f)
			{
				FlipBookComponent()->Play(16, 10, false);
				m_IsDead = true;
				m_State = eState::DEAD;
				//GetOwner()->SetDead(true);
			}
			else
			{
				FlipBookComponent()->Play(15, 10, false);
				GetRenderComponent()->GetDynamicMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1);

				m_HitTime = 0;
				m_KnockBackAge = 0.f;
				m_HitDir = _OwnCollider->GetCollisionPoint() - Transform()->GetRelativePos();
				m_HitDir.Normalize();

				if (m_HitDir.x > 0)
					m_Direction = eDIR::RIGHT;
				else
					m_Direction = eDIR::LEFT;

				m_State = eState::HIT;
			}

			FlipBookComponent()->Reset();
		}
	}
}

void CPlayerScript::Overlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Portal")
	{
		if (KEY_TAP(KEY::F))
		{
			Vec3 vPos = Transform()->GetRelativePos();
			vPos.x += 10.f;
			vPos.y += 250.f;
			Instantiate(m_TeleportPref, 0, vPos, L"Teleport");
		}
	}
}

void CPlayerScript::EndOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Platform")
	{
		m_CollisionCount -= 1;

		if (m_CollisionCount == 0)
			m_CollisionDir = CollisionDir::NONE;
	}
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