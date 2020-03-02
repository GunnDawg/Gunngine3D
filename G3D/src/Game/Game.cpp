#include "Engine/G3D_Core.h"
#include "Scenes/Scene01.h"

bool Game::Initialize()
{
	std::unique_ptr<GameState> S1 = std::make_unique<Scene01>();
	GSM.Push(std::move(S1));

	IsRunning = true;

	return true;
}

void Game::HandleInput()
{
	GSM.HandleInput();
}

void Game::UpdateAndRender()
{
	G3D::Core::Renderer.Clear(0.0f, 0.0f, 0.0f, 1.0f);
	GSM.UpdateAndRender();
	G3D::Core::Renderer.Present();

}

void Game::Shutdown()
{
	GSM.UnloadAll();
}