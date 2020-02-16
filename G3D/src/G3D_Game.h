#pragma once
#include "G3D_Win32Renderer.h"

struct game
{
	bool IsRunning = false;
};

bool GameInitialize(game* Game);
void GameHandleInput(game* Game);
void GameUpdateAndRender(game* Game, Win32Renderer* Renderer, float dt);
void GameShutdown(game* Game);