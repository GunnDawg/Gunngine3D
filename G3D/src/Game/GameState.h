#pragma once

struct GameState
{
	virtual void On_enter() = 0u;
	virtual void On_exit() = 0u;
	virtual void Handle_input() = 0u;
	virtual void UpdateAndRender() = 0u;
};