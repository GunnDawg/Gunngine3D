#include "G3D_Font.h"

constexpr const char* FontFilePath = "res/fonts/";
constexpr const char* FontFileExtension = ".spritefont";

namespace G3D
{
	bool Font::Load(const char* textString)
	{
		return Load("Default", textString);
	}

	bool Font::Load(const char* fontName, const char* textString)
	{
		TextString = textString;

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
		if (Game::ShowDebugData)
		{
			//@MOVE: All of this needs to be moved out into some debug structure so that this class
			//is not specific to printing ONLY debug information.
			local_persist char Buffer[512];
			local_persist const char* Build;
			local_persist const char* Version = "0.0.0.1";
			local_persist const char* Status;
			local_persist const char* VSync;
			local_persist const char* MSAA;
			local_persist const char* Camera;
			local_persist float DrawDistance = Settings::Graphics::DrawDistance;
			local_persist float FOV = Settings::Camera::FOV;


			//@PERFORMANCE: How much of a performance cost are we incurring by declaring these every frame?
			float DeltaTime = G3D::Core::PerformanceClock.DeltaTime;
			float FPS = G3D::Core::PerformanceClock.FPS;
			float MCPF = G3D::Core::PerformanceClock.MCPF;
			float CameraX = Game::GameCamera.GetCameraPosX();
			float CameraY = Game::GameCamera.GetCameraPosY();
			float CameraZ = Game::GameCamera.GetCameraPosZ();

			if (Game::IsPaused)
				Status = "Paused";
			else
				Status = "Playing";

			if (Settings::Camera::FreeRoam)
				Camera = "Free";
			else
				Camera = "FPS";

			if (Settings::Display::VSync)
				VSync = "On";
			else
				VSync = "Off";

			if (Settings::Graphics::MSAA)
				MSAA = "On";
			else
				MSAA = "Off";

			#if _DEBUG
				Build = "Debug";
			#else
				Build = "Release";
			#endif

			sprintf(Buffer, "Press 'F1' to hide debug data\n\nBuild: %s\nVersion: %s\n\nPerformance Information:\n  Status: %s\n  Frame Time: %.02fms\n  FPS: %.02f\n  CPU Millicycles Per Frame: %.02f\n\nCamera Settings:\n  Mode: %s\n  FOV: %.02f\n  Position:\n   X: %.02f\n   Y: %.02f\n   Z: %0.2f\n\nVideo Settings:\n  VSync: %s\n  MSAA: %s\n  Draw Distance: %.02f", Build, Version, Status, DeltaTime, FPS, MCPF, Camera, FOV, CameraX, CameraY, CameraZ, VSync, MSAA, DrawDistance);
			//sprintf(Buffer, "Build: %s\nVersion: 0.0.0.1\n\nPerformance Information:\n  Frame Time: %.02fms\n  FPS: %.02f\n  Millicycles Per Frame: %.02f\n\nCamera Settings:\n  Mode: %s\n  FOV: %.02f\n\  Position:\n   X: %.02f\n   Y: %.02f\n   Z: %0.2f\n\nVideo Settings:\n  VSync: %s\n  MSAA: %s\n  Draw Distance: %.02f", Build, G3D::Core::PerformanceClock.DeltaTime, G3D::Core::PerformanceClock.FPS, G3D::Core::PerformanceClock.MCPF, Camera, Settings::Camera::FOV, Game::GameCamera.GetCameraPosX(), Game::GameCamera.GetCameraPosY(), Game::GameCamera.GetCameraPosZ(), VSync, MSAA, Settings::Graphics::DrawDistance);

			spriteBatch->Begin();
				spriteFont->DrawString(spriteBatch.get(), Buffer, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
			spriteBatch->End();
		}
		else
		{
			local_persist char Buffer[32];
			sprintf(Buffer, "Press 'F1' to show debug data");

			spriteBatch->Begin();
				spriteFont->DrawString(spriteBatch.get(), Buffer, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
			spriteBatch->End();
		}
	}

	void Font::Unload()
	{
		spriteBatch = nullptr;
		spriteFont = nullptr;
	}
}