#pragma once
#include "CAsset.h"

class CTexture :
    public CAsset
{
private:
    ScratchImage                        m_Image;    // 파일을 시스템 메모리로 불러오는 역할
    ComPtr<ID3D11Texture2D>				m_Tex2D;

    ComPtr<ID3D11RenderTargetView>      m_RTV;
    ComPtr<ID3D11DepthStencilView>      m_DSV;
    ComPtr<ID3D11ShaderResourceView>    m_SRV;
    ComPtr<ID3D11UnorderedAccessView>   m_UAV;

    D3D11_TEXTURE2D_DESC                m_Desc;

public:
    ComPtr<ID3D11Texture2D>             GetTex2D() { return m_Tex2D; }
    ComPtr<ID3D11RenderTargetView>      GetRTV() { return m_RTV; }
    ComPtr<ID3D11DepthStencilView>      GetDSV() { return m_DSV; }
    ComPtr<ID3D11ShaderResourceView>    GetSRV() { return m_SRV; }
    ComPtr<ID3D11UnorderedAccessView>   GetUAV() { return m_UAV; }

public:
    // _Flags : D3D11_BIND_FLAG 
    int Create(UINT _Width, UINT _Height, DXGI_FORMAT _PixelFormat, UINT _Flags, D3D11_USAGE _Usage = D3D11_USAGE_DEFAULT);
    int Create(ComPtr<ID3D11Texture2D> _Tex2D);

    void Binding(UINT _RegisterNum);

    virtual int Load(const wstring& _FilePath) override;
    virtual int Save(const wstring& _FilePath) override;

public:
    CLONE_DISABLE(CTexture);
    CTexture();
    ~CTexture();

};

