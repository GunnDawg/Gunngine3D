#pragma once
#include "Engine/G3D_Timers.h"
#include "Engine/G3D_Renderer.h"
#include "Engine/G3D_Keyboard.h"
#include "Engine/G3D_Mouse.h"
#include "Game/GameSettings.h"

//@Note: If we're going to take cross platform compatibility very seriously,
//then the data we put in this game structure needs to be platform agnostic.
//The alternative is to have multiple platform specific game objects, but I don't
//like that idea.
struct game
{
	bool IsRunning = false;
};

bool GameInitialize(game* Game);
void GameHandleInput(game* Game, keyboard* Keyboard, mouse* Mouse, delta_clock* dt);
void GameUpdateAndRender(game* Game, renderer* Renderer, delta_clock* dt);
void GameShutdown(game* Game);