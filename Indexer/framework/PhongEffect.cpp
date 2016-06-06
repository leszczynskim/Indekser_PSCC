#include "PhongEffect.h"

using namespace std;

using namespace DirectX;

const wstring PhongEffect::ShaderName = L"phong";

PhongEffect::PhongEffect(DeviceHelper& device, shared_ptr<ID3D11InputLayout>& layout,
						 shared_ptr<ID3D11DeviceContext> context /* = nullptr */) : m_context(context)
{
	Initialize(device, layout, ShaderName);
}

void PhongEffect::SetLightPosBuffer(const shared_ptr<ConstantBuffer<XMFLOAT4, 2>>& lightPos)
{
	if (lightPos != nullptr)
		m_lightPosCB = lightPos;
}

void PhongEffect::SetSurfaceColorBuffer(const shared_ptr<ConstantBuffer<XMFLOAT4>>& surfaceColor)
{
	if (surfaceColor != nullptr)
		m_surfaceColorCB = surfaceColor;
}

void PhongEffect::SetVertexShaderData()
{
	ID3D11Buffer* vsb[4] = { m_worldCB->getBufferObject().get(), m_viewCB->getBufferObject().get(),
							 m_projCB->getBufferObject().get(), m_lightPosCB->getBufferObject().get() };
	m_context->VSSetConstantBuffers(0, 4, vsb);
}

void PhongEffect::SetPixelShaderData()
{
	ID3D11Buffer* psb[1] = { m_surfaceColorCB->getBufferObject().get() };
	m_context->PSSetConstantBuffers(0, 1, psb);
}


void PhongEffect::SetWorldMtxBuffer(const shared_ptr<CBMatrix>& world)
{
	if (world != nullptr)
		m_worldCB = world;
}

void PhongEffect::SetViewMtxBuffer(const shared_ptr<CBMatrix>& view)
{
	if (view != nullptr)
		m_viewCB = view;
}

void PhongEffect::SetProjMtxBuffer(const shared_ptr<CBMatrix>& proj)
{
	if (proj != nullptr)
		m_projCB = proj;
}


void PhongEffect::Begin(shared_ptr<ID3D11DeviceContext> context /* = nullptr */)
{
	if (context != nullptr && context != m_context)
		m_context = context;
	if (m_context == nullptr)
		return;
	m_context->VSSetShader(m_vs.get(), nullptr, 0);
	m_context->PSSetShader(m_ps.get(), nullptr, 0);
	m_context->IASetInputLayout(m_layout.get());
	SetVertexShaderData();
	SetPixelShaderData();
}

void PhongEffect::End()
{

}

void PhongEffect::Initialize(DeviceHelper& device, shared_ptr<ID3D11InputLayout>& layout, const wstring& shaderFile)
{
	auto vsByteCode = device.LoadByteCode(shaderFile + L"VS.cso");
	auto psByteCode = device.LoadByteCode(shaderFile + L"PS.cso");
	m_vs = device.CreateVertexShader(vsByteCode);
	m_ps = device.CreatePixelShader(psByteCode);

	if (m_layout == nullptr)
	{
		m_layout = device.CreateInputLayout<VertexPosNormal>(vsByteCode);
		layout = m_layout;
	}
	else
		m_layout = layout;
}