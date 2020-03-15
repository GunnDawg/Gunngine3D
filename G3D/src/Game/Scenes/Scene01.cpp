#include "Scene01.h"
#include "Game/Scenes/Scene02.h"

bool Scene01::On_load()
{
	OutputDebugString("S1 On_Load\n");

	//@INCOMPLETE: If this fails then we leak a ton of VRAM
	if (!testMesh.Load())
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
	testMesh.Unload();
}

void Scene01::Handle_input()
{
	if (G3D::Core::Keyboard.KeyIsPressed(VK_ESCAPE))
	{
		Game::IsRunning = false;
	}

	if (G3D::Core::Keyboard.KeyIsPressed(VK_RIGHT))
	{
		Game::GSM.Pop();

		std::unique_ptr<Scene02> S2 = std::make_unique<Scene02>();
		Game::GSM.Push(std::move(S2));
	}

	if (G3D::Core::Keyboard.KeyIsPressed('S'))
	{
		testMesh.SwapShader("Basic");
	}
}

void Scene01::Update_and_render()
{
	//Update

	//Render
	testMesh.Draw();
}