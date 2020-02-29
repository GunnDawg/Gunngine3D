#pragma once
#include "Game/GameState.h"
#include "Engine/G3D_Renderer.h"

class Scene01 : public GameState
{
public:
	void On_enter() override;
	void On_exit() override;
	void Handle_input(G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::DeltaClock* dt) override;
	void UpdateAndRender(G3D::Renderer* Renderer, G3D::DeltaClock* DeltaClock) override;

private:

};