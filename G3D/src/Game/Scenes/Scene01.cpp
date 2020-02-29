#include "Scene01.h"
#include "Game/Game.h"
#include "Game/Scenes/Scene02.h"

void Scene01::On_enter()
{

}

void Scene01::On_exit()
{

}

void Scene01::Handle_input()
{
	if (G3D::Engine::Keyboard.KeyIsPressed(VK_ESCAPE))
	{
		Game::IsRunning = false;
	}

	if (G3D::Engine::Keyboard.KeyIsPressed(VK_RIGHT))
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
	G3D::Engine::Renderer.Clear(0.0f, 0.0f, 0.0f, 1.0f);

	G3D::Engine::Renderer.Present();
}