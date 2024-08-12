#ifndef _TILEMAP
#define _TILEMAP

#include "value.fx"

// ===============================
// TileMapShader
// parameter
#define AtlasTex        g_tex_0
#define IsAtlasBind     g_btex_0
#define ImgIdx          g_int_0
#define AtlasMaxRow     g_int_1
#define AtlasMaxCol     g_int_2
#define TileSliceUV     g_vec2_0
#define TileColRow      g_vec2_1
// ===============================

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_TileMap(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // TileMap 이 우측 하단으로 확장되도록 하기 위해서 
    // Local RectMesh 의 좌표를 수정한 후 상태행렬을 곱하게 한다.
    _in.vPos.x += 0.5f;
    _in.vPos.y -= 0.5f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), matWVP);
    output.vUV = _in.vUV * TileColRow ;
    
    return output;
}


float4 PS_TileMap(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    if (IsAtlasBind)
    {
        int row = ImgIdx / AtlasMaxCol;
        int col = ImgIdx % AtlasMaxCol;
        
        float2 vLeftTopUV = float2(col, row) * TileSliceUV;
        
        float2 vUV = vLeftTopUV + frac(_in.vUV) * TileSliceUV;
        vOutColor = AtlasTex.Sample(g_sam_1, vUV);
    }
    else
    {
        vOutColor = float4(1.f, 0.f, 1.f, 1.f);
    }
    
    return vOutColor;
}




#endif