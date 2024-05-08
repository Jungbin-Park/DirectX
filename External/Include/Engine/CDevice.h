#pragma once

// DirectX 관련 기능을 담당
// GPU 제어

class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice)
private:
	HWND						m_hWnd;
	Vec2						m_vResolution;

	ID3D11Device*				m_Device;	// Dx11 객체 생성, GPU 메모리 할당
	ID3D11DeviceContext*		m_Context;	// Rendering

	IDXGISwapChain*				m_SwapChain;

	ID3D11Texture2D*			m_RTTex;	// 렌더링
	ID3D11Texture2D*			m_DSTex;	// 깊이 정보

	ID3D11RenderTargetView*		m_RTView;
	ID3D11DepthStencilView*		m_DSView;

	ID3D11BlendState*			m_BSState;
	ID3D11DepthStencilState*	m_DSSTage;
	ID3D11SamplerState*			m_Sampler;
	ID3D11RasterizerState*		m_RSState;

public:
	int Init(HWND _hWnd, UINT _Width, UINT _Height);
	void Clear();
	void Present(){ m_SwapChain->Present(0, 0); }	// 백 버퍼와 프론트 버퍼 교체

private:
	int CreateSwapChain();
	int CreateView();

public:
	ID3D11Device* GetDevice() { return m_Device; }
	ID3D11DeviceContext* GetContext() { return m_Context; }
};

