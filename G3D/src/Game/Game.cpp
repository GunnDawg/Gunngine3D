#include "Game/Game.h"
#include "Engine/G3D_Assert.h"
#include "Scenes/Scene01.h"

bool Game::Initialize()
{
	std::unique_ptr<GameState> S1 = std::make_unique<Scene01>();
	GSM.Push(std::move(S1));

	IsRunning = true;

	return true;
}

void Game::HandleInput(G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::DeltaClock* dt)
{
	GSM.HandleInput(Keyboard, Mouse, dt);
}

void Game::UpdateAndRender(G3D::Renderer* Renderer, G3D::DeltaClock* dt)
{
	GSM.UpdateAndRender(Renderer, dt);
}

void Game::Shutdown()
{
	GSM.UnloadAll();
}