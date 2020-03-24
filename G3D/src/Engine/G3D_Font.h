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
		void Unload();

		DirectX::SpriteBatch* spriteBatch;
		DirectX::SpriteFont* spriteFont;
	};
}