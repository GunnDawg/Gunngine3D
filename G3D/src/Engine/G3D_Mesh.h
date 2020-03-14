#pragma once
#include "Engine/G3D_Shader.h"

struct Mesh
{
	bool Load();
	bool Load(const char* shaderName);
	void Draw();
	void Unload();

	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	ID3D11InputLayout* InputLayout;

	UINT IndexCount;

	Shader shader;
};