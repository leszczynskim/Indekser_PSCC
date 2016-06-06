#include "Mesh.h"
#include "DirectUtils.h"


using namespace std;
using namespace DirectX;

Mesh::Mesh(shared_ptr<ID3D11Buffer> vb, unsigned int stride, shared_ptr<ID3D11Buffer> ib, unsigned int indicesCount)
	: m_vertexBuffer(vb), m_indexBuffer(ib), m_stride(stride), m_indicesCount(indicesCount)
{
	m_worldMtx = XMMatrixIdentity();
}

Mesh::Mesh(const DeviceHelper& device)
	: m_stride(0), m_indicesCount(0), m_device(device)
{
	m_worldMtx = XMMatrixIdentity();
}

bool Mesh::LoadMesh(std::wstring const &fileName, const DeviceHelper& device)
{
	if (fileName == m_path) return false;
	m_device = device;
	ifstream input;
	input.exceptions(ios::badbit | ios::failbit | ios::eofbit);
	int n, index;
	if (!boost::filesystem::exists(fileName)) return false;
	input.open(fileName);
	input >> n;
	vector<VertexPosNormal> positions(n);
	for (auto i = 0; i < n; ++i)
	{
		input >> positions[i].Pos.x >> positions[i].Pos.y >> positions[i].Pos.z;
		input >> positions[i].Normal.x >> positions[i].Normal.y >> positions[i].Normal.z;
	}
	input >> n;
	vector<unsigned short> indices(n);
	for (auto i = 0; i < n; i++)
	{
		input >> indices[i];
	}
	input.close();
	m_vertexBuffer = m_device.CreateVertexBuffer(positions);
	m_stride = sizeof(VertexPosNormal);
	m_indexBuffer = m_device.CreateIndexBuffer(indices);
	m_indicesCount = indices.size();
	m_path = fileName;
	return true;
}

void Mesh::Render(const shared_ptr<ID3D11DeviceContext>& context) const
{
	if (!m_vertexBuffer || !m_indexBuffer || !m_indicesCount)
		return;
	context->IASetIndexBuffer(m_indexBuffer.get(), DXGI_FORMAT_R16_UINT, 0);
	auto b = m_vertexBuffer.get();
	unsigned int offset = 0;
	context->IASetVertexBuffers(0, 1, &b, &m_stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->DrawIndexed(m_indicesCount, 0, 0);
}


const D3D11_INPUT_ELEMENT_DESC VertexPosNormal::Layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};
