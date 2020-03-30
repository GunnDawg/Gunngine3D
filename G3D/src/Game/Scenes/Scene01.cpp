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
	if (!DebugFont.Load("Some Text"))
		return false;

	return true;
}

void Scene01::On_enter()
{
	OutputDebugString("S1 On_Enter\n");
	Game::GameCamera.SetPosition(0.0f, 0.0f, 0.5f);
	Game::GameCamera.SetProjectionValues(135.0f, (static_cast<float>(Settings::Display::Width) / static_cast<float>(Settings::Display::Height)), 0.1f, 10.0f);
}

void Scene01::On_exit()
{
	OutputDebugString("S1 On_Exit\n\n");
	testMesh.Unload();
	DebugFont.Unload();
}

void Scene01::Handle_input()
{
	if (G3D::Core::Keyboard.KeyIsPressed(VK_ESCAPE))
		Game::IsRunning = false;

	if (G3D::Core::Keyboard.KeyIsPressed('S'))
		testMesh.SwapShader("Basic");

	if (G3D::Core::Keyboard.KeyIsPressed(VK_RIGHT))
	{
		Game::GSM.Pop();

		std::unique_ptr<Scene02> S2 = std::make_unique<Scene02>();
		Game::GSM.Push(std::move(S2));
	}
}

void Scene01::Update_and_render()
{
	//Update
	testMesh.Update();

	//Render
	testMesh.Draw();
	DebugFont.Draw();
}