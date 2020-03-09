#include "Scenes/Scene01.h"

bool Game::Initialize()
{
	std::unique_ptr<GameState> S1 = std::make_unique<Scene01>();
	if (!GSM.Push(std::move(S1)))
	{
		OutputDebugString("Error loading scene01\n");
		return false;
	}

	IsRunning = true;

	return true;
}

void Game::HandleInput()
{
	GSM.HandleInput();
}

void Game::UpdateAndRender()
{
	//@NOTE: This is the only place we should be calling Renderer->Clear() and Present(). It makes no sense for
	//each scene to be making that round trip call to the renderer when it can be done _once_ here. Unless we get into
	//some weird batch rendering or cacheing that needs to be done else where, and changes this later.
	G3D::Core::Renderer.Clear(0.0f, 0.0f, 0.0f, 1.0f);
	GSM.UpdateAndRender();
	G3D::Core::Renderer.Present();

}

void Game::Shutdown()
{
	GSM.UnloadAll();
}