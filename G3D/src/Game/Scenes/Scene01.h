#pragma once
#include "Game/GameState.h"

struct Scene01 : public GameState
{
	void On_load() override;
	void On_enter() override;
	void On_exit() override;
	void Handle_input() override;
	void UpdateAndRender() override;
};