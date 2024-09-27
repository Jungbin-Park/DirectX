#include "pch.h"
#include "PDashState.h"

#include <Engine/components.h>

#include <Scripts/CPlayerScript.h>

PDashState::PDashState()
	: CState(STATE_TYPE::PLAYERDASHSTATE)
	, m_DashSpeed(1700.f)
	, m_DashTime(0.f)
	, m_DashDuration(0.2f)
{
}

PDashState::~PDashState()
{
}

void PDashState::Enter()
{
	CPlayerScript* pScript = (CPlayerScript*)GetOwner()->GetScriptByName(L"CPlayerScript");
	m_Direction = pScript->GetDirection();
	m_CollisionDir = pScript->GetColDirection();

	m_DashTime = 0.f;

	// 애니메이션 재생
	switch (m_Direction)
	{
	case eDIR::UP:
		GetOwner()->FlipBookComponent()->Play(14, 40, false);
		break;
	case eDIR::DOWN:
		GetOwner()->FlipBookComponent()->Play(12, 40, false);
		break;
	case eDIR::LEFT:
	case eDIR::UP_LEFT:
	case eDIR::DOWN_LEFT:
		GetOwner()->FlipBookComponent()->Play(13, 40, false);
		break;
	case eDIR::RIGHT:
	case eDIR::UP_RIGHT:
	case eDIR::DOWN_RIGHT:
		GetOwner()->FlipBookComponent()->Play(13, 40, false);
		break;
	}
}

void PDashState::FinalTick()
{
	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	CPlayerScript* pScript = (CPlayerScript*)GetOwner()->GetScriptByName(L"CPlayerScript");
	m_CollisionDir = pScript->GetColDirection();
	m_KeyTapCount = pScript->GetKeyTapCount();

	if (m_DashTime >= m_DashDuration)
	{
		m_DashTime = 0.f;

		// 아무 키도 안눌려 있으면
		if (m_KeyTapCount == 0)
		{
			GetOwner()->FSM()->ChangeState(L"PIdleState");
		}
		// 다른 키를 누르고 있으면
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
			case eDIR::UP_LEFT:
			case eDIR::DOWN_LEFT:
				GetOwner()->FlipBookComponent()->Play(4, 10, true);
				break;
			case eDIR::RIGHT:
			case eDIR::UP_RIGHT:
			case eDIR::DOWN_RIGHT:
				GetOwner()->FlipBookComponent()->Play(4, 10, true);
				break;
			default:
				break;
			}
			GetOwner()->FSM()->ChangeState(L"PMoveState");
		}
	}
	else
	{
		// 상하좌우
		if (m_Direction == eDIR::UP)
		{
			if (m_CollisionDir != eDIR::DOWN)
				vPos.y += DT * m_DashSpeed;
		}
		if (m_Direction == eDIR::DOWN)
		{
			if (m_CollisionDir != eDIR::UP)
				vPos.y -= DT * m_DashSpeed;
		}
		if (m_Direction == eDIR::LEFT)
		{
			if (m_CollisionDir != eDIR::RIGHT)
				vPos.x -= DT * m_DashSpeed;
		}
		if (m_Direction == eDIR::RIGHT)
		{
			if (m_CollisionDir != eDIR::LEFT)
				vPos.x += DT * m_DashSpeed;
		}

		// 대각선 방향
		if (m_Direction == eDIR::UP_LEFT)
		{
			if (m_CollisionDir != eDIR::DOWN)
				vPos.y += DT * m_DashSpeed * 0.7f;  // 45도일 때 √2/2 ≈ 0.707
			if (m_CollisionDir != eDIR::RIGHT)
				vPos.x -= DT * m_DashSpeed * 0.7f;
		}
		if (m_Direction == eDIR::UP_RIGHT)
		{
			if (m_CollisionDir != eDIR::DOWN)
				vPos.y += DT * m_DashSpeed * 0.7f;
			if (m_CollisionDir != eDIR::LEFT)
				vPos.x += DT * m_DashSpeed * 0.7f;
		}
		if (m_Direction == eDIR::DOWN_LEFT)
		{
			if (m_CollisionDir != eDIR::UP)
				vPos.y -= DT * m_DashSpeed * 0.7f;
			if (m_CollisionDir != eDIR::RIGHT)
				vPos.x -= DT * m_DashSpeed * 0.7f;
		}
		if (m_Direction == eDIR::DOWN_RIGHT)
		{
			if (m_CollisionDir != eDIR::UP)
				vPos.y -= DT * m_DashSpeed * 0.7f;
			if (m_CollisionDir != eDIR::LEFT)
				vPos.x += DT * m_DashSpeed * 0.7f;
		}

		m_DashTime += DT;
	}

	GetOwner()->Transform()->SetRelativePos(vPos);
}

void PDashState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
}


