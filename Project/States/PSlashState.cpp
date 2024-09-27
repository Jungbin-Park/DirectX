#include "pch.h"
#include "PSlashState.h"

#include <Engine/components.h>

#include <Scripts/CPlayerScript.h>

PSlashState::PSlashState()
	: CState(STATE_TYPE::PLAYERSLASHSTATE)
	, m_ClickCount(0)
	, m_AtkDashSpeed(150.f)
	, m_AtkDashTime(0.f)
	, m_AtkDashDuration(0.3f)
	, m_AttackFinishTime(0.5f)
{
}

PSlashState::~PSlashState()
{
}

void PSlashState::Enter()
{
	CPlayerScript* pScript = (CPlayerScript*)GetOwner()->GetScriptByName(L"CPlayerScript");

	m_AtkDashTime = 0.f;
	m_ClickCount += 1;

	// 애니메이션 재생
	if (m_ClickCount % 2 == 1)
	{
		switch (m_AttackDir)
		{
		case eDIR::UP:
			m_Direction = eDIR::UP;
			GetOwner()->FlipBookComponent()->Play(10, 15, false);
			break;
		case eDIR::DOWN:
			m_Direction = eDIR::DOWN;
			GetOwner()->FlipBookComponent()->Play(6, 15, false);
			break;
		case eDIR::LEFT:
			m_Direction = eDIR::LEFT;
			GetOwner()->FlipBookComponent()->Play(8, 15, false);
			break;
		case eDIR::RIGHT:
			m_Direction = eDIR::RIGHT;
			GetOwner()->FlipBookComponent()->Play(8, 15, false);
			break;
		default:
			break;
		}
	}
	else if (m_ClickCount % 2 == 0)
	{
		switch (m_AttackDir)
		{
		case eDIR::UP:
			m_Direction = eDIR::UP;
			GetOwner()->FlipBookComponent()->Play(11, 15, false);
			break;
		case eDIR::DOWN:
			m_Direction = eDIR::DOWN;
			GetOwner()->FlipBookComponent()->Play(7, 15, false);
			break;
		case eDIR::LEFT:
			m_Direction = eDIR::LEFT;
			GetOwner()->FlipBookComponent()->Play(9, 15, false);
			break;
		case eDIR::RIGHT:
			m_Direction = eDIR::RIGHT;
			GetOwner()->FlipBookComponent()->Play(9, 15, false);
			break;
		default:
			break;
		}
	}
}

void PSlashState::FinalTick()
{
	CPlayerScript* pScript = (CPlayerScript*)GetOwner()->GetScriptByName(L"CPlayerScript");
	m_Direction = pScript->GetDirection();
	m_CollisionDir = pScript->GetColDirection();
	m_MouseDir = pScript->GetMouseDir();
	m_AttackDir = pScript->GetAttackDirection();
	m_KeyTapCount = pScript->GetKeyTapCount();

	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	Vec3 vRot = GetOwner()->Transform()->GetRelativeRotation();

	// 공격 시
	if (m_AtkDashTime < m_AtkDashDuration)
	{
		m_MouseDir.Normalize();

		switch (m_CollisionDir)
		{
		case eDIR::NONE:
			break;
		case eDIR::RIGHT:
			if (m_MouseDir.x < 0)
				m_MouseDir.x = 0;
			break;
		case eDIR::LEFT:
			if (m_MouseDir.x > 0)
				m_MouseDir.x = 0;
			break;
		case eDIR::UP:
			if (m_MouseDir.y < 0)
				m_MouseDir.y = 0;
			break;
		case eDIR::DOWN:
			if (m_MouseDir.y > 0)
				m_MouseDir.y = 0;
			break;
		default:
			break;
		}

		m_MovedPos = vPos + m_MouseDir * DT * m_AtkDashSpeed;

		m_AtkDashTime += DT;
	}
	if (m_AtkDashTime >= m_AttackFinishTime)
	{
		// 누르고 있는 키가 없으면
		if (m_KeyTapCount == 0)
		{
			pScript->SetAttackCount(0);
			GetOwner()->FSM()->ChangeState(L"PIdleState");
		}
		// 다른 키를 누르고 있을 경우
		else
		{
			switch (m_Direction)
			{
			case eDIR::UP:
				GetOwner()->FlipBookComponent()->Play(5, 10, true);
				break;
			case eDIR::DOWN:
				GetOwner()->FlipBookComponent()->Play(3, 10, true);
				break;
			case eDIR::LEFT:
				GetOwner()->FlipBookComponent()->Play(4, 10, true);
				break;
			case eDIR::RIGHT:
				GetOwner()->FlipBookComponent()->Play(4, 10, true);
				break;
			default:
				break;
			}
			pScript->SetAttackCount(0);
			GetOwner()->FSM()->ChangeState(L"PMoveState");
		}
	}
	
	GetOwner()->Transform()->SetRelativePos(m_MovedPos);
}

void PSlashState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
}


