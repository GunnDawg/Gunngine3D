#include "Scene01.h"
#include "Game/Scenes/Scene02.h"

bool Scene01::On_load()
{
	OutputDebugString("S1 On_Load\n");
	Game::GameCamera.Load(0.0f, 10.0f, -24.0f);

	Game::AmbientLight.SetLightColor(1.0f, 1.0f, 1.0f);
	Game::AmbientLight.SetLightStrength(0.8f);

	//@INCOMPLETE: If this fails then we leak a ton of VRAM
	if (!Boxes[0].Load("brickwall/base", "WoodBox", { -10.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[1].Load("brickwall/base", "WoodBox", { -5.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[2].Load("brickwall/base", "WoodBox", { 0.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[3].Load("brickwall/base", "WoodBox", { 5.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[4].Load("brickwall/base", "WoodBox", { 10.0f, 0.0f, 0.0f }))
		return false;

	if (!Boxes[5].Load("brickwall/base", "WoodBox", { -10.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[6].Load("brickwall/base", "WoodBox", { -5.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[7].Load("brickwall/base", "WoodBox", { 0.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[8].Load("brickwall/base", "WoodBox", { 5.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[9].Load("brickwall/base", "WoodBox", { 10.0f, 5.0f, 0.0f }))
		return false;

	if (!Boxes[10].Load("brickwall/base", "WoodBox", { -10.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[11].Load("brickwall/base", "WoodBox", { -5.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[12].Load("brickwall/base", "WoodBox", { 0.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[13].Load("brickwall/base", "WoodBox", { 5.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[14].Load("brickwall/base", "WoodBox", { 10.0f, 10.0f, 0.0f }))
		return false;

	if (!Boxes[15].Load("brickwall/base", "WoodBox", { -10.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[16].Load("brickwall/base", "WoodBox", { -5.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[17].Load("brickwall/base", "WoodBox", { 0.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[18].Load("brickwall/base", "WoodBox", { 5.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[19].Load("brickwall/base", "WoodBox", { 10.0f, 15.0f, 0.0f }))
		return false;

	if (!Boxes[20].Load("brickwall/base", "WoodBox", { -10.0f, 20.0f, 0.0f }))
		return false;

	if (!Boxes[21].Load("brickwall/base", "WoodBox", { -5.0f, 20.0f, 0.0f }))
		return false;

	if (!Boxes[22].Load("brickwall/base", "WoodBox", { 0.0f, 20.0f, 0.0f }))
		return false;

	if (!Boxes[23].Load("brickwall/base", "WoodBox", { 5.0f, 20.0f, 0.0f }))
		return false;

	if (!Boxes[24].Load("brickwall/base", "WoodBox", { 10.0f, 20.0f, 0.0f }))
		return false;

	return true;
}

void Scene01::On_enter()
{
	OutputDebugString("S1 On_Enter\n");
}

void Scene01::On_exit()
{
	OutputDebugString("S1 On_Exit\n\n");
	for (size_t i = 0; i < Boxes.size(); ++i)
		Boxes[i].Unload();
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

			case 0x28://Down Arrow
			{
				if(Game::AmbientLight.AmbientLightStrength >= 0.1f)
					Game::AmbientLight.DecreaseStrength(0.1f);
			} break;

			case 0x26://Up Arrow
			{
				if(Game::AmbientLight.AmbientLightStrength <= 0.99f)
					Game::AmbientLight.IncreaseStrength(0.1f);
			} break;

			case 'V':
			{
				if (Settings::Display::VSync)
					Settings::Display::VSync = false;
				else
					Settings::Display::VSync = true;
			} break;

			case 0x74://F5
			{
				if (!Settings::General::DevMode)
				{
					Settings::General::DevMode = true;
				}
				else
				{
					if (Settings::General::ShowingBasic || Settings::General::ShowingLights)
					{
						Settings::General::ShowingBasic = false;
						Settings::General::ShowingLights = false;

						Settings::General::DevMode = false;
					}
					else
					{
						Settings::General::DevMode = false;
					}
				}
			} break;

			case 0x70://F1
			{
				if (Settings::General::DevMode)
				{
					if (Settings::General::ShowingBasic)
					{
						Settings::General::ShowingBasic = false;
					}
					else if (Settings::General::ShowingLights)
					{
						break;
					}
					else
					{
						Settings::General::ShowingBasic = true;
						Settings::General::ShowingLights = false;
					}
				}
				else if(!Settings::General::ShowingLights)
				{
					Settings::General::ShowingBasic = false;
					Settings::General::ShowingLights = false;
				}
			} break;

			case 0x71://F2
			{
				if (Settings::General::DevMode)
				{
					if (Settings::General::ShowingLights)
					{
						Settings::General::ShowingLights = false;
					}
					else if (Settings::General::ShowingBasic)
					{
						break;
					}
					else
					{
						Settings::General::ShowingLights = true;
						Settings::General::ShowingBasic = false;
					}
				}
				else if(!Settings::General::ShowingBasic)
				{
					Settings::General::ShowingBasic = false;
					Settings::General::ShowingLights = false;
				}
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
					Game::GameCamera.SetPosition(Game::GameCamera.GetCameraPos().x, 1.81f, Game::GameCamera.GetCameraPos().z);
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
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetForwardVector() * Settings::Camera::CameraSpeed * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('A'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetLeftVector() * Settings::Camera::CameraSpeed * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('S'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetBackVector() * Settings::Camera::CameraSpeed * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('D'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetRightVector() * Settings::Camera::CameraSpeed * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (Settings::Camera::FreeRoam)
		{
			if (G3D::Core::Keyboard.KeyIsPressed(0x11))//Left Control
			{
				Game::GameCamera.AdjustPosition(0.0f, -Settings::Camera::CameraSpeed * G3D::Core::PerformanceClock.DeltaTime, 0.0f);
			}

			if (G3D::Core::Keyboard.KeyIsPressed(0x20))//Spacebar
			{
				Game::GameCamera.AdjustPosition(0.0f, Settings::Camera::CameraSpeed * G3D::Core::PerformanceClock.DeltaTime, 0.0f);
			}
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
	for (size_t i = 0; i < Boxes.size(); ++i)
		Boxes[i].Update(Game::AmbientLight);

	//Render
	for (size_t i = 0; i < Boxes.size(); ++i)
		Boxes[i].Draw();
}