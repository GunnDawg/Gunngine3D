#include "Engine/G3D_Mesh.h"
#include "Engine/G3D_Vertex.h"

namespace G3D
{
	bool Mesh::Load()
	{
		HRESULT Result = 0u;

		const BasicVertex vertices[] =
		{
			DirectX::XMFLOAT3(-0.5f, -0.5f, 1.0f),
			DirectX::XMFLOAT3(-0.5f,  0.5f, 1.0f),
			DirectX::XMFLOAT3( 0.5f,  0.5f, 1.0f),
			DirectX::XMFLOAT3( 0.5f, -0.5f, 1.0f),
		};

		const u16 indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		IndexCount = (UINT)std::size(indices);

		//Create Vertex Buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = sizeof(vertices);
		bd.StructureByteStride = sizeof(BasicVertex);

		D3D11_SUBRESOURCE_DATA srd;
		ZeroMemory(&srd, sizeof(D3D11_SUBRESOURCE_DATA));
		srd.pSysMem = vertices;

		Result = G3D::Core::Renderer.Device->CreateBuffer(&bd, &srd, &VertexBuffer);
		if (FAILED(Result))
		{
			//TODO: Error Checking.
			return false;
		}

		//Create Index Buffer
		D3D11_BUFFER_DESC ibd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.CPUAccessFlags = 0u;
		ibd.MiscFlags = 0u;
		ibd.ByteWidth = sizeof(indices);
		ibd.StructureByteStride = sizeof(BasicVertex);

		D3D11_SUBRESOURCE_DATA isrd;
		ZeroMemory(&isrd, sizeof(D3D11_SUBRESOURCE_DATA));
		isrd.pSysMem = indices;

		Result = G3D::Core::Renderer.Device->CreateBuffer(&ibd, &isrd, &IndexBuffer);
		if (FAILED(Result))
		{
			//TODO: Error Checking.
			return false;
		}

		//Create Input Layout
		ZeroMemory(&InputLayout, sizeof(ID3D11InputLayout));
		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u},
			{"TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u}
		};

		if (!Shader.Load())
		{
			Shader.Unload();
			return false;
		}

		G3D::Core::Renderer.Device->CreateInputLayout(ied, (UINT)std::size(ied), Shader.VertexBlob->GetBufferPointer(), Shader.VertexBlob->GetBufferSize(), &InputLayout);

		IsUsingDefault = true;

		return true;
	}

	bool Mesh::Load(const char* shaderName)
	{
		HRESULT Result = 0u;

		const BasicVertex vertices[] =
		{
			DirectX::XMFLOAT3(-0.5f, -0.5f, 1.0f),
			DirectX::XMFLOAT3(-0.5f,  0.5f, 1.0f),
			DirectX::XMFLOAT3(0.5f,  0.5f, 1.0f),
			DirectX::XMFLOAT3(0.5f, -0.5f, 1.0f),
		};

		const u16 indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		IndexCount = (UINT)std::size(indices);

		//Create Vertex Buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = sizeof(vertices);
		bd.StructureByteStride = sizeof(BasicVertex);

		D3D11_SUBRESOURCE_DATA srd;
		ZeroMemory(&srd, sizeof(D3D11_SUBRESOURCE_DATA));
		srd.pSysMem = vertices;

		Result = G3D::Core::Renderer.Device->CreateBuffer(&bd, &srd, &VertexBuffer);
		if (FAILED(Result))
		{
			//TODO: Error Checking.
			return false;
		}

		//Create Index Buffer
		D3D11_BUFFER_DESC ibd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.CPUAccessFlags = 0u;
		ibd.MiscFlags = 0u;
		ibd.ByteWidth = sizeof(indices);
		ibd.StructureByteStride = sizeof(BasicVertex);

		D3D11_SUBRESOURCE_DATA isrd;
		ZeroMemory(&isrd, sizeof(D3D11_SUBRESOURCE_DATA));
		isrd.pSysMem = indices;

		Result = G3D::Core::Renderer.Device->CreateBuffer(&ibd, &isrd, &IndexBuffer);
		if (FAILED(Result))
		{
			//TODO: Error Checking.
			return false;
		}

		//Create Input Layout
		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u}
		};

		if (!Shader.Load(shaderName))
		{
			//TODO: Error Checking.
			return false;
		}

		G3D::Core::Renderer.Device->CreateInputLayout(ied, (UINT)std::size(ied), Shader.VertexBlob->GetBufferPointer(), Shader.VertexBlob->GetBufferSize(), &InputLayout);

		return true;
	}

	void Mesh::Draw()
	{
		local_persist const UINT stride = sizeof(BasicVertex);
		local_persist const UINT offset = 0u;

		Shader.Bind();
		G3D::Core::Renderer.Context->IASetVertexBuffers(0u, 1u, &VertexBuffer, &stride, &offset);
		G3D::Core::Renderer.Context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R16_UINT, 0u);
		G3D::Core::Renderer.Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		G3D::Core::Renderer.Context->IASetInputLayout(InputLayout);

		G3D::Core::Renderer.Context->DrawIndexed(IndexCount, 0u, 0u);
	}

	void Mesh::SwapShader(const char* shaderName)
	{
		Shader.Unload();
		Shader.Load(shaderName);
	}

	void Mesh::Unload()
	{
		Shader.Unload();
		SAFE_RELEASE(VertexBuffer);
		SAFE_RELEASE(IndexBuffer);
		SAFE_RELEASE(InputLayout);
	}
}