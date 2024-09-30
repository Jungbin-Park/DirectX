#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	BOSSHUDSCRIPT,
	BOSSSCRIPT,
	BSLASHSCRIPT,
	CAMERAMOVESCRIPT,
	CHARGEEFFECTSCRIPT,
	CRYSTALSCRIPT,
	FIREBALLSCRIPT,
	FIREDRAGONSCRIPT,
	GHOULSCRIPT,
	HITSPARKSCRIPT,
	LANCESCRIPT,
	MANAGERSCRIPT,
	MARKERSCRIPT,
	MATTACKSCRIPT,
	PLATFORMSCRIPT,
	PLAYERHUDSCRIPT,
	PLAYERMPSCRIPT,
	PLAYERSCRIPT,
	PORTALSCRIPT,
	SLASHSCRIPT,
	SPAWNERSCRIPT,
	TELEPORTSCRIPT,
	TRIGGERSCRIPT,
	CURSORSCRIPT,
	WATERSCRIPT,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static CScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(CScript * _pScript);
};
