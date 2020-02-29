#include "Scene01.h"
#include "Game/Game.h"
#include "Game/Scenes/Scene02.h"

void Scene01::On_enter()
{

}

void Scene01::On_exit()
{

}

void Scene01::Handle_input(G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::DeltaClock* dt)
{
	if (Keyboard->KeyIsPressed(VK_ESCAPE))
	{
		Game::IsRunning = false;
	}

	if (Keyboard->KeyIsPressed(VK_RIGHT))
	{
		Game::GSM.Pop();

		std::unique_ptr<Scene02> S2 = std::make_unique<Scene02>();
		Game::GSM.Push(std::move(S2));
	}
}

void Scene01::UpdateAndRender(G3D::Renderer* Renderer, G3D::DeltaClock* DeltaClock)
{
	//Update

	//Render
	Renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);

	Renderer->Present();
}