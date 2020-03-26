#include "G3D_Font.h"

constexpr const char* FontFilePath = "res/fonts/";
constexpr const char* FontFileExtension = ".spritefont";

namespace G3D
{
	bool Font::Load()
	{
		return Load("Default");
	}

	bool Font::Load(const char* fontName)
	{
		std::wstringstream ss;
		ss << FontFilePath;
		ss << fontName;
		ss << FontFileExtension;

		std::wstring StringStreamToWString = ss.str();
		LPCWSTR FinalFontFilepath = StringStreamToWString.c_str();

		spriteBatch = std::make_shared<DirectX::SpriteBatch>(G3D::Core::Renderer.Context);
		spriteFont =  std::make_shared<DirectX::SpriteFont>(G3D::Core::Renderer.Device, FinalFontFilepath);

		return G3D_OK;
	}

	void Font::Draw()
	{
		local_persist char Buffer[256];
		sprintf(Buffer, "Frame Time: %.02fms\nFPS: %.02f\nMillicycles Per Frame: %.02f\nVSync: %i\nMSAA: %i\n", G3D::Core::PerformanceClock.DeltaTime, G3D::Core::PerformanceClock.FPS, G3D::Core::PerformanceClock.MCPF, Settings::Display::VSync, Settings::Graphics::MSAA);

		spriteBatch->Begin();
			spriteFont->DrawString(spriteBatch.get(), Buffer, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
		spriteBatch->End();
	}

	void Font::Unload()
	{
		spriteBatch.reset();
		spriteBatch = nullptr;

		spriteFont.reset();
		spriteFont = nullptr;
	}
}