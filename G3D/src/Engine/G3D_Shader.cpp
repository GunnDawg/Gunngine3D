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

		std::wstringstream Vss;
		Vss << ShaderFilepath;
		Vss << shadername;
		Vss << "VertexShader";
		Vss << ShaderFileExtension;

		std::wstring StringStreamToWString = Vss.str();
		LPCWSTR FinalVertexShaderFilepath = StringStreamToWString.c_str();

		//Create Vertex Shader
		Result = D3DReadFileToBlob(FinalVertexShaderFilepath, &VertexBlob);
		if (FAILED(Result))
		{
			//TODO: Error Checking.
			return G3D_ERROR;
		}

		Result = G3D::Core::Renderer.Device->CreateVertexShader(VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), nullptr, &VertexShader);
		if (FAILED(Result))
		{
			//TODO: Error Checking.
			return G3D_ERROR;
		}

		std::wstringstream Pss;
		Pss << ShaderFilepath;
		Pss << shadername;
		Pss << "PixelShader";
		Pss << ShaderFileExtension;

		StringStreamToWString = Pss.str();
		LPCWSTR FinalPixelShaderFilepath = StringStreamToWString.c_str();

		//Create Pixel Shader
		Result = D3DReadFileToBlob(FinalPixelShaderFilepath, &PixelBlob);
		if (FAILED(Result))
		{
			//TODO: Error Checking.
			return G3D_ERROR;
		}

		Result = G3D::Core::Renderer.Device->CreatePixelShader(PixelBlob->GetBufferPointer(), PixelBlob->GetBufferSize(), nullptr, &PixelShader);
		if (FAILED(Result))
		{
			//TODO: Error Checking.
			return G3D_ERROR;
		}

		return G3D_OK;
	}

	void Shader::Bind()
	{
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