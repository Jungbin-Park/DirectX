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

struct tLight
{
	Vec4	Color;		// 빛의 색상
	Vec4	Ambient;	// 환경광	
};

struct tLightInfo
{
	tLight		light;		// 광원 색상정보
	Vec3		WorldPos;	// 광원 위치
	Vec3		WorldDir;	// 광윈이 진행하는 방향
	float		Radius;		// 광원의 반경
	float		Angle;		// 광원 범위 각도
	LIGHT_TYPE	Type;		// 광원 종류
	int			padding[3]; // 패딩
};

struct tPixel
{
	BYTE b;
	BYTE g;
	BYTE r;
	BYTE a;
};

// Particle
struct tParticle
{
	Vec3	vLocalPos;
	Vec3	vWorldPos;
	Vec3	vWorldScale;
	Vec4	vColor;

	Vec3	vForce;
	Vec3	vVelocity;

	float	Mass;
	int		Active;

	int		Padding[3];
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

struct tGlobalData
{
	// 시간 관련 정보
	float   g_DT;
	float   g_EngineDT;
	float   g_Time;
	float   g_EngineTime;

	// 렌더타겟의 해상도 정보
	Vec2	g_Resolution;

	// 바인딩 된 구조화버퍼에 광원이 몇개 들어있는지
	int     g_Light2DCount;
	int     g_Light3DCount;
};
extern tGlobalData g_GlobalData;

struct tHUD
{
	float HPRatio;
	float Padding1;
	float Padding2;
	float Padding3;
};

struct tHUDMP
{
	float MPRatio;
	float Padding1;
	float Padding2;
	float Padding3;
};

struct tBOSSHUD
{
	float HPRatio;
	float Padding1;
	float Padding2;
	float Padding3;
};