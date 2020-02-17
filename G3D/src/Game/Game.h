#pragma once
#include "G3D_Renderer.h"

//@Note: If we're going to take cross platform compatibility very seriously,
//then the data we put in this game structure needs to be platform agnostic.
//The alternative is to have multiple platform specific game objects, but I don't
//like that idea.
struct game
{
	bool IsRunning = false;
};

bool GameInitialize(game* Game);
void GameHandleInput(game* Game);
void GameUpdateAndRender(game* Game, renderer* Renderer, float dt);
void GameShutdown(game* Game);