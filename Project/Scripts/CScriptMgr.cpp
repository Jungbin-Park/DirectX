#include "pch.h"
#include "CScriptMgr.h"

#include "CCameraMoveScript.h"
#include "CMarkerScript.h"
#include "CPlayerScript.h"
#include "CSlashScript.h"
#include "CursorScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CMarkerScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CSlashScript");
	_vec.push_back(L"CursorScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CMarkerScript" == _strScriptName)
		return new CMarkerScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CSlashScript" == _strScriptName)
		return new CSlashScript;
	if (L"CursorScript" == _strScriptName)
		return new CursorScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::MARKERSCRIPT:
		return new CMarkerScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::SLASHSCRIPT:
		return new CSlashScript;
		break;
	case (UINT)SCRIPT_TYPE::CURSORSCRIPT:
		return new CursorScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::MARKERSCRIPT:
		return L"CMarkerScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::SLASHSCRIPT:
		return L"CSlashScript";
		break;

	case SCRIPT_TYPE::CURSORSCRIPT:
		return L"CursorScript";
		break;

	}
	return nullptr;
}