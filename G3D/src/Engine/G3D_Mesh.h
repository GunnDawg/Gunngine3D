#pragma once

struct Mesh
{
	bool Load();
	void Draw();
	void Unload();

	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3DBlob* VertexBlob;
	ID3DBlob* PixelBlob;
	ID3D11InputLayout* InputLayout;

	UINT IndexCount;
};