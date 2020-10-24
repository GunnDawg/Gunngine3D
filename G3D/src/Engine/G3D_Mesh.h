#pragma once
#include "Engine/G3D_Shader.h"
#include "Engine/G3D_Texture.h"
#include "Engine/G3D_Light.h"

namespace G3D
{
	struct Mesh
	{
		bool Load();
		bool Load(const char* TextureName, const char* ShaderName, DirectX::XMFLOAT3 Position);
		void Update(const AmbientLight& AmbientLightSource);
		void Draw();
		void Unload();

		void SwapShader(const char* shaderName);

		ID3D11Buffer* VertexBuffer;
		ID3D11Buffer* IndexBuffer;
		ID3D11Buffer* TransformConstantBuffer;
		ID3D11Buffer* LightConstantBuffer;
		ID3D11InputLayout* InputLayout;

		UINT IndexCount;

		G3D::Shader Shader;
		G3D::Texture Texture;

		bool IsUsingDefault = false;

		DirectX::XMMATRIX worldPos;
	};
}