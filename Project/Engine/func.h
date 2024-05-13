#pragma once

template<typename T>
void Delete_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}

template<typename T1, typename T2>
void Delete_Map(map<T1, T2>& _map)
{
	for (const auto& pair : _map)
	{
		if (nullptr != pair.second)
			delete pair.second;
	}

	_map.clear();
}

#include "assets.h"
template<typename T>
ASSET_TYPE GetAssetType()
{
	if (typeid(T).hash_code() == typeid(CMesh).hash_code())
		return ASSET_TYPE::MESH;
	//if (typeid(T).hash_code() == typeid(CMeshData).hash_code())
	//	return ASSET_TYPE::MESH_DATA;
	//if (typeid(T).hash_code() == typeid(CMaterial).hash_code())
	//	return ASSET_TYPE::MATERIAL;
	//if (typeid(T).hash_code() == typeid(CPrefab).hash_code())
	//	return ASSET_TYPE::PREFAB;
	//if (typeid(T).hash_code() == typeid(CTexture).hash_code())
	//	return ASSET_TYPE::TEXTURE;
	//if (typeid(T).hash_code() == typeid(CSound).hash_code())
	//	return ASSET_TYPE::SOUND;
	if (typeid(T).hash_code() == typeid(CGraphicShader).hash_code())
		return ASSET_TYPE::GRAPHIC_SHADER;
	if (typeid(T).hash_code() == typeid(CComputeShader).hash_code())
		return ASSET_TYPE::COMPUTE_SHADER;

}