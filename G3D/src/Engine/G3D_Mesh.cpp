#include "Engine/G3D_Mesh.h"
#include "Engine/G3D_Vertex.h"
#include "Engine/G3D_ConstantBuffer.h"

namespace G3D
{
	bool Mesh::Load()
	{
		return Load("Default", "Default", DirectX::XMFLOAT3{ 0.0f, 0.0f, 0.0f });
	}

	bool Mesh::Load(const char* TextureName, const char* ShaderName, DirectX::XMFLOAT3 Position)
	{
		HRESULT Result = 0u;

		const TexturedVertex vertices[] =
		{
			//Back Face
			TexturedVertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f),
			TexturedVertex( 0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
			TexturedVertex(-0.5f,  0.5f, -0.5f, 1.0f, 0.0f),
			TexturedVertex( 0.5f,  0.5f, -0.5f, 1.0f, 1.0f),

			//Front Face
			TexturedVertex(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f),
			TexturedVertex( 0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
			TexturedVertex(-0.5f,  0.5f, 0.5f, 1.0f, 0.0f),
			TexturedVertex( 0.5f,  0.5f, 0.5f, 1.0f, 1.0f)
		};

		const u16 indices[] =
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
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
		bd.StructureByteStride = sizeof(TexturedVertex);

		D3D11_SUBRESOURCE_DATA srd;
		ZeroMemory(&srd, sizeof(D3D11_SUBRESOURCE_DATA));
		srd.pSysMem = vertices;

		Result = G3D::Core::Renderer.Device->CreateBuffer(&bd, &srd, &VertexBuffer);
		if (FAILED(Result))
		{
			//TODO: Error Handling.
			return G3D_ERROR;
		}

		//Create Index Buffer
		D3D11_BUFFER_DESC ibd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.CPUAccessFlags = 0u;
		ibd.MiscFlags = 0u;
		ibd.ByteWidth = sizeof(indices);
		ibd.StructureByteStride = sizeof(TexturedVertex);

		D3D11_SUBRESOURCE_DATA isrd;
		ZeroMemory(&isrd, sizeof(D3D11_SUBRESOURCE_DATA));
		isrd.pSysMem = indices;

		Result = G3D::Core::Renderer.Device->CreateBuffer(&ibd, &isrd, &IndexBuffer);
		if (FAILED(Result))
		{
			//TODO: Error Handling.
			return G3D_ERROR;
		}

		//Create Input Layout
		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u},
			{"TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u}
		};

		if (!Shader.Load(ShaderName))
		{
			//TODO: Error Handling.
			return G3D_ERROR;
		}

		if (!Texture.Load(TextureName))
		{
			//TODO: Error Handling.
			return G3D_ERROR;
		}

		G3D::Core::Renderer.Device->CreateInputLayout(ied, (UINT)std::size(ied), Shader.VertexBlob->GetBufferPointer(), Shader.VertexBlob->GetBufferSize(), &InputLayout);

		worldPos = DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);

		return G3D_OK;
	}

	void Mesh::Update()
	{
		HRESULT Result = 0u;

		WVP = DirectX::XMMatrixTranspose(
			worldPos *
			Game::GameCamera.GetViewMatrix()*
			Game::GameCamera.GetProjectionMatrix()
		);

		const CameraConstantBuffer cb =
		{
			WVP
		};

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(D3D11_BUFFER_DESC));
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(cb);
		cbd.StructureByteStride = 0u;
		D3D11_SUBRESOURCE_DATA csd;
		csd.pSysMem = &cb;
		Result = G3D::Core::Renderer.Device->CreateBuffer(&cbd, &csd, &mConstantBuffer);
		if (FAILED(Result))
		{
			//TODO: Error Handling;
		}
	}

	void Mesh::Draw()
	{
		local_persist const UINT stride = sizeof(TexturedVertex);
		local_persist const UINT offset = 0u;

		Texture.Bind();
		Shader.Bind();
		G3D::Core::Renderer.Context->VSSetConstantBuffers(0u, 1u, &mConstantBuffer);
		G3D::Core::Renderer.Context->IASetVertexBuffers(0u, 1u, &VertexBuffer, &stride, &offset);
		G3D::Core::Renderer.Context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R16_UINT, 0u);
		G3D::Core::Renderer.Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		G3D::Core::Renderer.Context->IASetInputLayout(InputLayout);

		G3D::Core::Renderer.Context->DrawIndexed(IndexCount, 0u, 0u);

		SAFE_RELEASE(mConstantBuffer);
	}

	void Mesh::SwapShader(const char* shaderName)
	{
		Shader.Unload();
		Shader.Load(shaderName);
	}

	void Mesh::Unload()
	{
		Shader.Unload();
		Texture.Unload();
		//SAFE_RELEASE(mConstantBuffer);
		SAFE_RELEASE(VertexBuffer);
		SAFE_RELEASE(IndexBuffer);
		SAFE_RELEASE(InputLayout);
	}
}