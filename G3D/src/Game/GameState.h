#pragma once
#include "Engine/G3D_Renderer.h"
#include "Engine/G3D_Keyboard.h"
#include "Engine/G3D_Mouse.h"
#include "Engine/G3D_Timers.h"

struct GameState
{
	virtual void On_enter() = 0u;
	virtual void On_exit() = 0u;
	virtual void Handle_input() = 0u;
	virtual void UpdateAndRender() = 0u;
};