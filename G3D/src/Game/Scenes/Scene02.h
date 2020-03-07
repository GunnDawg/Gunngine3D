#pragma once
#include "Game/GameState.h"

struct Scene02 : public GameState
{
	bool On_load() override;
	void On_enter() override;
	void On_exit() override;
	void Handle_input() override;
	void UpdateAndRender() override;
};