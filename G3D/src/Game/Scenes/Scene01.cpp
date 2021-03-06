#include "Scene01.h"
#include "Game/Scenes/Scene02.h"

bool Scene01::On_load()
{
	OutputDebugString("S1 On_Load\n");
	Game::GameCamera.Load(0.0f, 10.0f, -24.0f, 0.0f, 0.0f, 0.0f);
	Game::AmbientLight.Load(1.0f, 1.0f, 1.0f, 0.8f);
	Game::player.Load();

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
				if (Settings::Dev::DebugOverlayEnabled)
				{
					if (!Settings::Dev::DevModeEnabled)
					{
						Settings::Dev::DevModeEnabled = true;
					}
					else
					{
						if (Settings::Dev::ShowBasicDebugInformationEnabled || Settings::Dev::ShowLightInformationEnabled)
						{
							Settings::Dev::ShowBasicDebugInformationEnabled = false;
							Settings::Dev::ShowLightInformationEnabled = false;
						}
						else
						{
							Settings::Dev::DevModeEnabled = false;
						}
					}
				}
			} break;

			case 0x28://Down Arrow
			{
				Game::AmbientLight.DecreaseStrength(0.05f);
			} break;

			case 0x26://Up Arrow
			{
				Game::AmbientLight.IncreaseStrength(0.05f);
			} break;

			case 'V':
			{
				if (Settings::Display::VSync)
					Settings::Display::VSync = false;
				else
					Settings::Display::VSync = true;
			} break;

			case 'Q':
			{
				G3D::Core::AppIsRunning = false;
			} break;

			case 0xC0://~ Key
			{
				if (Settings::Dev::DebugOverlayEnabled)
					Settings::Dev::DebugOverlayEnabled = false;
				else
					Settings::Dev::DebugOverlayEnabled = true;
			} break;

			case 0x70://F1
			{
				if (Settings::Dev::DebugOverlayEnabled)
				{
					if (Settings::Dev::DevModeEnabled)
					{
						if (Settings::Dev::ShowBasicDebugInformationEnabled)
						{
							Settings::Dev::ShowBasicDebugInformationEnabled = false;
						}
						else if (Settings::Dev::ShowLightInformationEnabled)
						{
							Settings::Dev::ShowBasicDebugInformationEnabled = true;
							Settings::Dev::ShowLightInformationEnabled = false;
						}
						else
						{
							Settings::Dev::ShowBasicDebugInformationEnabled = true;
							Settings::Dev::ShowLightInformationEnabled = false;
						}
					}
					else if (!Settings::Dev::ShowLightInformationEnabled)
					{
						Settings::Dev::ShowBasicDebugInformationEnabled = false;
						Settings::Dev::ShowLightInformationEnabled = false;
					}
				}
			} break;

			case 0x71://F2
			{
				if (Settings::Dev::DebugOverlayEnabled)
				{
					if (Settings::Dev::DevModeEnabled)
					{
						if (Settings::Dev::ShowLightInformationEnabled)
						{
							Settings::Dev::ShowLightInformationEnabled = false;
						}
						else if (Settings::Dev::ShowBasicDebugInformationEnabled)
						{
							Settings::Dev::ShowBasicDebugInformationEnabled = false;
							Settings::Dev::ShowLightInformationEnabled = true;
						}
						else
						{
							Settings::Dev::ShowLightInformationEnabled = true;
							Settings::Dev::ShowBasicDebugInformationEnabled = false;
						}
					}
					else if (!Settings::Dev::ShowBasicDebugInformationEnabled)
					{
						Settings::Dev::ShowBasicDebugInformationEnabled = false;
						Settings::Dev::ShowLightInformationEnabled = false;
					}
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
				if (Settings::Camera::Type == Settings::Camera::CameraType::FreeRoam)
				{
					Settings::Camera::Type = Settings::Camera::CameraType::FPS;
					Game::GameCamera.SetPosition(Game::GameCamera.GetCameraPos().x, 1.81f, Game::GameCamera.GetCameraPos().z);
				}
				else
					Settings::Camera::Type = Settings::Camera::CameraType::FreeRoam;
			} break;

			//@INCOMPLETE: This is being done for a crouch effect, but it's still not right/complete.
			case 'C':
			{
				if (Settings::Camera::Type != Settings::Camera::CameraType::FreeRoam)
				{
					if (!Game::player.isCrouched)
					{
						Game::GameCamera.AdjustPosition(0.0f, -1.0f, 0.0f);
						Game::player.isCrouched = true;
					}
					else
					{
						Game::GameCamera.AdjustPosition(0.0f, 1.0f, 0.0f);
						Game::player.isCrouched = false;
					}
				}
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
		if (G3D::Core::Keyboard.KeyIsPressed(0x10))//Left Shift
		{
			Game::player.isRunning = true;
		}
		else
		{
			Game::player.isRunning = false;
		}

		if (G3D::Core::Keyboard.KeyIsPressed('W'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetForwardVector() * Game::player.MoveSpeed * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('A'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetLeftVector() * Game::player.MoveSpeed * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('S'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetBackVector() * Game::player.MoveSpeed * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (G3D::Core::Keyboard.KeyIsPressed('D'))
		{
			Game::GameCamera.AdjustPosition(Game::GameCamera.GetRightVector() * Game::player.MoveSpeed * G3D::Core::PerformanceClock.DeltaTime);
		}

		if (Settings::Camera::Type == Settings::Camera::CameraType::FreeRoam)
		{
			if (G3D::Core::Keyboard.KeyIsPressed(0x11))//Left Control
			{
				Game::GameCamera.AdjustPosition(0.0f, -Game::player.MoveSpeed * G3D::Core::PerformanceClock.DeltaTime, 0.0f);
			}

			if (G3D::Core::Keyboard.KeyIsPressed(0x20))//Spacebar
			{
				Game::GameCamera.AdjustPosition(0.0f, Game::player.MoveSpeed * G3D::Core::PerformanceClock.DeltaTime, 0.0f);
			}
		}

		auto e = G3D::Core::Mouse.Read();
		while (e.GetType() == G3D::Mouse::Event::Type::RAW_MOVE)
		{
			if (e.GetType() == G3D::Mouse::Event::Type::Invalid)
				break;

			Game::GameCamera.AdjustRotation((float)G3D::Core::Mouse.GetDeltaY() * Settings::Controls::MouseSensitivity, (float)G3D::Core::Mouse.GetDeltaX() * Settings::Controls::MouseSensitivity, 0.0f);
			e = G3D::Core::Mouse.Read();
		}
	}
}

void Scene01::Update_and_render()
{
	//Update
	Game::player.Update();

	for (size_t i = 0; i < Boxes.size(); ++i)
		Boxes[i].Update(Game::AmbientLight);

	//Render
	for (size_t i = 0; i < Boxes.size(); ++i)
		Boxes[i].Draw();
}