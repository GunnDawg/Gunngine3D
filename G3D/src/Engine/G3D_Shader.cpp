#include "G3D_Shader.h"
#include <sstream>

bool Shader::Load(const char* shadername)
{
	HRESULT Result = 0u;
	local_persist const char* ShaderFilepath = "res/shaders/";
	local_persist const char* ShaderFileExtension = ".cso";

	std::wstringstream Vss;
	Vss << ShaderFilepath;
	Vss << shadername;
	Vss << "VertexShader";
	Vss << ShaderFileExtension;

	std::wstring StringStreamToWString = Vss.str();
	LPCWSTR WideStringVertexShaderFile = StringStreamToWString.c_str();

	//Create Vertex Shader
	Result = D3DReadFileToBlob(WideStringVertexShaderFile, &VertexBlob);
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

	std::wstringstream Pss;
	Pss << ShaderFilepath;
	Pss << shadername;
	Pss << "PixelShader";
	Pss << ShaderFileExtension;

	StringStreamToWString = Pss.str();
	LPCWSTR WideStringPixelShaderFile = StringStreamToWString.c_str();

	//Create Pixel Shader
	Result = D3DReadFileToBlob(WideStringPixelShaderFile, &PixelBlob);
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

	return true;
}

bool Shader::Load()
{
	HRESULT Result = 0u;
	local_persist const char* ShaderFilepath = "res/shaders/";
	local_persist const char* ShaderFileExtension = ".cso";

	std::wstringstream Vss;
	Vss << ShaderFilepath;
	Vss << "Default";
	Vss << "VertexShader";
	Vss << ShaderFileExtension;

	std::wstring StringStreamToWString = Vss.str();
	LPCWSTR WideStringVertexShaderFile = StringStreamToWString.c_str();

	//Create Vertex Shader
	Result = D3DReadFileToBlob(WideStringVertexShaderFile, &VertexBlob);
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

	std::wstringstream Pss;
	Pss << ShaderFilepath;
	Pss << "Default";
	Pss << "PixelShader";
	Pss << ShaderFileExtension;

	StringStreamToWString = Pss.str();
	LPCWSTR WideStringPixelShaderFile = StringStreamToWString.c_str();

	//Create Pixel Shader
	Result = D3DReadFileToBlob(WideStringPixelShaderFile, &PixelBlob);
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

	return true;
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