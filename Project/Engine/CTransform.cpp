#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"


CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
{
}

CTransform::~CTransform()
{
}

void CTransform::FinalTick()
{
}

void CTransform::Binding()
{
	m_matWorld = XMMatrixIdentity();
	m_matWorld.Translation();	// 상태 행렬에서 4행 1, 2, 3열 반환, 이동 값.

	// GPU에 행렬 데이터를 전달하는 과정에서 발생하는 전치를 미리 예상해서 전치를 하거나
	// HLSL에서 행렬 변수를 선언할 때 row_major를 붙여주어야 한다.
	//XMMatrixTranspose(m_matWorld);

	tTransform trans = {};
	trans.Pos = m_RelativePos;
	trans.Scale = m_RelativeScale;

	CConstBuffer* pTransformCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformCB->SetData(&trans);
	pTransformCB->Binding();

	
}

