#ifndef _TEST
#define _TEST

cbuffer OBJECT_POS : register(b0)
{
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProj;
};

// Vertex Shader
struct VTX_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};

// 버텍스 쉐이더
VTX_OUT VS_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    // LocalSpace -> WorldSpace
    // float3 x float4x4(matrix)
    // float3를 float4로 차수를 맞추어준다.
    // 동차좌표를 1로 설정, 상태 행렬 4행에 들어있는 이동을 적용 받겠다.
    float3 vWorldPos = mul(float4(_in.vPos, 1.f), matWorld);
    float4 vViewPos = mul(float4(vWorldPos, 1.f), matView);
    float4 vProjPos = mul(vViewPos, matProj);
    
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    
    return output;
}

// 픽셀 쉐이더
float4 PS_Test(VTX_OUT _in) : SV_Target
{
    return _in.vColor;
}


#endif

