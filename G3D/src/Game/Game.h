#pragma once
#include "Game/GameSettings.h"

//@Note: If we're going to take cross platform compatibility very seriously,
//then the data we put in this game structure needs to be platform agnostic.
//The alternative is to have multiple platform specific game objects, but I don't
//like that idea.
struct Game
{
	bool Initialize();
	void HandleInput(G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::DeltaClock* dt);
	void UpdateAndRender(G3D::Renderer* Renderer, G3D::DeltaClock* dt);
	void Shutdown();

	bool IsRunning = false;
};