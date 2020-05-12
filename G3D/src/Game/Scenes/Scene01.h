#pragma once
#include "Game/GameState.h"
#include "Engine/G3D_Font.h"

#include <array>

struct Scene01 : public GameState
{
	bool On_load() override;
	void On_enter() override;
	void On_exit() override;
	void Handle_input() override;
	void Update_and_render() override;

	std::array<G3D::Mesh, 25> Boxes;
};