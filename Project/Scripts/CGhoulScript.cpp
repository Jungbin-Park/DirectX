#include "pch.h"
#include "CGhoulScript.h"

#include <States/CStateMgr.h>
#include <States/IdleState.h>
#include <States/AttackState.h>
#include <States/MoveState.h>
#include <States/HitState.h>
#include <States/DeadState.h>


CGhoulScript::CGhoulScript()
	: CScript(SCRIPT_TYPE::GHOULSCRIPT)
	, m_Speed(300.f)
	, m_HP(100.f)
	, m_Cooldown(3.f)
	, m_DetectRange(500.f)
	, m_AttackRange(100.f)
{ 
}

CGhoulScript::~CGhoulScript()
{
}

void CGhoulScript::Begin()
{
	FSM()->AddState(L"IdleState", new IdleState(STATE_TYPE::IDLESTATE));
	FSM()->AddState(L"AttackState", new AttackState(STATE_TYPE::ATTACKSTATE));
	FSM()->AddState(L"MoveState", new MoveState(STATE_TYPE::MOVESTATE));
	FSM()->AddState(L"HitState", new HitState(STATE_TYPE::HITSTATE));
	FSM()->AddState(L"DeadState", new DeadState(STATE_TYPE::DEADSTATE));

	Ptr<CFlipBook> pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulIdleLeft.flip");
	FlipBookComponent()->AddFlipBook(0, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulIdleRight.flip");
	FlipBookComponent()->AddFlipBook(1, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulAttackLeft.flip");
	FlipBookComponent()->AddFlipBook(2, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulAttackRight.flip");
	FlipBookComponent()->AddFlipBook(3, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulMoveLeft.flip");
	FlipBookComponent()->AddFlipBook(4, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhoulMoveRight.flip");
	FlipBookComponent()->AddFlipBook(5, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhouldDeadLeft.flip");
	FlipBookComponent()->AddFlipBook(6, pFlipBook);
	pFlipBook = CAssetMgr::GetInst()->FindAsset<CFlipBook>(L"Animation\\GhouldDeadRight.flip");
	FlipBookComponent()->AddFlipBook(7, pFlipBook);

	FlipBookComponent()->Play(0, 10, false);
	FSM()->ChangeState(L"IdleState");
}

void CGhoulScript::Tick()
{
}

void CGhoulScript::BeginOverlap(CCollider2D* _OwnCollider, CGameObject* _OtherObject, CCollider2D* _OtherCollider)
{
}

void CGhoulScript::SaveToFile(FILE* _File)
{
}

void CGhoulScript::LoadFromFile(FILE* _File)
{
}



