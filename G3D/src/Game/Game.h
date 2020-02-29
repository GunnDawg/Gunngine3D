#pragma once
#include "Game/GameStateMachine.h"

struct Game
{
	inline static bool Initialize();
	inline static void HandleInput(G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::DeltaClock* dt);
	inline static void UpdateAndRender(G3D::Renderer* Renderer, G3D::DeltaClock* dt);
	inline static void Shutdown();

	inline static bool IsRunning = false;
	inline static GameStateMachine GSM;
};