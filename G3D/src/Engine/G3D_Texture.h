#pragma once
#include <WICTextureLoader.h>

namespace G3D
{
	struct Texture
	{
		bool Load();
		void Bind();
		void Unload();

		ID3D11SamplerState* SamplerState;
		ID3D11ShaderResourceView* ShaderResourceView;
	};
}