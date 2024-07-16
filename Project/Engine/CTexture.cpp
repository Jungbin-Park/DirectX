#include "pch.h"
#include "CTexture.h"

#include "CDevice.h"


CTexture::CTexture()
	: CAsset(ASSET_TYPE::TEXTURE)
	, m_Desc{}
{
}

CTexture::~CTexture()
{
}

void CTexture::Binding(UINT _RegisterNum)
{
	CONTEXT->VSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
	CONTEXT->HSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
	CONTEXT->DSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
	CONTEXT->GSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
	CONTEXT->PSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
}

void CTexture::Clear(UINT _RegisterNum)
{
	ID3D11ShaderResourceView* pSRV = nullptr;
	CONTEXT->VSSetShaderResources(_RegisterNum, 1, &pSRV);
	CONTEXT->HSSetShaderResources(_RegisterNum, 1, &pSRV);
	CONTEXT->DSSetShaderResources(_RegisterNum, 1, &pSRV);
	CONTEXT->GSSetShaderResources(_RegisterNum, 1, &pSRV);
	CONTEXT->PSSetShaderResources(_RegisterNum, 1, &pSRV);
}

int CTexture::Load(const wstring& _FilePath)
{
	path filepath = _FilePath;
	path extension = filepath.extension();

	HRESULT hr = S_OK;

	// *.dds
	if (extension == L".dds" || extension == L".DDS")
	{
		hr = LoadFromDDSFile(_FilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_Image);
	}
	
	// *.tga
	else if (extension == L".tga" || extension == L".TGA")
	{
		hr = LoadFromTGAFile(_FilePath.c_str(), nullptr, m_Image);
	}

	// Window Image Component (*.bmp, *.png, *.jpg, *.jpeg)
	else if (extension == L".bmp" || extension == L".png" || extension == L".jpg" || extension == L".jpeg"
		|| extension == L".BMP" || extension == L".PNG" || extension == L".JPG" || extension == L".JPEG")
	{
		hr = LoadFromWICFile(_FilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_Image);
	}
	
	// 알 수 없는 포맷인 경우
	else
	{
		return E_FAIL;
	}

	// 로딩이 실패했다면
	if (FAILED(hr))
	{
		errno_t ErrNum = GetLastError();
		wchar_t szBuff[255] = {};
		wsprintf(szBuff, L"Error Number : %d", ErrNum);
		MessageBox(nullptr, szBuff, L"텍스쳐 로딩 실패", MB_OK);
		return E_FAIL;
	}

	// SystemMem(ScratchImage) -> GPU(Texture2D)
	CreateShaderResourceView(DEVICE
						   , m_Image.GetImages()
						   , m_Image.GetImageCount()
						   , m_Image.GetMetadata()
						   , m_SRV.GetAddressOf());

	// 원본 리소스 반환
	m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());

	// 반환 받은 원본에서 Desc 정보를 받아옴
	m_Tex2D->GetDesc(&m_Desc);

	return S_OK;
}

int CTexture::Save(const wstring& _FilePath)
{
	return 0;
}

int CTexture::Create(UINT _Width, UINT _Height, DXGI_FORMAT _PixelFormat, UINT _Flags, D3D11_USAGE _Usage)
{
	m_Desc.Width = _Width; // DepthStencil 텍스쳐는 렌더타겟 해상도와 반드시 일치해야한다.
	m_Desc.Height = _Height;
	m_Desc.Format = _PixelFormat; // Depth 24bit , Stencil 8bit
	m_Desc.ArraySize = 1;
	m_Desc.BindFlags = _Flags;

	m_Desc.Usage = _Usage;   // System Memory 와의 연계 설정

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == _Usage)
	{
		m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_Desc.CPUAccessFlags = 0;
	}
	
	m_Desc.MiscFlags = 0;
	m_Desc.MipLevels = 1;   // 열화버전 해상도 이미지 추가 생성

	m_Desc.SampleDesc.Count = 1;
	m_Desc.SampleDesc.Quality = 0;

	if (FAILED(DEVICE->CreateTexture2D(&m_Desc, nullptr, m_Tex2D.GetAddressOf())))
	{
		MessageBox(nullptr, L"DepthStencil 텍스쳐 생성 실패", L"View 생성 실패", MB_OK);
		return E_FAIL;
	}

	// View 생성
	if (m_Desc.BindFlags & D3D11_BIND_RENDER_TARGET)
	{
		DEVICE->CreateRenderTargetView(m_Tex2D.Get(), nullptr, m_RTV.GetAddressOf());
	}

	if (m_Desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		DEVICE->CreateDepthStencilView(m_Tex2D.Get(), nullptr, m_DSV.GetAddressOf());
	}

	if (m_Desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
	{
		DEVICE->CreateShaderResourceView(m_Tex2D.Get(), nullptr, m_SRV.GetAddressOf());
	}

	if (m_Desc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
	{
		DEVICE->CreateUnorderedAccessView(m_Tex2D.Get(), nullptr, m_UAV.GetAddressOf());
	}

	return S_OK;
}

int CTexture::Create(ComPtr<ID3D11Texture2D> _Tex2D)
{
	m_Tex2D = _Tex2D;
	m_Tex2D->GetDesc(&m_Desc);

	// View 생성
	if (m_Desc.BindFlags & D3D11_BIND_RENDER_TARGET)
	{
		DEVICE->CreateRenderTargetView(m_Tex2D.Get(), nullptr, m_RTV.GetAddressOf());
	}

	if (m_Desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		DEVICE->CreateDepthStencilView(m_Tex2D.Get(), nullptr, m_DSV.GetAddressOf());
	}

	if (m_Desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
	{
		DEVICE->CreateShaderResourceView(m_Tex2D.Get(), nullptr, m_SRV.GetAddressOf());
	}

	if (m_Desc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
	{
		DEVICE->CreateUnorderedAccessView(m_Tex2D.Get(), nullptr, m_UAV.GetAddressOf());
	}

	return S_OK;
}




