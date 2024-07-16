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