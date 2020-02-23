#pragma once
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
	float DeltaTime = 0.0f;
};

bool GameInitialize(game* Game);
void GameHandleInput(game* Game, keyboard* Keyboard, mouse* Mouse);
void GameUpdateAndRender(game* Game, renderer* Renderer);
void GameShutdown(game* Game);