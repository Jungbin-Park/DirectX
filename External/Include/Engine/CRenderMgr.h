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
	CCamera*				m_EditorCamera;

	CGameObject*			m_DebugObject;
	list<tDebugShapeInfo>	m_DebugShapeList;

public:
	void RegisterCamera(CCamera* _Cam, int _CamPriority);
	void RegisterEditorCamera(CCamera* _Cam) { m_EditorCamera = _Cam; }
	void AddDebugShapeInfo(const tDebugShapeInfo& _Info) { m_DebugShapeList.push_back(_Info); }

private:
	void RenderDebugShape();

public:
	void Init();
	void Tick();
};

