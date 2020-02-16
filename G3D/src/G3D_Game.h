#pragma once
#include "G3D_Renderer.h"

struct game
{
	bool IsRunning = false;
};

bool GameInitialize(game* Game);
void GameHandleInput(game* Game);
void GameUpdateAndRender(game* Game, renderer* Renderer, float dt);
void GameShutdown(game* Game);