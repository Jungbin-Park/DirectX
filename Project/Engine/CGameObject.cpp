#include "pch.h"
#include "CGameObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "components.h"
#include "CScript.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)	// 어느 레이어 소속도 아니다. (레벨 안에 있지 않은 상태)
	, m_Dead(false)
{
}

CGameObject::CGameObject(const CGameObject& _Origin)
	: CEntity(_Origin)
	, m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_LayerIdx(-1)
	, m_Dead(false)
{
	// 컴포넌트 복사
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == _Origin.m_arrCom[i])
			continue;

		CComponent* pClonedCom = _Origin.m_arrCom[i]->Clone();

		AddComponent(pClonedCom);

		pClonedCom->Init();
	}

	// Script 복사
	for (size_t i = 0; i < _Origin.m_vecScript.size(); ++i)
	{
		AddComponent(_Origin.m_vecScript[i]->Clone());
	}

	// 자식 오브젝트 복사
	for (size_t i = 0; i < _Origin.m_vecChildren.size(); ++i)
	{
		AddChild(_Origin.m_vecChildren[i]->Clone());
	}
}

CGameObject::~CGameObject()
{
	Delete_Array(m_arrCom);
	Delete_Vec(m_vecScript);
	Delete_Vec(m_vecChildren);
}

void CGameObject::AddComponent(CComponent* _Component)
{
	COMPONENT_TYPE Type = _Component->GetComponentType();

	if (COMPONENT_TYPE::SCRIPT == Type)
	{
		m_vecScript.push_back((CScript*)_Component);
		_Component->SetOwner(this);
	}
	else
	{
		assert(nullptr == m_arrCom[(UINT)Type]);

		m_arrCom[(UINT)Type] = _Component;
		m_arrCom[(UINT)Type]->SetOwner(this);

		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Component);

		assert(!(pRenderCom && m_RenderCom));

		if (pRenderCom)
		{
			m_RenderCom = pRenderCom;
		}
	}
}

void CGameObject::AddChild(CGameObject* _ChildObject)
{
	// 부모 오브젝트는 Level 에 속해있고, AddChild 되는 자식 오브젝트는 레벨에 소속되지 않은 경우
	if (-1 != m_LayerIdx && -1 == _ChildObject->m_LayerIdx)
	{
		assert(nullptr);
	}

	// 자식으로 들어오는 오브젝트가 이미 부모가 있는 경우
	if (_ChildObject->GetParent())
	{
		_ChildObject->DeregisterChild();
	}

	// 자식으로 들어오는 오브젝트가 최상위 부모 오브젝트인 경우
	else
	{
		if (-1 != _ChildObject->m_LayerIdx)
		{
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			if (nullptr != pCurLevel)
			{
				CLayer* pLayer = pCurLevel->GetLayer(_ChildObject->m_LayerIdx);
				pLayer->DeregisterObjectAsParent(_ChildObject);
			}
		}
	}

	m_vecChildren.push_back(_ChildObject);
	_ChildObject->m_Parent = this;

	CLevelMgr::GetInst()->LevelChanged();
}

CGameObject* CGameObject::GetChild(const wstring& _ChildName)
{
	vector<CGameObject*>::iterator iter = m_vecChildren.begin();

	for (; iter != m_vecChildren.end(); ++iter)
	{
		if ((*iter)->GetName() == _ChildName)
		{
			return *iter;
		}
	}
}


CScript* CGameObject::GetScriptByName(const wstring& _ScriptName)
{
	vector<CScript*>::iterator iter = m_vecScript.begin();

	for (; iter != m_vecScript.end(); ++iter)
	{
		if ((*iter)->GetName() == _ScriptName)
		{
			return *iter;
		}
	}
}

bool CGameObject::IsAncestor(CGameObject* _Object)
{
	CGameObject* pObject = m_Parent;

	while (pObject)
	{
		if (pObject == _Object)
			return true;
		else
			pObject = pObject->GetParent();
	}

	return false;
}

void CGameObject::DisConnenctWithLayer()
{
	if (nullptr == m_Parent)
	{
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLayer* pLayer = pLevel->GetLayer(m_LayerIdx);
		pLayer->DisconnectWithObject(this);
	}

	m_LayerIdx = -1;
}

void CGameObject::DeregisterChild()
{
	CLevelMgr::GetInst()->LevelChanged();

	vector<CGameObject*>::iterator iter = m_Parent->m_vecChildren.begin();

	for (; iter != m_Parent->m_vecChildren.end(); ++iter)
	{
		if ((*iter) == this)
		{
			m_Parent->m_vecChildren.erase(iter);
			m_Parent = nullptr;
			return;
		}
	}

	assert(nullptr);
}

void CGameObject::Begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->Begin();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Begin();
	}

	// 자식 오브젝트
	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->Begin();
	}
}

void CGameObject::Tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->Tick();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->Tick();
	}

	// 자식 오브젝트
	for (size_t i = 0; i < m_vecChildren.size(); ++i)
	{
		m_vecChildren[i]->Tick();
	}
}

void CGameObject::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if(nullptr != m_arrCom[i])
			m_arrCom[i]->FinalTick();
	}

	// 레이어 등록
	assert(-1 != m_LayerIdx);
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pLevel->GetLayer(m_LayerIdx);
	pLayer->RegisterGameObject(this);

	// 자식 오브젝트
	vector<CGameObject*>::iterator iter = m_vecChildren.begin();
	for (; iter != m_vecChildren.end();)
	{
		(*iter)->FinalTick();

		if ((*iter)->IsDead())
			iter = m_vecChildren.erase(iter);
		else
			++iter;
	}
}

void CGameObject::Render()
{
	if(m_RenderCom)
		m_RenderCom->Render();
}


