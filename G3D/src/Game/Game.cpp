#include "Game/Game.h"
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
	GSM.UpdateAndRender();
}

void Game::Shutdown()
{
	GSM.UnloadAll();
}