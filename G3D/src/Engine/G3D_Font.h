#pragma once
#include <SpriteBatch.h>
#include <SpriteFont.h>

#include <memory>

namespace G3D
{
	struct Font
	{
		bool Load(const char* fontName, const char* textString);
		bool Load(const char* textString);
		void Draw();
		void Unload();

		std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
		std::unique_ptr<DirectX::SpriteFont> spriteFont;

		const char* TextString;
	};
}