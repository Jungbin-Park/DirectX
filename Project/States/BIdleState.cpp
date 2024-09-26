#include "pch.h"
#include "BIdleState.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CTimeMgr.h>
#include <Engine/components.h>

BIdleState::BIdleState()
	: CState(STATE_TYPE::BOSSIDLESTATE)
	, m_WaitTime(0.f)
	, m_bWaitStart(true)
	, m_bLance(true)
	, m_bWater(false)
	, m_bSword(false)
{
}

BIdleState::~BIdleState()
{
}

void BIdleState::Enter()
{
	GetOwner()->FlipBookComponent()->Play(1, 10, false);
	m_bWaitStart = true;
}

void BIdleState::FinalTick()
{
	if (m_bWaitStart)
	{
		m_WaitTime += DT;
		if (m_WaitTime >= 2.f)
		{
			m_bWaitStart = false;

			if (m_bLance)
			{
				m_bLance = false;
				GetOwner()->FSM()->ChangeState(L"BLanceState");
			}
			else if (m_bSword)
			{
				m_bSword = false;
				GetOwner()->FSM()->ChangeState(L"BSlashState");
			}
			else if (m_bWater)
			{
				m_bWater = false;
				GetOwner()->FSM()->ChangeState(L"BWaterState");
			}
			
		}
	}
	
}

void BIdleState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
	m_bWaitStart = false;
	m_WaitTime = 0.f;

	int rand = std::rand() % 3 + 1;

	switch (rand)
	{
	case 1:
		m_bLance = true;
		break;
	case 2:
		m_bSword = true;
		break;
	case 3:
		m_bWater = true;
		break;
	}
}


