#include "Scene02.h"
#include "Engine/G3D_Core.h"
#include "Game/Game.h"
#include "Game/Scenes/Scene01.h"

void Scene02::On_enter()
{

}

void Scene02::On_exit()
{
	
}

void Scene02::Handle_input()
{
	if (Engine::Keyboard.KeyIsPressed(VK_ESCAPE))
	{
		Game::IsRunning = false;
	}

	if (Engine::Keyboard.KeyIsPressed(VK_LEFT))
	{
		Game::GSM.Pop();

		std::unique_ptr<Scene01> S1 = std::make_unique<Scene01>();
		Game::GSM.Push(std::move(S1));
	}
}

void Scene02::UpdateAndRender()
{
	//Update

	//Render
	Engine::Renderer.Clear(1.0f, 0.0f, 0.0f, 1.0f);

	Engine::Renderer.Present();
}