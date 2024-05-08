#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CUI.h"

CTaskMgr::CTaskMgr()
{}

CTaskMgr::~CTaskMgr()
{}

void CTaskMgr::tick()
{
	ClearGC();

	ExecuteTask();
}

void CTaskMgr::ClearGC()
{
	Safe_Del_Vec(m_GC);

	m_GC.clear();
}

void CTaskMgr::ExecuteTask()
{
	static bool bLevelChanged = false;
	bLevelChanged = false;

	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::SPAWN_OBJECT:
		{
			CLevel* pSpawnLevel = (CLevel*)m_vecTask[i].Param1;
			LAYER_TYPE Layer = (LAYER_TYPE)m_vecTask[i].Param2;
			CObj* pObj = (CObj*)m_vecTask[i].Param3;

			if (CLevelMgr::GetInst()->GetCurrentLevel() != pSpawnLevel)
			{
				delete pObj;
			}
			pSpawnLevel->AddObject(Layer, pObj);
			pObj->begin();
		}
		break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			CObj* pObject = (CObj*)m_vecTask[i].Param1;
			if (pObject->m_bDead)
			{
				continue;
			}
			pObject->m_bDead = true;

			// GC 에서 수거
			m_GC.push_back(pObject);
		}
		break;

		case TASK_TYPE::CHANGE_LEVEL:
		{
			assert(!bLevelChanged);
			bLevelChanged = true;


			LEVEL_TYPE NextType = (LEVEL_TYPE)m_vecTask[i].Param1;
			CLevelMgr::GetInst()->ChangeLevel(NextType);
		}
			break;

		case TASK_TYPE::UI_LBTN_DOWN:
		{
			CUI* pUI = (CUI*)m_vecTask[i].Param1;
			bool bLbtnDown = (bool)m_vecTask[i].Param2;
			pUI->m_MouseLbtnDown = bLbtnDown;
		}


			break;
		}

	}

	m_vecTask.clear();	
}