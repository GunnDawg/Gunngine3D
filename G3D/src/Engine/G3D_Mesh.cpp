#include "Engine/G3D_Mesh.h"
#include "Engine/G3D_Vertex.h"

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

	//Create Vertex Shader
	Result = D3DReadFileToBlob(L"res/shaders/BasicVertexShader.cso", &VertexBlob);
	if (FAILED(Result))
	{
		//TODO: Error Checking.
		return false;
	}

	Result = G3D::Core::Renderer.Device->CreateVertexShader(VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), nullptr, &VertexShader);
	if (FAILED(Result))
	{
		//TODO: Error Checking.
		return false;
	}

	//Create Pixel Shader
	Result = D3DReadFileToBlob(L"res/shaders/BasicPixelShader.cso", &PixelBlob);
	if (FAILED(Result))
	{
		//TODO: Error Checking.
		return false;
	}

	Result = G3D::Core::Renderer.Device->CreatePixelShader(PixelBlob->GetBufferPointer(), PixelBlob->GetBufferSize(), nullptr, &PixelShader);
	if (FAILED(Result))
	{
		//TODO: Error Checking.
		return false;
	}

	//Create Input Layout
	ZeroMemory(&InputLayout, sizeof(ID3D11InputLayout));
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u}
	};

	G3D::Core::Renderer.Device->CreateInputLayout(ied, (UINT)std::size(ied), VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), &InputLayout);

	return true;
}

void Mesh::Draw()
{
	const UINT stride = sizeof(BasicVertex);
	const UINT offset = 0u;

	G3D::Core::Renderer.Context->VSSetShader(VertexShader, 0u, 0u);
	G3D::Core::Renderer.Context->PSSetShader(PixelShader, 0u, 0u);
	G3D::Core::Renderer.Context->IASetVertexBuffers(0u, 1u, &VertexBuffer, &stride, &offset);
	G3D::Core::Renderer.Context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R16_UINT, 0u);
	G3D::Core::Renderer.Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	G3D::Core::Renderer.Context->IASetInputLayout(InputLayout);

	G3D::Core::Renderer.Context->DrawIndexed(IndexCount, 0u, 0u);
}

void Mesh::Unload()
{
	SAFE_RELEASE(VertexBuffer);
	SAFE_RELEASE(IndexBuffer);
	SAFE_RELEASE(VertexShader);
	SAFE_RELEASE(PixelShader);
	SAFE_RELEASE(PixelBlob);
	SAFE_RELEASE(VertexBlob);
	SAFE_RELEASE(InputLayout);
}