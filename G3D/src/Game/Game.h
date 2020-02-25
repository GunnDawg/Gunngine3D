#pragma once
#include "Game/GameSettings.h"

//@Note: If we're going to take cross platform compatibility very seriously,
//then the data we put in this game structure needs to be platform agnostic.
//The alternative is to have multiple platform specific game objects, but I don't
//like that idea.
struct game
{
	bool IsRunning = false;
};


//@Refactor: Do we want to pass the game and engine data into these functions,
//or keep passing individual modules of the engine? hmmmmmmmmmmm......
bool GameInitialize(game* Game);
void GameHandleInput(game* Game, G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::Delta_Clock* dt);
void GameUpdateAndRender(game* Game, G3D::Renderer* Renderer, G3D::Delta_Clock* dt);
void GameShutdown(game* Game);