#pragma once
#include "Game/GameState.h"
#include "Engine/G3D_Font.h"

struct Scene01 : public GameState
{
	bool On_load() override;
	void On_enter() override;
	void On_exit() override;
	void Handle_input() override;
	void Update_and_render() override;

	G3D::Mesh testMesh;
	G3D::Font DebugFont;
};