#pragma once
#include "Game/GameStateMachine.h"

struct Game
{
	bool Initialize();
	void HandleInput(G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::DeltaClock* dt);
	void UpdateAndRender(G3D::Renderer* Renderer, G3D::DeltaClock* dt);
	void Shutdown();

	inline static bool IsRunning = false;
	inline static GameStateMachine GSM;
};