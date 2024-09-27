#include "pch.h"
#include "PIdleState.h"

#include <Engine/components.h>

#include <Scripts/CPlayerScript.h>

PIdleState::PIdleState()
	: CState(STATE_TYPE::PLAYERIDLESTATE)
{
}

PIdleState::~PIdleState()
{
}

void PIdleState::Enter()
{
	CPlayerScript* pScript = (CPlayerScript*)GetOwner()->GetScriptByName(L"CPlayerScript");
	m_Direction = pScript->GetDirection();
	m_CollisionDir = pScript->GetColDirection();

	switch (m_Direction)
	{
	case eDIR::UP:
		GetOwner()->FlipBookComponent()->Play(2, 10, false);
		break;
	case eDIR::DOWN:
		GetOwner()->FlipBookComponent()->Play(0, 10, false);
		break;
	case eDIR::LEFT:
	case eDIR::UP_LEFT:
	case eDIR::DOWN_LEFT:
		GetOwner()->FlipBookComponent()->Play(1, 10, false);
		break;
	case eDIR::RIGHT:
	case eDIR::UP_RIGHT:
	case eDIR::DOWN_RIGHT:
		GetOwner()->FlipBookComponent()->Play(1, 10, false);
		break;
	default:
		break;
	}
}

void PIdleState::FinalTick()
{
	if (KEY_TAP(KEY::A))
	{
		m_KeyTapCount += 1;

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

		FSM()->ChangeState(L"PMoveState");
	}
	if (KEY_RELEASED(KEY::A))
	{
		m_KeyTapCount -= 1;

		if (m_KeyTapCount == 0)
		{
			m_Direction = eDIR::LEFT;
			m_PrevDirection = m_Direction;
			//FlipBookComponent()->Play(1, 10, true);
			FSM()->ChangeState(L"PIdleState");
		}
		if (m_KeyTapCount == 1)
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
		m_KeyTapCount += 1;

		FSM()->ChangeState(L"PMoveState");

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
		m_KeyTapCount -= 1;

		if (m_KeyTapCount == 0)
		{
			m_Direction = eDIR::RIGHT;
			m_PrevDirection = m_Direction;
			//FlipBookComponent()->Play(1, 10, true);
			FSM()->ChangeState(L"PIdleState");
		}
		if (m_KeyTapCount == 1)
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
		m_KeyTapCount += 1;

		FSM()->ChangeState(L"PMoveState");

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
		m_KeyTapCount -= 1;

		if (m_KeyTapCount == 0)
		{
			m_Direction = eDIR::UP;
			m_PrevDirection = m_Direction;
			//FlipBookComponent()->Play(2, 10, true);
			FSM()->ChangeState(L"PIdleState");
		}
		if (m_KeyTapCount == 1)
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
		m_KeyTapCount += 1;

		FSM()->ChangeState(L"PMoveState");

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
		m_KeyTapCount -= 1;

		if (m_KeyTapCount == 0)
		{
			m_Direction = eDIR::DOWN;
			m_PrevDirection = m_Direction;
			//FlipBookComponent()->Play(0, 10, true);
			FSM()->ChangeState(L"PIdleState");
		}
		if (m_KeyTapCount == 1)
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

void PIdleState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
}


