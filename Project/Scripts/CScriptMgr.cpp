#include "pch.h"
#include "CScriptMgr.h"

#include "CBossScript.h"
#include "CBSlashScript.h"
#include "CCameraMoveScript.h"
#include "CCrystalScript.h"
#include "CGhoulScript.h"
#include "CLanceScript.h"
#include "CManagerScript.h"
#include "CMarkerScript.h"
#include "CMAttackScript.h"
#include "CPlatformScript.h"
#include "CPlayerScript.h"
#include "CSlashScript.h"
#include "CSpawnerScript.h"
#include "CTriggerScript.h"
#include "CursorScript.h"
#include "CWaterScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBossScript");
	_vec.push_back(L"CBSlashScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CCrystalScript");
	_vec.push_back(L"CGhoulScript");
	_vec.push_back(L"CLanceScript");
	_vec.push_back(L"CManagerScript");
	_vec.push_back(L"CMarkerScript");
	_vec.push_back(L"CMAttackScript");
	_vec.push_back(L"CPlatformScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CSlashScript");
	_vec.push_back(L"CSpawnerScript");
	_vec.push_back(L"CTriggerScript");
	_vec.push_back(L"CursorScript");
	_vec.push_back(L"CWaterScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBossScript" == _strScriptName)
		return new CBossScript;
	if (L"CBSlashScript" == _strScriptName)
		return new CBSlashScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CCrystalScript" == _strScriptName)
		return new CCrystalScript;
	if (L"CGhoulScript" == _strScriptName)
		return new CGhoulScript;
	if (L"CLanceScript" == _strScriptName)
		return new CLanceScript;
	if (L"CManagerScript" == _strScriptName)
		return new CManagerScript;
	if (L"CMarkerScript" == _strScriptName)
		return new CMarkerScript;
	if (L"CMAttackScript" == _strScriptName)
		return new CMAttackScript;
	if (L"CPlatformScript" == _strScriptName)
		return new CPlatformScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CSlashScript" == _strScriptName)
		return new CSlashScript;
	if (L"CSpawnerScript" == _strScriptName)
		return new CSpawnerScript;
	if (L"CTriggerScript" == _strScriptName)
		return new CTriggerScript;
	if (L"CursorScript" == _strScriptName)
		return new CursorScript;
	if (L"CWaterScript" == _strScriptName)
		return new CWaterScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BOSSSCRIPT:
		return new CBossScript;
		break;
	case (UINT)SCRIPT_TYPE::BSLASHSCRIPT:
		return new CBSlashScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::CRYSTALSCRIPT:
		return new CCrystalScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULSCRIPT:
		return new CGhoulScript;
		break;
	case (UINT)SCRIPT_TYPE::LANCESCRIPT:
		return new CLanceScript;
		break;
	case (UINT)SCRIPT_TYPE::MANAGERSCRIPT:
		return new CManagerScript;
		break;
	case (UINT)SCRIPT_TYPE::MARKERSCRIPT:
		return new CMarkerScript;
		break;
	case (UINT)SCRIPT_TYPE::MATTACKSCRIPT:
		return new CMAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::PLATFORMSCRIPT:
		return new CPlatformScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::SLASHSCRIPT:
		return new CSlashScript;
		break;
	case (UINT)SCRIPT_TYPE::SPAWNERSCRIPT:
		return new CSpawnerScript;
		break;
	case (UINT)SCRIPT_TYPE::TRIGGERSCRIPT:
		return new CTriggerScript;
		break;
	case (UINT)SCRIPT_TYPE::CURSORSCRIPT:
		return new CursorScript;
		break;
	case (UINT)SCRIPT_TYPE::WATERSCRIPT:
		return new CWaterScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BOSSSCRIPT:
		return L"CBossScript";
		break;

	case SCRIPT_TYPE::BSLASHSCRIPT:
		return L"CBSlashScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::CRYSTALSCRIPT:
		return L"CCrystalScript";
		break;

	case SCRIPT_TYPE::GHOULSCRIPT:
		return L"CGhoulScript";
		break;

	case SCRIPT_TYPE::LANCESCRIPT:
		return L"CLanceScript";
		break;

	case SCRIPT_TYPE::MANAGERSCRIPT:
		return L"CManagerScript";
		break;

	case SCRIPT_TYPE::MARKERSCRIPT:
		return L"CMarkerScript";
		break;

	case SCRIPT_TYPE::MATTACKSCRIPT:
		return L"CMAttackScript";
		break;

	case SCRIPT_TYPE::PLATFORMSCRIPT:
		return L"CPlatformScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::SLASHSCRIPT:
		return L"CSlashScript";
		break;

	case SCRIPT_TYPE::SPAWNERSCRIPT:
		return L"CSpawnerScript";
		break;

	case SCRIPT_TYPE::TRIGGERSCRIPT:
		return L"CTriggerScript";
		break;

	case SCRIPT_TYPE::CURSORSCRIPT:
		return L"CursorScript";
		break;

	case SCRIPT_TYPE::WATERSCRIPT:
		return L"CWaterScript";
		break;

	}
	return nullptr;
}