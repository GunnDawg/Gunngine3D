#pragma once
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include <memory>

namespace G3D
{
	struct Font
	{
		bool Load(const char* fontName);
		bool Load();
		void Draw();
		void Unload();

		std::shared_ptr<DirectX::SpriteBatch> spriteBatch;
		std::shared_ptr<DirectX::SpriteFont> spriteFont;
	};
}