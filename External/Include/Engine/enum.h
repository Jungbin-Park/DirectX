#pragma once

enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL,
	SPRITE,
	GLOBAL,
	HUD,
	HUDMP,
	BOSSHUD,
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
	SPRITE,
	FLIPBOOK,
	END,
};

extern const char* ASSET_TYPE_STRING[(UINT)ASSET_TYPE::END];
const char* ToString(ASSET_TYPE _Type);

enum class COMPONENT_TYPE
{
	TRANSFORM,
	COLLIDER2D,
	COLLIDER3D,
	LIGHT2D,
	LIGHT3D,
	FLIPBOOKCOMPONENT,
	ANIMATOR3D,
	FSM,
	RIGIDBODY,
	CAMERA,

	MESHRENDER,
	TILEMAP,
	PARTICLESYSTEM,
	DECAL,
	SKYBOX,
	LANDSCAPE,

	END,

	SCRIPT,
};

extern const char* COMPONENT_TYPE_STRING[(UINT)COMPONENT_TYPE::END];
const char* ToString(COMPONENT_TYPE _Type);

enum class eDIR
{
	NONE,
	UP,
    UP_LEFT,
    UP_RIGHT,
    DOWN,
    DOWN_LEFT,
    DOWN_RIGHT,
    LEFT,
    RIGHT,
	FRONT,
};

enum DIR
{
	RIGHT,
	UP,
	FRONT,
};

enum class RS_TYPE
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,
	END,
};

enum class DS_TYPE
{
	LESS,				// 가까운 통과
	LESS_EQUAL,			// 가깝거나 같은 경우 통과

	GREATER,			// 더 멀면 통과

	NO_TEST,			// 깊이 판정 X
	NO_WRITE,
	NO_TEST_NO_WRITE,	// 깊이 판정 X, 기록 X

	END,
};

enum class BS_TYPE
{
	DEFAULT,
	ALPHABLEND_COVERAGE,
	ALPHABLEND,
	ONE_ONE,
	END,
};

enum SCALAR_PARAM
{
	INT_0,   INT_1,   INT_2,   INT_3,
	FLOAT_0, FLOAT_1, FLOAT_2, FLOAT_3,
	VEC2_0,  VEC2_1,  VEC2_2,  VEC2_3,
	VEC4_0,  VEC4_1,  VEC4_2,  VEC4_3,
	MAT_0,   MAT_1,   MAT_2,   MAT_3,
};

enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEXCUBE_0,
	TEXCUBE_1,

	TEXARR_0,
	TEXARR_1,

	END,
};

enum SHADER_DOMAIN
{
	DOMAIN_OPAQUE,		// 불투명
	DOMAIN_MASKED,		// 불투명한 영역과 투명한 영역이 나뉠 때
	DOMAIN_TRANSPARENT, // 반투명
	DOMAIN_PARTICLE,	// 파티클(입자)
	DOMAIN_POSTPROCESS, // 후처리
	DOMAIN_UI,			// UI
	DOMAIN_DEBUG,		// 디버그
	DOMAIN_NONE,		// 미설정
};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,
	CUBE,
	SPHERE,
};

enum TASK_TYPE
{
	// Param_0 : Layer, Param_1 : Object Address
	CREATE_OBJECT,

	// Param_0 : Delete Object Address
	DELETE_OBJECT,

	// Param_0 : Next Level State
	CHANGE_LEVELSTATE,

	// Param_0 : Level Address, Param_1 : Level State
	CHANGE_LEVEL,

	// Param_0 : AssetAddress
	DEL_ASSET,

	LEVEL_CHANGED,
	ASSET_CHANGED,

	ADD_CHILD,
	COMPONENT_ACTIVATE,
	COMPONENT_DEACTIVATE,
};

enum LEVEL_STATE
{
	PLAY,
	PAUSE,
	STOP,
};

enum class LIGHT_TYPE
{
	DIRECTIONAL,
	POINT,
	SPOT,
};