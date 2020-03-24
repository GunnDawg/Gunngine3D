#include "G3D_Font.h"

namespace G3D
{
	bool Font::Load()
	{
		spriteBatch = std::make_unique<DirectX::SpriteBatch>(G3D::Core::Renderer.Context);
		spriteFont = std::make_unique<DirectX::SpriteFont>(G3D::Core::Renderer.Device, L"res/fonts/DebugFont.spritefont");

		return G3D_OK;
	}

	void Font::Draw()
	{
		char Buffer[256];
		sprintf(Buffer, "Frame Time: %.04f\nFPS: %.04f\nMilicycles Per Frame: %.04f\nVSync: %i\nMSAA: %i\n", G3D::Core::PerformanceClock.DeltaTime, G3D::Core::PerformanceClock.FPS, G3D::Core::PerformanceClock.MCPF, Settings::Display::VSync, Settings::Graphics::MSAA);

		spriteBatch->Begin();
			spriteFont->DrawString(spriteBatch.get(), Buffer, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
		spriteBatch->End();
	}
}