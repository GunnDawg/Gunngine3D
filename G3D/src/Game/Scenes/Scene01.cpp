#include "Scene01.h"
#include "Game/Scenes/Scene02.h"

bool Scene01::On_load()
{
	OutputDebugString("S1 On_Load\n");

	//@INCOMPLETE: If this fails then we leak a ton of VRAM
	if (!testMesh.Load("WoodBox", "WoodBox"))
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
	Game::GameCamera.SetPosition(0.0f, 0.0f, -2.0f);
	Game::GameCamera.SetProjectionValues(90.0f, (static_cast<float>(Settings::Display::Width) / static_cast<float>(Settings::Display::Height)), 0.1f, 1000.0f);
}

void Scene01::On_exit()
{
	OutputDebugString("S1 On_Exit\n\n");
	testMesh.Unload();
	DebugFont.Unload();
}

void Scene01::Handle_input()
{
	if (G3D::Core::Keyboard.KeyIsPressed(0x1B)) //Escape
		Game::IsRunning = false;

	if (!Game::IsPaused)
	{
		if (G3D::Core::Keyboard.KeyIsPressed('A'))
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetLeftVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);

		if (G3D::Core::Keyboard.KeyIsPressed('D'))
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetRightVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);

		if (G3D::Core::Keyboard.KeyIsPressed('W'))
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetForwardVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);

		if (G3D::Core::Keyboard.KeyIsPressed('S'))
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetBackVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);

		if (G3D::Core::Keyboard.KeyIsPressed(0x11)) //Left Control
			Game::GameCamera.AdjustPosition(0.0f, -Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime, 0.0f);

		if (G3D::Core::Keyboard.KeyIsPressed(0x20)) //Spacebar
			Game::GameCamera.AdjustPosition(0.0f, Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime, 0.0f);

		if (G3D::Core::Keyboard.KeyIsPressed(0x27)) //Right Arrow
		{
			Game::GSM.Pop();

			std::unique_ptr<Scene02> S2 = std::make_unique<Scene02>();
			Game::GSM.Push(std::move(S2));
		}
	}

	auto e = G3D::Core::Mouse.Read();
	while (e.GetType() == G3D::Mouse::Event::Type::RAW_MOVE)
	{
		Game::GameCamera.AdjustRotation((float)G3D::Core::Mouse.GetDeltaY() * Settings::Controls::MouseSensitivity, (float)G3D::Core::Mouse.GetDeltaX() * Settings::Controls::MouseSensitivity, 0.0f);
		e = G3D::Core::Mouse.Read();
	}
}

void Scene01::Update_and_render()
{
	//Update
	testMesh.Update();

	//Render
	G3D::Core::Renderer.Clear(0.15f, 0.15f, 0.15f, 1.0f);
	testMesh.Draw();
	DebugFont.Draw();
}