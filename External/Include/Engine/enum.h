#pragma once

enum class CB_TYPE
{
	TRANSFORM,

	MATERIAL,

	GLOBAL,

	END,
};

enum class ASSET_TYPE
{
	MESH,
	MESH_DATA,
	MATERIAL,
	PREFAB,
	TEXTURE,
	SOUND,
	GRAPHIC_SHADER,
	COMPUTE_SHADER,
	END,
};

enum class COMPONENT_TYPE
{
	TRANSFORM,
	COLLIDER2D,
	COLLIDER3D,
	ANIMATOR2D,
	ANIMATOR3D,
	STATE_MACHINE,
	RIGIDBODY,
	CAMERA,

	MESHRENDER,
	TILEMAP,
	PARTICLE_SYSTEM,
	DECAL,
	SKYBOX,
	LANDSCAPE,

	END,

	SCRIPT,
};

enum DIR
{
	RIGHT,
	UP,
	FRONT,
};