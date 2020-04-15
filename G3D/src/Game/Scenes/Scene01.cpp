#include "Scene01.h"
#include "Game/Scenes/Scene02.h"

bool Scene01::On_load()
{
	OutputDebugString("S1 On_Load\n");

	//@INCOMPLETE: If this fails then we leak a ton of VRAM
	if (!Boxes[0].Load("WoodBox", "WoodBox", { -10.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[1].Load("WoodBox", "WoodBox", { -5.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[2].Load("WoodBox", "WoodBox", { 0.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[3].Load("WoodBox", "WoodBox", { 5.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[4].Load("WoodBox", "WoodBox", { 10.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[5].Load("WoodBox", "WoodBox", { -10.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[6].Load("WoodBox", "WoodBox", { -5.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[7].Load("WoodBox", "WoodBox", { 0.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[8].Load("WoodBox", "WoodBox", { 5.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[9].Load("WoodBox", "WoodBox", { 10.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[10].Load("WoodBox", "WoodBox", { -10.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[11].Load("WoodBox", "WoodBox", { -5.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[12].Load("WoodBox", "WoodBox", { 0.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[13].Load("WoodBox", "WoodBox", { 5.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[14].Load("WoodBox", "WoodBox", { 10.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[15].Load("WoodBox", "WoodBox", { -10.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[16].Load("WoodBox", "WoodBox", { -5.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[17].Load("WoodBox", "WoodBox", { 0.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[18].Load("WoodBox", "WoodBox", { 5.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[19].Load("WoodBox", "WoodBox", { 10.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[20].Load("WoodBox", "WoodBox", { -10.0f, 20.0f, 0.0f }))
		return false;

	if (!Boxes[21].Load("WoodBox", "WoodBox", { -5.0f, 20.0f, 0.0f }))
		return false;

	if (!Boxes[22].Load("WoodBox", "WoodBox", { 0.0f, 20.0f, 0.0f }))
		return false;

	if (!Boxes[23].Load("WoodBox", "WoodBox", { 5.0f, 20.0f, 0.0f }))
		return false;

	if (!Boxes[24].Load("WoodBox", "WoodBox", { 10.0f, 20.0f, 0.0f }))
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
	Game::GameCamera.SetPosition(0.0f, 10.0f, -12.0f);
}

void Scene01::On_exit()
{
	OutputDebugString("S1 On_Exit\n\n");
	for (size_t i = 0; i < Boxes.size(); ++i)
		Boxes[i].Unload();

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
				if (Game::Pause == PAUSED)
				{
					G3D::Core::Mouse.DisableCursor();
					Game::Pause = UNPAUSED;
				}
				else
				{
					G3D::Core::Mouse.EnableCursor();
					Game::Pause = PAUSED;
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

	if (Game::Pause == UNPAUSED)
	{
		if (G3D::Core::Keyboard.KeyIsPressed('W'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetForwardVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('A'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetLeftVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('S'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetBackVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('D'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetRightVector() * Game::GameCamera.GetCameraSpeed() * G3D::Core::PerformanceClock.DeltaTime);
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
	//@TEMP: This is only a band-aid to fix the depth buffer until we figure out what is wrong with the
	//depth buffer that I created. This simply sets it back to the default state.
	G3D::Core::Renderer.Context->OMSetDepthStencilState(nullptr, 1u);

	//Update
	for (size_t i = 0; i < Boxes.size(); ++i)
		Boxes[i].Update();

	//Render
	G3D::Core::Renderer.Clear(0.15f, 0.15f, 0.15f, 1.0f);
	for (size_t i = 0; i < Boxes.size(); ++i)
		Boxes[i].Draw();

	DebugFont.Draw();
}