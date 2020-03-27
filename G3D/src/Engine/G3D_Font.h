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

		std::shared_ptr<DirectX::SpriteBatch> spriteBatch;
		std::shared_ptr<DirectX::SpriteFont> spriteFont;

		const char* TextString;
	};
}