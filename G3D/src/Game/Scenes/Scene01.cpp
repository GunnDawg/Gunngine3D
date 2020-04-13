#include "Scene01.h"
#include "Game/Scenes/Scene02.h"

bool Scene01::On_load()
{
	OutputDebugString("S1 On_Load\n");

	//@INCOMPLETE: If this fails then we leak a ton of VRAM
	if (!testMesh.Load("WoodBox", "WoodBox", -25.0f, 0.0f, 0.0f))
		return false;

	if (!testMesh2.Load("WoodBox", "WoodBox", -20.0f, 0.0f, 0.0f))
		return false;

	if (!testMesh3.Load("WoodBox", "WoodBox", -15.0f, 0.0f, 0.0f))
		return false;

	if (!testMesh4.Load("WoodBox", "WoodBox", -10.0f, 0.0f, 0.0f))
		return false;

	if (!testMesh5.Load("WoodBox", "WoodBox", -5.0f, 0.0f, 0.0f))
		return false;

	if (!testMesh6.Load("WoodBox", "WoodBox", -25.0f, -5.0f, 0.0f))
		return false;

	if (!testMesh7.Load("WoodBox", "WoodBox", -20.0f, -5.0f, 0.0f))
		return false;

	if (!testMesh8.Load("WoodBox", "WoodBox", -15.0f, -5.0f, 0.0f))
		return false;

	if (!testMesh9.Load("WoodBox", "WoodBox", -10.0f, -5.0f, 0.0f))
		return false;

	if (!testMesh10.Load("WoodBox", "WoodBox", -5.0f, -5.0f, 0.0f))
		return false;

	if (!testMesh11.Load("WoodBox", "WoodBox", -25.0f, -10.0f, 0.0f))
		return false;

	if (!testMesh12.Load("WoodBox", "WoodBox", -20.0f, -10.0f, 0.0f))
		return false;

	if (!testMesh13.Load("WoodBox", "WoodBox", -15.0f, -10.0f, 0.0f))
		return false;

	if (!testMesh14.Load("WoodBox", "WoodBox", -10.0f, -10.0f, 0.0f))
		return false;

	if (!testMesh15.Load("WoodBox", "WoodBox", -5.0f, -10.0f, 0.0f))
		return false;

	if (!testMesh16.Load("WoodBox", "WoodBox", -25.0f, -15.0f, 0.0f))
		return false;

	if (!testMesh17.Load("WoodBox", "WoodBox", -20.0f, -15.0f, 0.0f))
		return false;

	if (!testMesh18.Load("WoodBox", "WoodBox", -15.0f, -15.0f, 0.0f))
		return false;

	if (!testMesh19.Load("WoodBox", "WoodBox", -10.0f, -15.0f, 0.0f))
		return false;

	if (!testMesh20.Load("WoodBox", "WoodBox", -5.0f, -15.0f, 0.0f))
		return false;

	if (!testMesh21.Load("WoodBox", "WoodBox", -25.0f, -20.0f, 0.0f))
		return false;

	if (!testMesh22.Load("WoodBox", "WoodBox", -20.0f, -20.0f, 0.0f))
		return false;

	if (!testMesh23.Load("WoodBox", "WoodBox", -15.0f, -20.0f, 0.0f))
		return false;

	if (!testMesh24.Load("WoodBox", "WoodBox", -10.0f, -20.0f, 0.0f))
		return false;

	if (!testMesh25.Load("WoodBox", "WoodBox", -5.0f, -20.0f, 0.0f))
		return false;

	//@INCOMPLETE: We haven't actually implemented this load function fully. We still need to format the
	//text passed to it on the Font side, which we're not doing.
	if (!DebugFont.Load("Debug", "Some Text"))
		return false;

	return true;
}

void Scene01::On_enter()
{
	OutputDebugString("S1 On_Enter\n");
	Game::GameCamera.Load();
	Game::GameCamera.SetPosition(-15.0f, -10.0f, -15.0f);
}

