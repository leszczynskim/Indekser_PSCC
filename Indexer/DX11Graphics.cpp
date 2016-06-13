#include "DX11Graphics.h"
using namespace std;

DX11Graphics::DX11Graphics()
{
}

DX11Graphics::~DX11Graphics()
{
}

HRESULT DX11Graphics::CreateDevice(HWND hwnd, int width, int height)
{
	D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE };
	auto driverTypesCount = ARRAYSIZE(driverTypes);
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
	auto featureLevelsCount = ARRAYSIZE(featureLevels);
	
	HRESULT hr;
	DXGI_MODE_DESC bufferDesc = GetBufferDsc(width, height);
	DXGI_SWAP_CHAIN_DESC swapChainDesc = CreateSwapChain(hwnd, &bufferDesc);
	
	unsigned int creationFlags = 0;
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;

	for (unsigned int driver = 0; driver < driverTypesCount; ++driver)
	{
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		IDXGISwapChain* swapChain = nullptr;
		hr = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[driver], nullptr, creationFlags, featureLevels,
			static_cast<UINT>(featureLevelsCount), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &m_featureLevel, &context);
		m_device.setDeviceObject(shared_ptr<ID3D11Device>(device, Utils::COMRelease));
		m_swapChain.reset(swapChain, Utils::COMRelease);
		m_context.reset(context, Utils::COMRelease);
		if (SUCCEEDED(hr))
		{
			m_driverType = driverTypes[driver];
			return hr;
		}
	}
	return hr;
}

DXGI_MODE_DESC DX11Graphics::GetBufferDsc(int width, int height)
{
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Width = width;
	bufferDesc.Height = height;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	return bufferDesc;
}

DXGI_SWAP_CHAIN_DESC DX11Graphics::CreateSwapChain(HWND hwnd, DXGI_MODE_DESC *buffer)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferDesc = *buffer;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	return swapChainDesc;
}

void DX11Graphics::SetViewPort(SIZE windowSize) const
{
	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(windowSize.cx);
	viewport.Height = static_cast<float>(windowSize.cy);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	m_context->RSSetViewports(1, &viewport);
}
bool DX11Graphics::Initialize(HWND hwnd, int w, int h)
{
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	CreateDevice(hwnd, w, h);
	SIZE s;
	s.cx = w;
	s.cy = h;
	CreateBackBuffers(s);
	SetViewPort(s);
	return true;
}
void DX11Graphics::CreateBackBuffers(SIZE windowSize)
{
	ID3D11Texture2D* bbt;
	HRESULT result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&bbt));
	m_backBufferTexture.reset(bbt, Utils::COMRelease);
	if (FAILED(result))	return;
	m_backBuffer = m_device.CreateRenderTargetView(m_backBufferTexture);
	D3D11_TEXTURE2D_DESC desc;
	m_backBufferTexture->GetDesc(&desc);
	m_depthStencilTexture = m_device.CreateDepthStencilTexture(windowSize);
	m_depthStencilView = m_device.CreateDepthStencilView(m_depthStencilTexture);
	ID3D11RenderTargetView* backBuffer = m_backBuffer.get();
	m_context->OMSetRenderTargets(1, &backBuffer, m_depthStencilView.get());
}