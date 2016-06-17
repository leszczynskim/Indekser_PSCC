#include "Mesh.h"
#include "DirectUtils.h"


using namespace std;
using namespace DirectX;
const double Mesh::pow216 = pow(2, 16);
Mesh::Mesh(const DeviceHelper& device)
	: m_stride(0), m_indicesCount(0), m_device(device)
{
	m_worldMtx = XMMatrixIdentity(); 
	modelsCount = 1;
	m_vertexBuffer = new std::shared_ptr<ID3D11Buffer>[modelsCount];
	m_indexBuffer = new std::shared_ptr<ID3D11Buffer>[modelsCount];
	m_indicesCount = new unsigned int[modelsCount];
	m_indicesCount[0] = 0;

}

std::string toUtf8Str(const std::wstring & wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

bool Mesh::LoadMesh(std::wstring const &fileName, const DeviceHelper& device, float *sizeX, float *sizeY,float *centerX, float *centerY)
{
	if (fileName == m_path) return false;
	m_device = device;
	if (!boost::filesystem::exists(fileName)) return false;
	gc_tFacetRep fb2;
	string aa = toUtf8Str(fileName);
	if (fb2.Read(toUtf8Str(fileName).c_str()))	return false;
	if (fb2.nfacets * 3 != fb2.nverts)	return false;
	int n = fb2.nverts;
	modelsCount = (int)(n / pow216 + 1);
	m_vertexBuffer = new std::shared_ptr<ID3D11Buffer>[modelsCount];
	m_indexBuffer = new std::shared_ptr<ID3D11Buffer>[modelsCount];
	m_indicesCount = new unsigned int[modelsCount];
	vector<VertexPosNormal> allPositions(n);
	float minX = (float)INT_MAX, maxX = (float)INT_MIN, minY = (float)INT_MAX, maxY = (float)INT_MIN;
	for (int i = 0; i < fb2.nverts; i++)
	{
		float x = fb2.verts[3 * i];
		float y = fb2.verts[3 * i + 1];
		allPositions[i].Pos.x = x;
		allPositions[i].Pos.y = y;
		allPositions[i].Pos.z = fb2.verts[3 * i + 2];
		allPositions[i].Normal.x = fb2.norms[3 * i];
		allPositions[i].Normal.y = fb2.norms[3 * i + 1];
		allPositions[i].Normal.z = fb2.norms[3 * i + 2];	
		if (x < minX) minX = x;
		if (x > maxX) maxX = x;
		if (y < minY) minY = y;
		if (y > maxY) maxY = y;
	}
	n = fb2.nindices;
	int start = 0;
	for (int j = 0; j < modelsCount; j++)
	{
		vector<VertexPosNormal> positions(n / modelsCount);
		for (auto i = 0; i < n / modelsCount; ++i)
		{
			positions[i].Pos = allPositions[start].Pos;
			positions[i].Normal = allPositions[start].Normal;
			start++;
		}
		vector<unsigned short> indices;
		for (auto i = 0; i < n / modelsCount; i++)
			indices.push_back(i);
		m_vertexBuffer[j] = m_device.CreateVertexBuffer(positions);
		m_stride = sizeof(VertexPosNormal);
		m_indexBuffer[j] = m_device.CreateIndexBuffer(indices);
		m_indicesCount[j] = (int)indices.size();
	}
	m_path = fileName;
	*sizeX = maxX - minX;
	*sizeY = maxY - minY;
	*centerX = (maxX + minX) / 2.0f;
	*centerY = (maxY + minY) / 2.0f;
	return true;
}

void Mesh::Render(const shared_ptr<ID3D11DeviceContext>& context) const
{
	if (!m_indicesCount[0])
		return;
	for (int i = 0; i < modelsCount; i++)
	{
		context->IASetIndexBuffer(m_indexBuffer[i].get(), DXGI_FORMAT_R16_UINT, 0);
		auto b = m_vertexBuffer[i].get();
		unsigned int offset = 0;
		context->IASetVertexBuffers(0, 1, &b, &m_stride, &offset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->DrawIndexed(m_indicesCount[i], 0, 0);
	}
}

const D3D11_INPUT_ELEMENT_DESC VertexPosNormal::Layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};
