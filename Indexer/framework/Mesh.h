#ifndef __MESH_H_
#define __MESH_H_

#include <memory>
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <fstream>
#include "Devicehelper.h"
#include <boost/filesystem.hpp>
#include <d3d11.h>
#include "api.h"

class Mesh
{
public:
	Mesh(const DeviceHelper & device);
	Mesh() {};

	const DirectX::XMMATRIX& getWorldMatrix() const { return m_worldMtx; }
	void setWorldMatrix(const DirectX::XMMATRIX& mtx) { m_worldMtx = mtx; }
	bool LoadMesh(std::wstring const & fileName, const DeviceHelper & device, float *sizeX, float *sizeY, float *centerX,float *centerY);
	void Render(const std::shared_ptr<ID3D11DeviceContext>& context) const;
private:
	std::shared_ptr<ID3D11Buffer>* m_vertexBuffer;
	std::shared_ptr<ID3D11Buffer>* m_indexBuffer;
	unsigned int m_stride;
	unsigned int* m_indicesCount;
	static const double pow216;
	DirectX::XMMATRIX m_worldMtx;
	DeviceHelper m_device;
	std::wstring m_path;
	int modelsCount;
};


struct VertexPosNormal
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT3 Normal;
	static const unsigned int LayoutElements = 2;
	static const D3D11_INPUT_ELEMENT_DESC Layout[LayoutElements];
};

#endif __MESH_H_
