#include "pch.h"
#include "CDevice.h"

#include "CConstBuffer.h"

CDevice::CDevice()
	: m_hWnd(nullptr)
	, m_arrCB{}
{

}

CDevice::~CDevice()
{
	for (UINT i = 0; i < (UINT)CB_TYPE::END; ++i)
	{
		if (nullptr != m_arrCB[i])
			delete m_arrCB[i];
	}
}

int CDevice::Init(HWND _hWnd, UINT _Width, UINT _Height)
{
	// ������ �ڵ� �� �ػ� �� ����
	m_hWnd = _hWnd;
	m_vResolution.x = (float)_Width;
	m_vResolution.y = (float)_Height;

	// Device, Context ����
	UINT Flag = 0;

#ifdef _DEBUG
	Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
							   , nullptr, Flag
							   , nullptr, 0
							   , D3D11_SDK_VERSION
							   , m_Device.GetAddressOf(), nullptr, m_Context.GetAddressOf())))
	{
		MessageBox(nullptr, L"Device, Context ���� ����", L"��ġ �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// Swap Chain ����
	if (FAILED(CreateSwapChain()))
	{
		MessageBox(nullptr, L"SwapChain ���� ����", L"��ġ �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// RenderTargetView, DepthStencilView ����
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"View ���� ����", L"��ġ �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// Output Merge State (��� ���� �ܰ�)
	m_Context->OMSetRenderTargets(1, m_RTView.GetAddressOf(), m_DSView.Get());


	// ViewPort ����
	// ��½�ų ȭ�� ������ ������ ����
	D3D11_VIEWPORT viewport = {};

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = m_vResolution.x;
	viewport.Height = m_vResolution.y;

	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.f;

	CONTEXT->RSSetViewports(1, &viewport);

	if (FAILED(CreateConstBuffer()))
	{
		MessageBox(nullptr, L"������� ���� ����", L"��ġ �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}


	return S_OK;
}

void CDevice::Clear()
{
	float color[4] = { 0.4f, 0.4f, 0.4f, 1.f };
	m_Context->ClearRenderTargetView(m_RTView.Get(), color);

	m_Context->ClearDepthStencilView(m_DSView.Get(), D3D10_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

int CDevice::CreateSwapChain()
{
	// SwapChain : ȭ�鿡 �׸��� �׸��� ���� ���۸� �����ϰ� ���ۿ� �׷��� �̹����� ȭ�鿡 ����ϴ� ��ü

	DXGI_SWAP_CHAIN_DESC Desc = {};

	Desc.BufferCount                        = 1; // ����� ����
    Desc.BufferDesc.Width                   = (UINT)m_vResolution.x; // ����� �ػ� 
    Desc.BufferDesc.Height                  = (UINT)m_vResolution.y;// ����� �ػ�
    Desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM; // �ȼ� ����
    Desc.BufferDesc.RefreshRate.Denominator = 60;
    Desc.BufferDesc.RefreshRate.Numerator   = 1;
    Desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
    Desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    Desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    Desc.Windowed                           = true;  // â��� ����
    Desc.OutputWindow                       = m_hWnd;// SwapChain ������ �̹����� ��½�ų ������ �ڵ�
    Desc.Flags                              = 0;
    Desc.SampleDesc.Count                   = 1;
    Desc.SampleDesc.Quality                 = 0;
    Desc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;

	// Swap Chain ��ü ����
	ComPtr<IDXGIDevice>		Device = nullptr;
	ComPtr<IDXGIAdapter>	Adapter = nullptr;
	ComPtr<IDXGIFactory>	Factory = nullptr;


	if (FAILED(m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)Device.GetAddressOf())))
		return E_FAIL;

	if(FAILED(Device->GetParent(__uuidof(IDXGIAdapter), (void**)Adapter.GetAddressOf())))
		return E_FAIL;

	if(FAILED(Adapter->GetParent(__uuidof(IDXGIFactory), (void**)Factory.GetAddressOf())))
		return E_FAIL;

	if(FAILED(Factory->CreateSwapChain(m_Device.Get(), &Desc, m_SwapChain.GetAddressOf())))
		return E_FAIL;

	return S_OK;
}

int CDevice::CreateView()
{
	// =======================================================
	// RenderTarget Texture, DepthStencil Texture �� ������Ų��
	// =======================================================
	// Swap Chain�� Back Buffer�� �ּҸ� �޾ƿ´�.
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RTTex.GetAddressOf());	// Ref Count 1����

	// DepthStencil �ؽ��� ����
	D3D11_TEXTURE2D_DESC Desc = {};

	Desc.Width          = (UINT)m_vResolution.x; // DepthStencil �ؽ��Ĵ� ����Ÿ�� �ػ󵵿� �ݵ�� ��ġ�ؾ��Ѵ�.
    Desc.Height         = (UINT)m_vResolution.y;
    Desc.Format         = DXGI_FORMAT_D24_UNORM_S8_UINT; // Depth 24bit , Stencil 8bit
    Desc.ArraySize      = 1;
    Desc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;

    Desc.Usage          = D3D11_USAGE_DEFAULT;   // System Memory ���� ���� ����
    Desc.CPUAccessFlags = 0;

    Desc.MiscFlags      = 0;
    Desc.MipLevels      = 1;   // ��ȭ���� �ػ� �̹��� �߰� ����

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	if (FAILED(m_Device->CreateTexture2D(&Desc, nullptr, m_DSTex.GetAddressOf())))
	{
		MessageBox(nullptr, L"DepthStencil �ؽ��� ���� ����", L"View ���� ����", MB_OK);
		return E_FAIL;
	}

	// =======================================
	// RenderTargetView, DepthStencilView ����
	// =======================================
	if (FAILED(m_Device->CreateRenderTargetView(m_RTTex.Get(), nullptr, m_RTView.GetAddressOf())))
	{
		MessageBox(nullptr, L"RenderTargetView ���� ����", L"View ���� ����", MB_OK);
		return E_FAIL;
	}

	if (FAILED(m_Device->CreateDepthStencilView(m_DSTex.Get(), nullptr, m_DSView.GetAddressOf())))
	{
		MessageBox(nullptr, L"DepthStencilView ���� ����", L"View ���� ����", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateConstBuffer()
{
	CConstBuffer* pCB = nullptr;

	// ������� ����
	pCB = new CConstBuffer;
	if (FAILED(pCB->Create(CB_TYPE::TRANSFORM, sizeof(tTransform))))
	{
		MessageBox(nullptr, L"������� ���� ����", L"�ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}
	m_arrCB[(UINT)CB_TYPE::TRANSFORM] = pCB;





	return S_OK;
}