#include "stdafx.h"
#include <d3dx11.h>
#include <D3D11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "framework/DirectUtils.h"
#include "framework/DeviceHelper.h"
#include <memory>

using namespace DirectX;
class DX11Graphics
{
public:
	DX11Graphics();
	HWND g_hWnd = NULL;

	DeviceHelper m_device;
	std::shared_ptr<ID3D11DeviceContext> m_context;
	std::shared_ptr<IDXGISwapChain> m_swapChain;
	std::shared_ptr<ID3D11Texture2D> m_backBufferTexture;
	std::shared_ptr<ID3D11RenderTargetView> m_backBuffer;
	std::shared_ptr<ID3D11Texture2D> m_depthStencilTexture;
	std::shared_ptr<ID3D11DepthStencilView> m_depthStencilView;
	D3D_DRIVER_TYPE m_driverType;
	D3D_FEATURE_LEVEL m_featureLevel;

	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	int colormodr = 1;
	int colormodg = 1;
	int colormodb = 1;

	virtual ~DX11Graphics();
	bool Initialize(HWND hwnd, int w, int h);

	void CreateBackBuffers(SIZE windowSize);

	virtual bool Init() = 0;
	virtual bool Render() = 0;
	virtual void DrawScene() = 0;
	virtual void ReleaseObjects() = 0;

private:
	DXGI_MODE_DESC GetBufferDsc(int width, int height);
	DXGI_SWAP_CHAIN_DESC CreateSwapChain(HWND hwnd, DXGI_MODE_DESC *buffer);
	HRESULT CreateDevice(HWND hwnd, int width, int height);
	void SetViewPort(SIZE windowSize) const;
};