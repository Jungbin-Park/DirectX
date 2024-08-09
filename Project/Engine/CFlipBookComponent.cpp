#include "pch.h"
#include "CFlipBookComponent.h"

#include "CTimeMgr.h"

#include "CFlipBook.h"

CFlipBookComponent::CFlipBookComponent()
	:CComponent(COMPONENT_TYPE::FLIPBOOKCOMPONENT)
	, m_CurFlipBook(nullptr)
	, m_CurFrmIdx(0)
{
}

CFlipBookComponent::~CFlipBookComponent()
{
}

void CFlipBookComponent::FinalTick()
{
	if (m_Finish)
	{
		if (false == m_Repeat)
			return;

		Reset();
	}

	if (nullptr != m_CurFlipBook)
	{
		float MaxTime = 1.f / m_FPS;

		m_AccTime += DT;

		if (MaxTime < m_AccTime)
		{
			m_AccTime -= MaxTime;
			++m_CurFrmIdx;

			if (m_CurFlipBook->GetMaxFrameCount() <= m_CurFrmIdx)
			{
				--m_CurFrmIdx;
				m_Finish = true;
			}
		}

		m_CurFrmSprite = m_CurFlipBook->GetSprite(m_CurFrmIdx);
	}
}

void CFlipBookComponent::AddFlipBook(Ptr<CFlipBook> _Flipbook)
{
	// 동일한 FlipBook 이 이미 컴포넌트에 등록된 적이 있다면	
	m_vecFlipBook.push_back(_Flipbook);
}

Ptr<CFlipBook> CFlipBookComponent::FindFlipBook(const wstring& _Key)
{
	for (size_t i = 0; i < m_vecFlipBook.size(); ++i)
	{
		if (m_vecFlipBook[i]->GetKey() == _Key)
			return m_vecFlipBook[i];
	}

	return nullptr;
}

void CFlipBookComponent::Play(int _FliBookIdx, float _FPS, bool _Repeat)
{
	m_CurFlipBook = m_vecFlipBook[_FliBookIdx];

	if (nullptr == m_CurFlipBook)
		return;

	m_CurFrmIdx = 0;
	m_AccTime = 0.f;
	m_FPS = _FPS;
	m_Repeat = _Repeat;
}

void CFlipBookComponent::Reset()
{
	m_CurFrmIdx = 0;
	m_AccTime = 0.f;
	m_Finish = false;
}
