#include "G3D_Texture.h"

constexpr const char* TextureFilePath = "res/textures/";
constexpr const char* TextureFileExtension = ".png";

namespace G3D
{
	bool Texture::Load()
	{
		return Load("Default");
	}

	bool Texture::Load(const char* TextureFilepath)
	{
		HRESULT Result = 0u;

		std::wstringstream ss;
		ss << TextureFilePath;
		ss << TextureFilepath;
		ss << TextureFileExtension;

		std::wstring StringStreamToWString = ss.str();
		LPCWSTR FinalTextureFilepath = StringStreamToWString.c_str();

		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sd.MinLOD = 0u;
		sd.MaxLOD = D3D11_FLOAT32_MAX;

		Result = G3D::Core::Renderer.Device->CreateSamplerState(&sd, &SamplerState);
		if (FAILED(Result))
		{
			//TODO: Error Handling.
			return G3D_ERROR;
		}

		Result = DirectX::CreateWICTextureFromFile(G3D::Core::Renderer.Device, FinalTextureFilepath, nullptr, &ShaderResourceView);
		if (FAILED(Result))
		{
			//TODO: Error Handling.
			return G3D_ERROR;
		}

		return G3D_OK;
	}

	void Texture::Bind()
	{
		G3D::Core::Renderer.Context->PSSetSamplers(0u, 1u, &SamplerState);
		G3D::Core::Renderer.Context->PSSetShaderResources(0u, 1u, &ShaderResourceView);
	}

	void Texture::Unload()
	{
		SAFE_RELEASE(SamplerState);
		SAFE_RELEASE(ShaderResourceView);
	}
}