#include "Scene02.h"
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
	if (G3D::Core::Keyboard.KeyIsPressed(VK_ESCAPE))
	{
		Game::IsRunning = false;
	}

	if (G3D::Core::Keyboard.KeyIsPressed(VK_LEFT))
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
}