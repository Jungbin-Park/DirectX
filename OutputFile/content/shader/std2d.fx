#ifndef _STD2D
#define _STD2D

#include "value.fx"
#include "func.fx"

// Vertex Shader
struct VTX_IN
{
    float3 vPos     : POSITION;
    float4 vColor   : COLOR;
    float2 vUV      : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor    : COLOR;
    float2 vUV       : TEXCOORD;
};

// 버텍스 쉐이더
VTX_OUT VS_Std2D(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    // LocalSpace -> WorldSpace
    // float3 x float4x4(matrix)
    // float3를 float4로 차수를 맞추어준다.
    // 동차좌표를 1로 설정, 상태 행렬 4행에 들어있는 이동을 적용 받겠다.
    output.vPosition = mul(float4(_in.vPos, 1.f), matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

// 픽셀 쉐이더
float4 PS_Std2D(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    // FlipBook을 사용한다.
    if(g_int_0)
    {
        // _in.vUV : 스프라이트를 참조할 위치를 비율로 환산한 값
        float2 vSpriteUV = g_vec2_0 + (_in.vUV * g_vec2_1);
        vColor = g_AtlasTex.Sample(g_sam_1, vSpriteUV);
    }
    // FlipBook을 사용하지 않는다.
    else
    {
        if (g_btex_0)
        {
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        }
        else
        {
            vColor = float4(1.f, 0.f, 1.f, 1.f);
        }
    }
    
    if (vColor.a == 0.f)
    {
        discard;
    }
    
    return vColor;
}

float4 PS_Std2D_Alphablend(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    if (g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    }
    else
    {
        vColor = float4(1.f, 0.f, 1.f, 1.f);
    }
    
    return vColor;
}


#endif

