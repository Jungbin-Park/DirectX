#pragma once

// DirectX ���� ����� ���
// GPU ����
class CConstBuffer;

class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice)
private:
	HWND								m_hWnd;
	Vec2								m_vResolution;

	ComPtr<ID3D11Device>				m_Device;	// Dx11 ��ü ����, GPU �޸� �Ҵ�
	ComPtr<ID3D11DeviceContext>			m_Context;	// Rendering

	ComPtr<IDXGISwapChain>				m_SwapChain;

	ComPtr<ID3D11Texture2D>				m_RTTex;	// ������
	ComPtr<ID3D11Texture2D>				m_DSTex;	// ���� ����

	ComPtr<ID3D11RenderTargetView>		m_RTView;
	ComPtr<ID3D11DepthStencilView>		m_DSView;

	ComPtr<ID3D11BlendState>			m_BSState;
	ComPtr<ID3D11DepthStencilState>		m_DSSTage;
	ComPtr<ID3D11SamplerState>			m_Sampler;
	ComPtr<ID3D11RasterizerState>		m_RSState;

	CConstBuffer* m_arrCB[(UINT)CB_TYPE::END];

public:
	int Init(HWND _hWnd, UINT _Width, UINT _Height);
	void Clear();
	void Present(){ m_SwapChain->Present(0, 0); }	// �� ���ۿ� ����Ʈ ���� ��ü

private:
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();

public:
	ID3D11Device* GetDevice() { return m_Device.Get(); }
	ID3D11DeviceContext* GetContext() { return m_Context.Get(); }

	CConstBuffer* GetConstBuffer(CB_TYPE _Type) { return m_arrCB[(UINT)_Type]; }
};
