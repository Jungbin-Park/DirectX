#pragma once
#include <Engine/CState.h>

class MoveState :
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
	CLONE_DISABLE(MoveState);
	MoveState(UINT _StateType);
	~MoveState();
};

