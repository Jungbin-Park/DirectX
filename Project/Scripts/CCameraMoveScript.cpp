#include "pch.h"
#include "CCameraMoveScript.h"

#include <Engine/CCamera.h>
#include <Engine/CGameObject.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>


CCameraMoveScript::CCameraMoveScript()
	: CScript(UINT(SCRIPT_TYPE::CAMERAMOVESCRIPT))
	, m_CamSpeed(500.f)
	, m_FollowObj(nullptr)
{
	//AddScriptParam(SCRIPT_PARAM::PREFAB, "FollowObject", &m_FollowObj);
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::Begin()
{
	m_FollowObj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
}

void CCameraMoveScript::Tick()
{
	if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
	{
		OrthoGraphicMove();
	}
	else if (PROJ_TYPE::PERSPECTIVE == Camera()->GetProjType())
	{
		PerspectiveMove();
	}

	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 objPos = m_FollowObj->Transform()->GetRelativePos();

	vPos = objPos;

	Transform()->SetRelativePos(vPos);
}

void CCameraMoveScript::OrthoGraphicMove()
{
	
}

void CCameraMoveScript::PerspectiveMove()
{
	float Speed = m_CamSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		Speed *= 3.f;
	}

	Vec3 vFront = Transform()->GetWorldDir(DIR::FRONT);
	Vec3 vRight = Transform()->GetWorldDir(DIR::RIGHT);

	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos += vFront * DT * Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos -= vFront * DT * Speed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos -= vRight * DT * Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos += vRight * DT * Speed;
	}

	Transform()->SetRelativePos(vPos);

	if (KEY_PRESSED(KEY::RBTN))
	{
		CKeyMgr::GetInst()->MouseCapture(true);

		// 마우스가 이동하는 방향
		//vDir.x; ==> y축 회전;
		//vDir.y; ==> x축 회전
		Vec2 vDir = CKeyMgr::GetInst()->GetDragDir();

		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.y += vDir.x * XM_PI * DT * 10.f;
		vRot.x += vDir.y * XM_PI * DT * 10.f;
		Transform()->SetRelativeRotation(vRot);
	}
	else if (KEY_RELEASED(KEY::RBTN))
	{
		CKeyMgr::GetInst()->MouseCapture(false);
	}
}

void CCameraMoveScript::SaveToFile(FILE* _File)
{
	fwrite(&m_CamSpeed, sizeof(float), 1, _File);
}

void CCameraMoveScript::LoadFromFile(FILE* _File)
{
	fread(&m_CamSpeed, sizeof(float), 1, _File);
}
