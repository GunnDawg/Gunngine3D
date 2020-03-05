#include "Scene01.h"
#include "Game/Game.h"
#include "Game/Scenes/Scene02.h"

void Scene01::On_load()
{
	OutputDebugString("S1 On_Load\n");
}

void Scene01::On_enter()
{
	OutputDebugString("S1 On_Enter\n");
}

void Scene01::On_exit()
{
	OutputDebugString("S1 On_Exit\n\n");
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
}

void Scene01::UpdateAndRender()
{
	//Update

	//Render
}