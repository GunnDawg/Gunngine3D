#pragma once
#include "Engine/G3D_Shader.h"

namespace G3D
{
	struct Mesh
	{
		bool Load();
		bool Load(const char* shaderName);
		void Draw();
		void Unload();

		void SwapShader(const char* shaderName);

		ID3D11Buffer* VertexBuffer;
		ID3D11Buffer* IndexBuffer;
		ID3D11InputLayout* InputLayout;

		UINT IndexCount;

		G3D::Shader Shader;
	};
}