#pragma once

struct GameState
{
	virtual bool On_load() = 0;
	virtual void On_enter() = 0;
	virtual void On_exit() = 0;
	virtual void Handle_input() = 0;
	virtual void UpdateAndRender() = 0;
};