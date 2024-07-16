#pragma once

// 정점(Vertex) 구조체
struct Vtx
{
	Vec3	vPos;	// 좌표
	Vec4	vColor;	// 색상
	Vec2	vUV;
};


// 상수 버퍼 연동 구조체
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
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