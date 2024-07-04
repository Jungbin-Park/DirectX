#pragma once

class CLevel;

class CLevelMgr
	: public CSingleton<CLevelMgr>
{
	SINGLE(CLevelMgr);
private:
	CLevel*		m_CurLevel;

public:
	CLevel* GetCurrentLevel() { return m_CurLevel; }

public:
	void Init();
	void Progress();
};