void Scene01::On_exit()
{
	OutputDebugString("S1 On_Exit\n\n");
	testMesh.Unload();
	DebugFont.Unload();
}

void Scene01::Handle_input()
{
	while (const auto e = G3D::Core::Keyboard.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
			case 0x1B://Escape
			{
				Game::IsRunning = false;
			} break;

			case 0x70://F1
			{
				if (Game::ShowDebugData)
					Game::ShowDebugData = false;
				else
					Game::ShowDebugData = true;
			} break;

			case 'P':
			{
				if (Game::IsPaused)
				{
					G3D::Core::Mouse.DisableCursor();
					Game::IsPaused = false;
				}
				else
				{
					G3D::Core::Mouse.EnableCursor();
					Game::IsPaused = true;
				}
			} break;

			case 'M':
			{
				if (Settings::Camera::FreeRoam)
				{
					Settings::Camera::FreeRoam = false;
					Game::GameCamera.SetPosition(Game::GameCamera.GetCameraPos().x, 0.0f, Game::GameCamera.GetCameraPos().z);
				}
				else
					Settings::Camera::FreeRoam = true;
			} break;

			case 0x27://Right Arrow
			{
				Game::GSM.Pop();

				std::unique_ptr<Scene02> S2 = std::make_unique<Scene02>();
				Game::GSM.Push(std::move(S2));
			} break;

		}
	}

	if (!Game::IsPaused)
	{
		if (G3D::Core::Keyboard.KeyIsPressed('A'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetLeftVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('D'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetRightVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('W'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetForwardVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('S'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetBackVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed(0x11))//Left Control
		{
			Game::GameCamera.AdjustPosition(0.0f, -Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime, 0.0f);
		}

		if (G3D::Core::Keyboard.KeyIsPressed(0x20))//Spacebar
		{
			Game::GameCamera.AdjustPosition(0.0f, Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime, 0.0f);
		}

		auto e = G3D::Core::Mouse.Read();
		while (e.GetType() == G3D::Mouse::Event::Type::RAW_MOVE)
		{
			Game::GameCamera.AdjustRotation((float)G3D::Core::Mouse.GetDeltaY() * Settings::Controls::MouseSensitivity, (float)G3D::Core::Mouse.GetDeltaX() * Settings::Controls::MouseSensitivity, 0.0f);
			e = G3D::Core::Mouse.Read();
		}
	}
}

void Scene01::Update_and_render()
{
	//Update
	testMesh.Update();
	testMesh2.Update();
	testMesh3.Update();
	testMesh4.Update();
	testMesh5.Update();
	testMesh6.Update();
	testMesh7.Update();
	testMesh8.Update();
	testMesh9.Update();
	testMesh10.Update();
	testMesh11.Update();
	testMesh12.Update();
	testMesh13.Update();
	testMesh14.Update();
	testMesh15.Update();
	testMesh16.Update();
	testMesh17.Update();
	testMesh18.Update();
	testMesh19.Update();
	testMesh20.Update();
	testMesh21.Update();
	testMesh22.Update();
	testMesh23.Update();
	testMesh24.Update();
	testMesh25.Update();

	//Render
	G3D::Core::Renderer.Clear(0.15f, 0.15f, 0.15f, 1.0f);

	testMesh.Draw();
	testMesh2.Draw();
	testMesh3.Draw();
	testMesh4.Draw();
	testMesh5.Draw();
	testMesh6.Draw();
	testMesh7.Draw();
	testMesh8.Draw();
	testMesh9.Draw();
	testMesh10.Draw();
	testMesh11.Draw();
	testMesh12.Draw();
	testMesh13.Draw();
	testMesh14.Draw();
	testMesh15.Draw();
	testMesh16.Draw();
	testMesh17.Draw();
	testMesh18.Draw();
	testMesh19.Draw();
	testMesh20.Draw();
	testMesh21.Draw();
	testMesh22.Draw();
	testMesh23.Draw();
	testMesh24.Draw();
	testMesh25.Draw();

	DebugFont.Draw();
}