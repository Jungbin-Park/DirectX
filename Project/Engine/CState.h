#pragma once
#include "CEntity.h"

#include "CGameObject.h"
#include "CFlipBook.h"
#include "CFlipBookComponent.h"
#include "CFSM.h"

//class CFSM;

class CState :
    public CEntity
{
private:
	CFSM*					m_Owner;

	const UINT              m_StateType;

public:
	UINT GetStateType() { return m_StateType; }

protected:
	CGameObject* GetOwner() { return m_Owner->GetOwner(); }
	CFSM* GetFSM() { return m_Owner; }

	void ChangeState(const wstring& _strStateName);
	CGameObject* InstantiateSkill(Ptr<CPrefab> _Pref, int _LayerIdx, Vec3 _WorldPos, const wstring& _Name = L"");

public:
	virtual void Enter() = 0;
	virtual void FinalTick() = 0;
	virtual void Exit() = 0;

	virtual void SaveToFile(FILE* _File) {}
	virtual void LoadFromFile(FILE* _File) {}

public:
	CLONE_DISABLE(CState);
	CState(UINT _StateType);
	~CState();

	friend class CFSM;
};

