#pragma once
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include <memory>

namespace G3D
{
	struct Font
	{
		bool Load();
		void Draw();

		std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
		std::unique_ptr<DirectX::SpriteFont> spriteFont;
	};
}