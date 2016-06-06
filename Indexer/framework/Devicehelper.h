#ifndef __DEVICE_HELPER_H_
#define __DEVICE_HELPER_H_

#include <memory>
#include <d3d11.h>
#include <string>
#include <vector>

	class DeviceHelper
	{
	public:
		DeviceHelper(const std::shared_ptr<ID3D11Device>& deviceObject = nullptr);
		DeviceHelper(const DeviceHelper & right);
		static void Throw();
		const std::shared_ptr<ID3D11Device>& getDeviceObject() const { return m_deviceObject; }
		void setDeviceObject(const std::shared_ptr<ID3D11Device>& deviceObject) { m_deviceObject = deviceObject; }
		static std::vector<BYTE> LoadByteCode(const std::wstring& fileName);
		std::shared_ptr<ID3D11VertexShader> CreateVertexShader(const std::vector<BYTE>& byteCode) const;
		std::shared_ptr<ID3D11PixelShader> CreatePixelShader(const std::vector<BYTE>& byteCode) const;
		std::shared_ptr<ID3D11InputLayout> CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* layout,
															 unsigned int layoutElements,
															 const std::vector<BYTE>& vsByteCode) const;

		template<typename T>
		std::shared_ptr<ID3D11InputLayout> CreateInputLayout(const std::vector<BYTE>& vsByteCode)
		{
			return CreateInputLayout(T::Layout, T::LayoutElements, vsByteCode);
		}

		template<typename T>
		std::shared_ptr<ID3D11Buffer> CreateVertexBuffer(const std::vector<T>& vertices)
		{
			return _CreateBufferInternal(reinterpret_cast<const void*>(vertices.data()), sizeof(T) * vertices.size(),
				D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT);
		}

		std::shared_ptr<ID3D11Buffer> CreateIndexBuffer(const std::vector<unsigned short> indices) const
		{
			return _CreateBufferInternal(reinterpret_cast<const void*>(indices.data()),
				sizeof(unsigned short) * indices.size(), D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_DEFAULT);
		}

		std::shared_ptr<ID3D11Buffer> CreateBuffer(const D3D11_BUFFER_DESC& desc, const void* pData = nullptr) const;
		std::shared_ptr<ID3D11Texture2D> CreateTexture2D(const D3D11_TEXTURE2D_DESC& desc) const;
		std::shared_ptr<ID3D11Texture2D> CreateDepthStencilTexture(SIZE size) const;
		std::shared_ptr<ID3D11RenderTargetView> CreateRenderTargetView(
													std::shared_ptr<ID3D11Texture2D> backBufferTexture) const;
		std::shared_ptr<ID3D11DepthStencilView> CreateDepthStencilView(
																std::shared_ptr<ID3D11Texture2D> depthStencilTexture) const;

	private:
		std::shared_ptr<ID3D11Device> m_deviceObject;

		std::shared_ptr<ID3D11Buffer> _CreateBufferInternal(const void* pData, size_t byteWidth,
			D3D11_BIND_FLAG bindFlags, D3D11_USAGE usage) const;
	};


#endif __DEVICE_HELPER_H_
