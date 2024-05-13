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

	CAsset* FindAsset(ASSET_TYPE _Type, const wstring& _Key);
	//void AddAsset(const wstring& _strName, CAsset* _Asset);

	template<typename T>
	T* FindAsset(const wstring& _Key);

	template<typename T>
	void AddAsset(const wstring& _Key, T* _Asset);
};

template<typename T>
inline T* CAssetMgr::FindAsset(const wstring& _Key)
{
	ASSET_TYPE Type = GetAssetType<T>();

	map<wstring, CAsset*>::iterator iter = m_mapAsset[(UINT)Type].find(_Key);

	if (iter == m_mapAsset[(UINT)Type].end())
		return nullptr;

	return (T*)iter->second;
}

template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _Key, T* _Asset)
{
	ASSET_TYPE Type = GetAssetType<T>();

	assert(!FindAsset(Type, _Key));

	m_mapAsset[(UINT)Type].insert(make_pair(_Key, _Asset));
}
