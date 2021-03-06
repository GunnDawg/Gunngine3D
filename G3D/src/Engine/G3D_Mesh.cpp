#include "Engine/G3D_Mesh.h"
#include "Engine/G3D_Vertex.h"
#include "Engine/G3D_ConstantBufferTypes.h"

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
			//Front Face
			TexturedVertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f,-1.0f,-1.0f),
			TexturedVertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f,-1.0f),
			TexturedVertex( 1.0f,  1.0f, -1.0f, 1.0f, 0.0f,  1.0f, 1.0f,-1.0f),
			TexturedVertex( 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,  1.0f,-1.0f,-1.0f),

			//Back Face
			TexturedVertex(-1.0f, -1.0f, 1.0f,  1.0f, 1.0f, -1.0f,-1.0f, 1.0f),
			TexturedVertex( 1.0f, -1.0f, 1.0f,  0.0f, 1.0f,  1.0f,-1.0f, 1.0f),
			TexturedVertex( 1.0f,  1.0f, 1.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f),
			TexturedVertex(-1.0f,  1.0f, 1.0f,  1.0f, 0.0f, -1.0f, 1.0f, 1.0f),

			//Top Face
			TexturedVertex(-1.0f,  1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 1.0f,-1.0f),
			TexturedVertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
			TexturedVertex( 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f),
			TexturedVertex( 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,  1.0f, 1.0f,-1.0f),

			//Bottom Face
			TexturedVertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,-1.0f),
			TexturedVertex( 1.0f, -1.0f, -1.0f, 0.0f, 1.0f,  1.0f, -1.0f,-1.0f),
			TexturedVertex( 1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  1.0f, -1.0f, 1.0f),
			TexturedVertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 1.0f),

			//Left Face
			TexturedVertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 1.0f),
			TexturedVertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f,  1.0f, 1.0f),
			TexturedVertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f, -1.0f,  1.0f,-1.0f),
			TexturedVertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,-1.0f),

			//Right Face
			TexturedVertex(1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  1.0f, -1.0f,-1.0f),
			TexturedVertex(1.0f,  1.0f, -1.0f,  0.0f, 0.0f,  1.0f,  1.0f,-1.0f),
			TexturedVertex(1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  1.0f,  1.0f, 1.0f),
			TexturedVertex(1.0f, -1.0f,  1.0f,  1.0f, 1.0f,  1.0f, -1.0f, 1.0f)
		};

		const u16 indices[] =
		{
			//Front Face
			0, 1, 2,
			0, 2, 3,

			//Back Face
			4, 5, 6,
			4, 6, 7,

			//Top Face
			8, 9, 10,
			8, 10, 11,

			//Bottom Face
			12, 13, 14,
			12, 14, 15,

			//Left Face
			16, 17, 18,
			16, 18, 19,

			//Right Face
			20, 21, 22,
			20, 22, 23
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
			MessageBox(nullptr, "Error creating vertex buffer", "Mesh Load Error", MB_OK);
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
			MessageBox(nullptr, "Error creating index buffer", "Mesh Load Error", MB_OK);
			return G3D_ERROR;
		}

		//Create Input Layout
		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u},
			{"TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u},
			{"NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u}
		};

		if (!Shader.Load(ShaderName))
			return G3D_ERROR;

		if (!Texture.Load(TextureName))
			return G3D_ERROR;

		G3D::Core::Renderer.Device->CreateInputLayout(ied, (UINT)std::size(ied), Shader.VertexBlob->GetBufferPointer(), Shader.VertexBlob->GetBufferSize(), &InputLayout);

		//Set position in world space
		worldPos = DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);

		//Create our world space transform constant buffer
		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(D3D11_BUFFER_DESC));
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(CB_VS_TransformConstantBuffer);
		cbd.StructureByteStride = 0u;

		Result = G3D::Core::Renderer.Device->CreateBuffer(&cbd, nullptr, &TransformConstantBuffer);
		if (FAILED(Result))
		{
			MessageBox(nullptr, "Error creating transform constant buffer", "Mesh Load Error", MB_OK);
			return G3D_ERROR;
		}

		//Create our ambient light constant buffer
		D3D11_BUFFER_DESC cbd2;
		ZeroMemory(&cbd2, sizeof(D3D11_BUFFER_DESC));
		cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd2.Usage = D3D11_USAGE_DYNAMIC;
		cbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd2.MiscFlags = 0u;
		cbd2.ByteWidth = sizeof(CB_PS_AmbientLight);
		cbd2.StructureByteStride = 0u;

		Result = G3D::Core::Renderer.Device->CreateBuffer(&cbd2, nullptr, &LightConstantBuffer);
		if (FAILED(Result))
		{
			MessageBox(nullptr, "Error creating ambient light constant buffer", "Mesh Load Error", MB_OK);
			return G3D_ERROR;
		}

		return G3D_OK;
	}

	void Mesh::Update(const AmbientLight& AmbientLightSource)
	{
		HRESULT Result = 0u;

		//@NOTE: We're no longer storing WVP matrix, but instead creating it as a static object in the update function.
		//Nothing else seems to need access to it, so why store it, especially when it's values change every frame
		local_persist DirectX::XMMATRIX WVP;
		local_persist DirectX::XMFLOAT3 Color;
		local_persist float Strength;

		Color = AmbientLightSource.Color;
		Strength = AmbientLightSource.Strength;

		WVP = DirectX::XMMatrixTranspose
		(
			worldPos *
			Game::GameCamera.GetViewMatrix() *
			Game::GameCamera.GetProjectionMatrix()
		);

		const CB_VS_TransformConstantBuffer tcb =
		{
			WVP
		};

		const CB_PS_AmbientLight alcb =
		{
			Color,
			Strength
		};

		//Update our transform buffer data
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		Result = G3D::Core::Renderer.Context->Map(TransformConstantBuffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
		if (FAILED(Result))
		{
			MessageBox(nullptr, "Error mapping subresource to transform constant buffer", "Mesh Update Error", MB_OK);
		}
		CopyMemory(mappedResource.pData, &tcb, sizeof(CB_VS_TransformConstantBuffer));
		G3D::Core::Renderer.Context->Unmap(TransformConstantBuffer, 0u);

		//Update our ambient light buffer data
		Result = G3D::Core::Renderer.Context->Map(LightConstantBuffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mappedResource);
		if (FAILED(Result))
		{
			MessageBox(nullptr, "Error mapping subresource to ambient light constant buffer", "Mesh Update Error", MB_OK);
		}
		CopyMemory(mappedResource.pData, &alcb, sizeof(alcb));
		G3D::Core::Renderer.Context->Unmap(LightConstantBuffer, 0u);
	}

	void Mesh::Draw()
	{
		local_persist const UINT stride = sizeof(TexturedVertex);
		local_persist const UINT offset = 0u;

		Texture.Bind();
		Shader.Bind();
		G3D::Core::Renderer.Context->VSSetConstantBuffers(0u, 1u, &TransformConstantBuffer);
		G3D::Core::Renderer.Context->PSSetConstantBuffers(0u, 1u, &LightConstantBuffer);
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
		Texture.Unload();
		SAFE_RELEASE(TransformConstantBuffer);
		SAFE_RELEASE(LightConstantBuffer);
		SAFE_RELEASE(VertexBuffer);
		SAFE_RELEASE(IndexBuffer);
		SAFE_RELEASE(InputLayout);
	}
}