#ifndef __PHONG_EFFECT_H_
#define __PHONG_EFFECT_H_

#include <d3d11.h>
#include "Devicehelper.h"
#include "ConstantBuffer.h"
#include <memory>
#include <string>
#include "Mesh.h"


class PhongEffect
{
public:
	PhongEffect(DeviceHelper& device, std::shared_ptr<ID3D11InputLayout>& layout,
		std::shared_ptr<ID3D11DeviceContext> context = nullptr);

	void SetLightPosBuffer(const std::shared_ptr<ConstantBuffer<DirectX::XMFLOAT4, 2>>& lightPos);
	void SetSurfaceColorBuffer(const std::shared_ptr<ConstantBuffer<DirectX::XMFLOAT4>>& surfaceColor);
	void SetWorldMtxBuffer(const std::shared_ptr<CBMatrix>& world);
	void SetViewMtxBuffer(const std::shared_ptr<CBMatrix>& view);
	void SetProjMtxBuffer(const std::shared_ptr<CBMatrix>& proj);

	void Begin(std::shared_ptr<ID3D11DeviceContext> context = nullptr);
	void End();


	void Initialize(DeviceHelper& device, std::shared_ptr<ID3D11InputLayout>& layout,
		const std::wstring& shaderName);
protected:
	void SetVertexShaderData();
	void SetPixelShaderData();
	std::shared_ptr<CBMatrix> m_worldCB;
	std::shared_ptr<CBMatrix> m_viewCB;
	std::shared_ptr<CBMatrix> m_projCB;
	std::shared_ptr<ID3D11DeviceContext> m_context;
private:
	std::shared_ptr<ID3D11VertexShader> m_vs;
	std::shared_ptr<ID3D11PixelShader> m_ps;
	std::shared_ptr<ID3D11InputLayout> m_layout;
	static const std::wstring ShaderName;

	std::shared_ptr<ConstantBuffer<DirectX::XMFLOAT4, 2>> m_lightPosCB;
	std::shared_ptr<ConstantBuffer<DirectX::XMFLOAT4>> m_surfaceColorCB;
};

#endif __PHONG_EFFECT_H_
