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
	G3D::Mesh testMesh2;
	G3D::Mesh testMesh3;
	G3D::Mesh testMesh4;
	G3D::Mesh testMesh5;
	G3D::Mesh testMesh6;
	G3D::Mesh testMesh7;
	G3D::Mesh testMesh8;
	G3D::Mesh testMesh9;
	G3D::Mesh testMesh10;
	G3D::Mesh testMesh11;
	G3D::Mesh testMesh12;
	G3D::Mesh testMesh13;
	G3D::Mesh testMesh14;
	G3D::Mesh testMesh15;
	G3D::Mesh testMesh16;
	G3D::Mesh testMesh17;
	G3D::Mesh testMesh18;
	G3D::Mesh testMesh19;
	G3D::Mesh testMesh20;
	G3D::Mesh testMesh21;
	G3D::Mesh testMesh22;
	G3D::Mesh testMesh23;
	G3D::Mesh testMesh24;
	G3D::Mesh testMesh25;


	G3D::Font DebugFont;
};