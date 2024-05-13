#pragma once

class CAsset;

class CAssetMgr
	: public CSingleton<CAssetMgr>
{
	SINGLE(CAssetMgr);

private:
	map<wstring, CAsset*> m_mapAsset[(UINT)ASSET_TYPE::END];

public:
	void Init();

	void AddAsset(const wstring& _strName, CAsset* _Asset);
};

