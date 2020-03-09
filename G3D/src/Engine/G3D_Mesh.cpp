#include "Engine/G3D_Mesh.h"

void Mesh::Draw()
{
	HRESULT Result = 0u;

	const Vertex vertices[] =
	{
		{0.0f, 0.5f, 1.0f},
		{0.5f, -0.5f, 1.0f},
		{-0.5f, -0.5f, 1.0f}
	};

	ID3D11Buffer* pVertexBuffer;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA srd;
	ZeroMemory(&srd, sizeof(D3D11_SUBRESOURCE_DATA));
	srd.pSysMem = vertices;

	Result = G3D::Core::Renderer.Device->CreateBuffer(&bd, &srd, &pVertexBuffer);
	if (FAILED(Result))
	{
		//@TODO: Error Checking.
	}

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	G3D::Core::Renderer.Context->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);

	//Create Pixel Shader
	ID3D11PixelShader* pPixelShader;
	ID3DBlob* pBlob;
	Result = D3DReadFileToBlob(L"BasicPixelShader.cso", &pBlob);
	if (FAILED(Result))
	{
		//@TODO: Error Checking.
	}

	Result = G3D::Core::Renderer.Device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	if (FAILED(Result))
	{
		//@TODO: Error Checking.
	}

	//Bind Pixel Shader
	G3D::Core::Renderer.Context->PSSetShader(pPixelShader, 0, 0);

	//Create Vertex Shader
	ID3D11VertexShader* pVertexShader;
	Result = D3DReadFileToBlob(L"BasicVertexShader.cso", &pBlob);
	if (FAILED(Result))
	{
		//@TODO: Error Checking.
	}

	Result = G3D::Core::Renderer.Device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	if (FAILED(Result))
	{
		//@TODO: Error Checking.
	}

	//Bind vertex Shader
	G3D::Core::Renderer.Context->VSSetShader(pVertexShader, 0, 0);

	//Create Input Layout
	ID3D11InputLayout* pInputLayout;
	ZeroMemory(&pInputLayout, sizeof(ID3D11InputLayout));
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	G3D::Core::Renderer.Device->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);

	//Set Primitive Topology
	G3D::Core::Renderer.Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	G3D::Core::Renderer.Context->IASetInputLayout(pInputLayout);

	G3D::Core::Renderer.Context->Draw(static_cast<UINT>(std::size(vertices)), 0u);

	SAFE_RELEASE(pVertexBuffer);
	SAFE_RELEASE(pVertexShader);
	SAFE_RELEASE(pPixelShader);
	SAFE_RELEASE(pInputLayout);
	SAFE_RELEASE(pBlob);
}