#include "DeviceHelper.h"
#include "DirectUtils.h"
#include <cassert>
#include <fstream>

using namespace std;



DeviceHelper::DeviceHelper(const shared_ptr<ID3D11Device>& deviceObject)
	: m_deviceObject(deviceObject)
{

}

DeviceHelper::DeviceHelper(const DeviceHelper& right)
	: m_deviceObject(right.m_deviceObject)
{

}

void DeviceHelper::Throw()
{
	string tmp = __FILE__ ":" +  __LINE__;
	throw std::exception(tmp.c_str());
}

vector<BYTE> DeviceHelper::LoadByteCode(const std::wstring& fileName)
{
	size_t byteCodeLength;
	ifstream sIn(fileName, ios::in | ios::binary);
	if (!sIn)
		Throw();
	sIn.seekg(0, ios::end);
	byteCodeLength = sIn.tellg();
	sIn.seekg(0, ios::beg);
	vector<BYTE> byteCode(byteCodeLength);
	if (!sIn.read(reinterpret_cast<char*>(byteCode.data()), byteCodeLength))
		Throw();
	sIn.close();
	return byteCode;
}

shared_ptr<ID3D11VertexShader> DeviceHelper::CreateVertexShader(const vector<BYTE>& byteCode) const
{
	assert(m_deviceObject);
	ID3D11VertexShader* vs;
	auto result = m_deviceObject->CreateVertexShader(byteCode.data(),
													 byteCode.size(), nullptr, &vs);
	shared_ptr<ID3D11VertexShader> vertexShader(vs, Utils::COMRelease);
	if (FAILED(result))
		Throw();
	return vertexShader;
}

shared_ptr<ID3D11PixelShader> DeviceHelper::CreatePixelShader(const vector<BYTE>& byteCode) const
{
	assert(m_deviceObject);
	ID3D11PixelShader* ps;
	auto result = m_deviceObject->CreatePixelShader(byteCode.data(),
													byteCode.size(), nullptr, &ps);
	shared_ptr<ID3D11PixelShader> pixelShader(ps, Utils::COMRelease);
	if (FAILED(result))
		Throw();
	return pixelShader;
}

shared_ptr<ID3D11InputLayout> DeviceHelper::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* layout,
	unsigned int layoutElements,
	const vector<BYTE>& vsByteCode) const
{
	assert(m_deviceObject);
	ID3D11InputLayout* il;
	auto result = m_deviceObject->CreateInputLayout(layout, layoutElements, vsByteCode.data(),
													vsByteCode.size(), &il);
	shared_ptr<ID3D11InputLayout> inputLayout(il, Utils::COMRelease);
	if (FAILED(result))
		Throw();
	return inputLayout;
}

shared_ptr<ID3D11Buffer> DeviceHelper::CreateBuffer(const D3D11_BUFFER_DESC& desc, const void* pData) const
{
	assert(m_deviceObject);
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = pData;
	ID3D11Buffer* b;
	auto result = m_deviceObject->CreateBuffer(&desc, pData?&data:nullptr, &b);
	shared_ptr<ID3D11Buffer> buffer(b, Utils::COMRelease);
	if (FAILED(result))
		Throw();
	return buffer;
}

shared_ptr<ID3D11Buffer> DeviceHelper::_CreateBufferInternal(const void* pData, size_t byteWidth,
	D3D11_BIND_FLAG bindFlags, D3D11_USAGE usage) const
{
	assert(m_deviceObject);
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = usage;
	desc.BindFlags = bindFlags;
	desc.ByteWidth = static_cast<UINT>(byteWidth);
	if ((usage & D3D11_USAGE_DYNAMIC) != 0 || (usage & D3D11_USAGE_STAGING) != 0)
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	return CreateBuffer(desc, pData);
}

shared_ptr<ID3D11Texture2D> DeviceHelper::CreateTexture2D(const D3D11_TEXTURE2D_DESC& desc) const
{
	assert(m_deviceObject);
	ID3D11Texture2D* t;
	auto result = m_deviceObject->CreateTexture2D(&desc, nullptr, &t);
	shared_ptr<ID3D11Texture2D> texture(t, Utils::COMRelease);
	if (FAILED(result))
		Throw();
	return texture;
}

shared_ptr<ID3D11Texture2D> DeviceHelper::CreateDepthStencilTexture(SIZE size) const
{
	assert(m_deviceObject);
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = size.cx;
	desc.Height = size.cy;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	ID3D11Texture2D* dst;
	auto result = m_deviceObject->CreateTexture2D(&desc, nullptr, &dst);
	shared_ptr<ID3D11Texture2D> depthStencilTexture(dst, Utils::COMRelease);
	if (FAILED(result))
		Throw();
	return depthStencilTexture;
}

shared_ptr<ID3D11RenderTargetView> DeviceHelper::CreateRenderTargetView(shared_ptr<ID3D11Texture2D> backBufferTexture) const
{
	assert(m_deviceObject);
	ID3D11RenderTargetView* bb;
	auto result = m_deviceObject->CreateRenderTargetView(backBufferTexture.get(), nullptr, &bb);
	shared_ptr<ID3D11RenderTargetView> backBuffer(bb, Utils::COMRelease);
	if (FAILED(result))
		Throw();
	return backBuffer;
}

shared_ptr<ID3D11DepthStencilView> DeviceHelper::CreateDepthStencilView(shared_ptr<ID3D11Texture2D> depthStencilTexture) const
{
	assert(m_deviceObject);
	ID3D11DepthStencilView* dsv;
	auto result = m_deviceObject->CreateDepthStencilView(depthStencilTexture.get(), nullptr, &dsv);
	shared_ptr<ID3D11DepthStencilView> depthStencilView(dsv, Utils::COMRelease);
	if (FAILED(result))
		Throw();
	return depthStencilView;
}