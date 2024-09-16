#pragma once
#include <Engine/CState.h>

class IdleState :
    public CState
{


public:
	virtual void Enter();
	virtual void FinalTick();
	virtual void Exit();

public:
	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

public:
	CLONE_DISABLE(IdleState);
	IdleState(UINT _StateType);
	~IdleState();
};

