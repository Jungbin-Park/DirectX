#pragma once
#include "singleton.h"

class CCamera;
class CGameObject;

class CRenderMgr :
	public CSingleton<CRenderMgr>
{
	SINGLE(CRenderMgr)
private:
	vector<CCamera*>		m_vecCam;

	CGameObject*			m_DebugObject;
	list<tDebugShapeInfo>	m_DebugShapeList;

public:
	void RegisterCamera(CCamera* _Cam, int _CamPriority);
	void AddDebugShapeInfo(const tDebugShapeInfo& _Info) { m_DebugShapeList.push_back(_Info); }

private:
	void RenderDebugShape();

public:
	void Init();
	void Tick();
};

