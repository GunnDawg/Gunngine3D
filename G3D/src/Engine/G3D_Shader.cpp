#include "G3D_Shader.h"
#include <sstream>

#ifdef _DEBUG
constexpr const char* ShaderFilepath = "res/shaders/Debug/";
#else
constexpr const char* ShaderFilepath = "res/shaders/Release/";
#endif

constexpr const char* ShaderFileExtension = ".cso";

namespace G3D
{
	bool Shader::Load()
	{
		return Load("Default");
	}

	bool Shader::Load(const char* shadername)
	{
		HRESULT Result = 0u;

		//Parse Vertex Shader
		std::wstringstream Vss;
		Vss << ShaderFilepath;
		Vss << shadername;
		Vss << "VertexShader";
		Vss << ShaderFileExtension;

		std::wstring StringStreamToWString = Vss.str();
		LPCWSTR FinalVertexShaderFilepath = StringStreamToWString.c_str();

		//Read Vertex shader file to blob
		Result = D3DReadFileToBlob(FinalVertexShaderFilepath, &VertexBlob);
		if (FAILED(Result))
		{
			MessageBox(nullptr, "Error reading vertex shader file data to blob", "Vertex shader to blob error", MB_OK);
			return G3D_ERROR;
		}

		//Create Verstx Shader
		Result = G3D::Core::Renderer.Device->CreateVertexShader(VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), nullptr, &VertexShader);
		if (FAILED(Result))
		{
			MessageBox(nullptr, "Error creating vertex shader", "Vertex Shader Error", MB_OK);
			return G3D_ERROR;
		}

		//Parse Pixel Shader
		std::wstringstream Pss;
		Pss << ShaderFilepath;
		Pss << shadername;
		Pss << "PixelShader";
		Pss << ShaderFileExtension;

		StringStreamToWString = Pss.str();
		LPCWSTR FinalPixelShaderFilepath = StringStreamToWString.c_str();

		//Read Pixel shader file to blob
		Result = D3DReadFileToBlob(FinalPixelShaderFilepath, &PixelBlob);
		if (FAILED(Result))
		{
			MessageBox(nullptr, "Error reading pixel shader file data to blob", "Pixel shader to blob error", MB_OK);
			return G3D_ERROR;
		}

		//Create Pixel Shader
		Result = G3D::Core::Renderer.Device->CreatePixelShader(PixelBlob->GetBufferPointer(), PixelBlob->GetBufferSize(), nullptr, &PixelShader);
		if (FAILED(Result))
		{
			MessageBox(nullptr, "Error creating pixel shader", "Pixel Shader Error", MB_OK);
			return G3D_ERROR;
		}

		return G3D_OK;
	}

	void Shader::Bind()
	{
		//Set both vertex and pixel shaders to be the active shaders being used.
		G3D::Core::Renderer.Context->VSSetShader(VertexShader, 0u, 0u);
		G3D::Core::Renderer.Context->PSSetShader(PixelShader, 0u, 0u);
	}

	void Shader::Unload()
	{
		SAFE_RELEASE(VertexShader);
		SAFE_RELEASE(PixelShader);
		SAFE_RELEASE(VertexBlob);
		SAFE_RELEASE(PixelBlob);
	}
}