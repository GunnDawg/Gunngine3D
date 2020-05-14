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
		local_persist char TitleBuffer[24];
		sprintf(TitleBuffer, "Gunngine3D");

		spriteBatch->Begin();
			spriteFont->DrawString(spriteBatch.get(), TitleBuffer, DirectX::XMFLOAT2((Settings::Display::Width / 2) - 55, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
		spriteBatch->End();

		if (Settings::General::DevMode)
		{
			if (Settings::General::ShowingBasic)
			{
				//@MOVE: All of this needs to be moved out into some debug structure so that this class
				//is not specific to printing ONLY debug information.
				//@NOTE: These are static
				local_persist char Buffer[512];
				local_persist const char* Build;
				local_persist const char* Version = "0.0.0.1";
				local_persist const char* Status;
				local_persist u16 Width = Settings::Display::Width;
				local_persist u16 Height = Settings::Display::Height;
				local_persist const char* VSync;
				local_persist const char* MSAA;
				local_persist const char* InputType;
				local_persist const char* Camera;
				local_persist const float CSpeed = Settings::Camera::CameraSpeed * 100.0f;
				local_persist const float cSens = Settings::Controls::MouseSensitivity * 1000.0f;
				local_persist float DrawDistance = Settings::Graphics::DrawDistance;
				local_persist float FOV = Settings::Camera::FOV;

				//@NOTE: These get updated every frame
				local_persist s32 Clock;
				local_persist float DeltaTime;
				local_persist float FPS;
				local_persist float MCPF;
				local_persist float CameraX;
				local_persist float CameraY;
				local_persist float CameraZ;

				//@PERFORMANCE: How much  of a performance cost is it to assign these per-frame data
				//every frame?
				Clock = static_cast<int>(G3D::Core::Timer.Peek());
				DeltaTime = G3D::Core::PerformanceClock.DeltaTime;
				FPS = G3D::Core::PerformanceClock.FPS;
				MCPF = G3D::Core::PerformanceClock.MCPF;
				CameraX = Game::GameCamera.GetCameraPos().x;
				CameraY = Game::GameCamera.GetCameraPos().y;
				CameraZ = Game::GameCamera.GetCameraPos().z;

				if (Game::Pause == PAUSED)
					Status = "Paused";
				else
					Status = "Playing";

				if (Settings::Controls::IsUsingGamepad)
					InputType = "Gamepad";
				else
					InputType = "Keyboard";

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

				sprintf(Buffer, "F1 Hide Basic Information\n\nBuild: %s\nVersion: %s\n\nPerformance Information:\n  Status: %s\n  Runtime Clock: %is\n  Frame Time: %.02fms\n  FPS: %.02f\n  CPU MCPF: %.02f\n\nVideo Settings:\n  Resolution: %ix%i\n  VSync: %s\n  MSAA: %s\n  Draw Distance: %.02f\n\nInput Settings:\n  Device: %s\n  Look Sens: %.02f\n\nCamera Settings:\n  Mode: %s\n  vFOV: %.02f\n  Speed: %.02f\n  Position:\n   X: %.02f\n   Y: %.02f\n   Z: %0.2f", Build, Version, Status, Clock, DeltaTime, FPS, MCPF, Width, Height, VSync, MSAA, DrawDistance, InputType, cSens, Camera, FOV, CSpeed, CameraX, CameraY, CameraZ);

				spriteBatch->Begin();
				spriteFont->DrawString(spriteBatch.get(), Buffer, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
				spriteBatch->End();
			}
			else if (Settings::General::ShowingLights)
			{
				char Buffer[512];
				local_persist float AmbientStr;
				AmbientStr = Game::AmbientLight.AmbientLightStrength;

				sprintf(Buffer, "F2 Hide Lighting Information\n\nStrength: %.02f", AmbientStr);

				spriteBatch->Begin();
					spriteFont->DrawString(spriteBatch.get(), Buffer, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
				spriteBatch->End();
			}
			else
			{
				local_persist char Buffer[512];
				sprintf(Buffer, "F1 Show System Information\nF2 Show Lighting Information\n\nF12 Close Debug Menu");

				spriteBatch->Begin();
					spriteFont->DrawString(spriteBatch.get(), Buffer, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::Colors::White, 0.0f, DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f));
				spriteBatch->End();
			}
		}
		else
		{
			local_persist char Buffer[128];
			sprintf(Buffer, "F12 Debug Menu");

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