#pragma once

// 정점(Vertex) 구조체
struct Vtx
{
	Vec3	vPos;	// 좌표
	Vec4	vColor;	// 색상
	Vec2	vUV;
};

struct tDebugShapeInfo
{
	DEBUG_SHAPE		Shape;
	Vec3			vPos;
	Vec3			vScale;
	Vec3			vRot;
	Matrix			matWorld;
	Vec4			vColor;
	float			LifeTime;
	float			Age;
	bool			DepthTest;	// 깊이 판정 여부
};

struct tTask
{
	TASK_TYPE	Type;
	DWORD_PTR	Param_0;
	DWORD_PTR	Param_1;
};


// ====================
// 상수 버퍼 연동 구조체
// ====================	
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;

	Matrix matWV;
	Matrix matWVP;
};

extern tTransform g_Trans;

struct tMtrlConst
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matArr[4];
	int btex[TEX_PARAM::END + 2];
};

struct tSpriteInfo
{
	Vec2 LeftTopUV;
	Vec2 SliceUV;
	Vec2 BackGroundUV;
	Vec2 OffsetUV;
	int UseFlipbook;
	int Padding[3];
};