#include "pch.h"
#include "PMoveState.h"

#include <Engine/components.h>

#include <Scripts/CPlayerScript.h>

#include "PIdleState.h"

PMoveState::PMoveState()
	: CState(STATE_TYPE::PLAYERMOVESTATE)
	, m_Speed(400.f)
	, m_Direction(eDIR::NONE)
	, m_CollisionDir(eDIR::NONE)
{
}

PMoveState::~PMoveState()
{
}

void PMoveState::Enter()
{
	//CPlayerScript* pScript = (CPlayerScript*)GetOwner()->GetScriptByName(L"CPlayerScript");
}

void PMoveState::FinalTick()
{
	CPlayerScript* pScript = (CPlayerScript*)GetOwner()->GetScriptByName(L"CPlayerScript");
	m_Direction = pScript->GetDirection();
	m_CollisionDir = pScript->GetColDirection();

	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::A))
	{
		if (m_CollisionDir != eDIR::RIGHT)
		{
			vPos.x -= DT * m_Speed;
		}
	}

	if (KEY_PRESSED(KEY::D))
	{
		if (m_CollisionDir != eDIR::LEFT)
		{
			vPos.x += DT * m_Speed;
		}
	}

	if (KEY_PRESSED(KEY::W))
	{
		if (m_CollisionDir != eDIR::DOWN)
		{
			vPos.y += DT * m_Speed;
		}
	}

	if (KEY_PRESSED(KEY::S))
	{
		if (m_CollisionDir != eDIR::UP)
		{
			vPos.y -= DT * m_Speed;
		}
	}

	GetOwner()->Transform()->SetRelativePos(vPos);
}

void PMoveState::Exit()
{
	GetOwner()->FlipBookComponent()->Reset();
}



