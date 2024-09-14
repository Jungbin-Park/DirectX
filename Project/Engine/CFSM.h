#pragma once
#include "CComponent.h"

class CState;

class CFSM :
    public CComponent
{
private:
    map<wstring, CState*>	m_mapState;

    CState*                 m_CurState;
    CState*                 m_PrevState;

private:
    void ChangeState_proc(CState* _pNextState);

public:
    CState* GetCurState() { return m_CurState; }
    const map<wstring, CState*>& GetStates() { return m_mapState; }
    void SetState(const wstring& _strState) { m_CurState = FindState(_strState); }
        
public:
    CState* FindState(const wstring& _strStateName);
    void AddState(const wstring& _strStateName, CState* _State);
    void DeleteState(const wstring& _StateKey);
    void ChangeState(const wstring& _strNextStateName);

public:
    virtual void Init() override;
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void FinalTick() override;

public:
    virtual int Save(const wstring& _strRelativePath);
    virtual int Load(const wstring& _strFilePath);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CFSM);
    CFSM();
    CFSM(const CFSM& _Other);
    ~CFSM();
};

