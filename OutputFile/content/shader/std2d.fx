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
    
    float3 vWorldPos : POSITION;
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
    
    output.vWorldPos = mul(float4(_in.vPos, 1.f), matWorld).xyz;
    
    return output;
}

// 픽셀 쉐이더
float4 PS_Std2D(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    //if (g_int_0 == 1)
    //    return float4(1.f, 0.f, 0.f, 1.f);
    //else
    //    return float4(0.f, 0.f, 1.f, 1.f);
    
    // FlipBook을 사용한다.
    if(UseFlipbook)
    {
        // _in.vUV : 스프라이트를 참조할 위치를 비율로 환산한 값
        float2 BackGroundLeftTop = LeftTopUV - (BackGroundUV - SliceUV) / 2.f;
        float2 vSpriteUV = BackGroundLeftTop + (_in.vUV * BackGroundUV);
        vSpriteUV -= OffsetUV;
                
        if (LeftTopUV.x <= vSpriteUV.x && vSpriteUV.x <= LeftTopUV.x + SliceUV.x
            && LeftTopUV.y <= vSpriteUV.y && vSpriteUV.y <= LeftTopUV.y + SliceUV.y)
        {
            if(g_int_0 == 1)
            {
                vColor = g_AtlasTex.Sample(g_sam_1, vSpriteUV);
                if(vColor.a != 0)
                    vColor += float4(0.8f, 0.8f, 0.8f, 1.f);
            }
                
            else
                vColor = g_AtlasTex.Sample(g_sam_1, vSpriteUV);
        }
        else
        {
            //vColor = float4(1.f, 1.f, 0.f, 1.f);
            discard;
        }
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
    
    // 광원 적용
    tLight Light = (tLight) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalculateLight2D(i, _in.vWorldPos, Light);
    }
    
    vColor.rgb = vColor.rgb * Light.Color.rgb 
               + vColor.rgb * Light.Ambient.rgb;
    
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

float4 PS_Std2D_HUD(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    if (_in.vUV.x > HPRatio)
    {
        discard;
    }
    
    if (g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    }
    else
    {
        vColor = float4(1.f, 0.f, 1.f, 1.f);
    }


    if (vColor.a == 0.f)
    {
        //clip(-1);
        discard;
    }
    
    
    // 광원 적용
    tLight Light = (tLight) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalculateLight2D(i, _in.vWorldPos, Light);
    }
    
    vColor.rgb = vColor.rgb * Light.Color.rgb
               + vColor.rgb * Light.Ambient.rgb;

    
    return vColor;
}

float4 PS_Std2D_HUDMP(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    if (_in.vUV.x > MPRatio)
    {
        discard;
    }
    
    if (g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    }
    else
    {
        vColor = float4(1.f, 0.f, 1.f, 1.f);
    }


    if (vColor.a == 0.f)
    {
        //clip(-1);
        discard;
    }
    
    
    // 광원 적용
    tLight Light = (tLight) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalculateLight2D(i, _in.vWorldPos, Light);
    }
    
    vColor.rgb = vColor.rgb * Light.Color.rgb
               + vColor.rgb * Light.Ambient.rgb;

    
    return vColor;
}

float4 PS_Std2D_BOSSHUD(VTX_OUT _in) : SV_Target
{
    float4 vColor = float4(0.f, 0.f, 0.f, 1.f);
    
    if (_in.vUV.x > BOSSHPRatio)
    {
        discard;
    }
    
    if (g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    }
    else
    {
        vColor = float4(1.f, 0.f, 1.f, 1.f);
    }


    if (vColor.a == 0.f)
    {
        //clip(-1);
        discard;
    }
    
    
    // 광원 적용
    tLight Light = (tLight) 0.f;
    
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        CalculateLight2D(i, _in.vWorldPos, Light);
    }
    
    vColor.rgb = vColor.rgb * Light.Color.rgb
               + vColor.rgb * Light.Ambient.rgb;

    
    return vColor;
}

#endif

