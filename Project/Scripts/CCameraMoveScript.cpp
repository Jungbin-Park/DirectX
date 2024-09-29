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
	, m_BossSpawn(false)
	, m_Dir(Vec3(0.f, 0.f, 0.f))
	, m_Timer(0.f)
{
	//AddScriptParam(SCRIPT_PARAM::PREFAB, "FollowObject", &m_FollowObj);
}

CCameraMoveScript::~CCameraMoveScript()
{
}



void CCameraMoveScript::Begin()
{
	SetName(L"CCameraMoveScript");

	m_FollowObj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
}

void CCameraMoveScript::Tick()
{
	/*if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
	{
		OrthoGraphicMove();
	}
	else if (PROJ_TYPE::PERSPECTIVE == Camera()->GetProjType())
	{
		PerspectiveMove();
	}*/

	if (m_BossSpawn)
	{
		m_Timer += DT;

		Vec3 vBossPos = Vec3(0.f, 1200.f, 0.f);
		Vec3 vPos = Transform()->GetRelativePos();
		Vec3 vDir = vBossPos - vPos;
		vDir.Normalize();

		m_Dir = vDir;

		if (fabs(vDir.x - m_Dir.x) < 0.001f && fabs(vDir.y - m_Dir.y) < 0.001f)
		{
			vPos += vDir * m_CamSpeed * DT;
		}

		Transform()->SetRelativePos(Vec3(vPos.x, vPos.y, 0.f));

		if (m_Timer >= 3.f)
		{
			m_BossSpawn = false;
			m_Timer = 0.f;
		}
		
	}
	else
	{
		if (m_FollowObj)
		{
			Vec3 vPos = Transform()->GetRelativePos();
			Vec3 objPos = m_FollowObj->Transform()->GetRelativePos();

			vPos = objPos;

			Transform()->SetRelativePos(vPos);
		}
		else
		{

		}
	}
	
}

void CCameraMoveScript::BossSpawn()
{
	m_BossSpawn = true;

	Vec3 vBossPos = Vec3(0.f, 1200.f, 0.f);
	Vec3 vPos = Transform()->GetRelativePos();
	m_Dir = vBossPos - vPos;
	m_Dir.Normalize();
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
