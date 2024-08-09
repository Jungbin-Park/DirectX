#include "pch.h"
#include "CMeshRender.h"

#include "CTransform.h"
#include "CFlipBookComponent.h"
#include "CSprite.h"

CMeshRender::CMeshRender()
	:CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::FinalTick()
{
}

void CMeshRender::Render()
{
	if (!GetMesh() || !GetMaterial() || !GetMaterial()->GetShader())
		return;

	if (FlipBookComponent())
	{
		Ptr<CSprite> pCurSprite = FlipBookComponent()->GetCurSprite();

		pCurSprite->GetAtlasTexture()->Binding(10);
		GetMaterial()->SetScalarParam(VEC2_0, pCurSprite->GetLeftTopUV());
		GetMaterial()->SetScalarParam(VEC2_1, pCurSprite->GetSliceUV());
		GetMaterial()->SetScalarParam(INT_0, 1);
	}
	else
	{
		GetMaterial()->SetScalarParam(INT_0, 0);
	}

	Transform()->Binding();
	GetMaterial()->Binding();
	GetMesh()->render();
}
