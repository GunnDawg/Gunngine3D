#pragma once
#include "G3D_Renderer.h"

struct game
{
	renderer* Renderer = nullptr;
	bool IsRunning = false;
};

bool GameStartup(game* Game);
void GameHandleInput(game* Game);
void GameUpdateAndRender(game* Game, float dt);
void GameShutdown(game* Game);