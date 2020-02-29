#pragma once
#include "Game/GameStateMachine.h"

struct Game
{
	inline static bool Initialize();
	inline static void HandleInput();
	inline static void UpdateAndRender();
	inline static void Shutdown();

	inline static bool IsRunning = false;
	inline static GameStateMachine GSM;
};