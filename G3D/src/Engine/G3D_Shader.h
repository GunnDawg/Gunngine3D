#pragma once
#include <sstream>
//#include <string>

namespace G3D
{
	struct Shader
	{
		bool Load();
		bool Load(const char* shaderName);
		void Bind();
		void Unload();

		ID3D11VertexShader* VertexShader;
		ID3D11PixelShader* PixelShader;
		ID3DBlob* VertexBlob;
		ID3DBlob* PixelBlob;

		bool IsUsingDefault = false;
	};
}