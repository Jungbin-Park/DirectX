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
		if (m_WaitTime >= 1.f)
		{
			m_bWaitStart = false;

			if (m_bLance)
			{
				GetOwner()->FSM()->ChangeState(L"BLanceState");
			}
			else if (m_bSword)
			{
				GetOwner()->FSM()->ChangeState(L"BDashState");
			}
			else if (m_bWater)
			{
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

	if (m_bLance)
	{
		m_bLance = false;
		m_bSword = true;
		m_bWater = false;
	}
		
	else if (m_bSword)
	{
		m_bSword = false;
		m_bWater = true;
		m_bLance = false;
	}
		
	else if (m_bWater)
	{
		m_bWater = false;
		m_bLance = true;
		m_bSword = false;
	}
		

	/*int rand = std::rand() % 3 + 1;

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
	}*/


}


