#pragma once
#include "GameState.h"
#include "Engine/G3D_Renderer.h"
#include "Engine/G3D_Keyboard.h"
#include "Engine/G3D_Mouse.h"
#include "Engine/G3D_Timers.h"

#include <vector>
#include <memory>

class GameStateMachine
{
public:
	inline void Push(std::unique_ptr<GameState> states)
	{
		//@Speed I haven't tested it yet but I think emplace_back() is faster than push_back() here. Maybe run
		//a test later. Probably not a huge difference either way though.
		GameStates.emplace_back(std::move(states));
		GameStates.back()->On_enter();
	}

	inline void Pop()
	{
		if (!GameStates.empty())
		{
			GameStates.back()->On_exit();
			GameStates.pop_back();
		}
	}

	inline void HandleInput(G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::DeltaClock* dt)
	{
		if (!GameStates.empty())
		{
			GameStates.back()->Handle_input(Keyboard, Mouse, dt);
		}
	}

	inline void UpdateAndRender(G3D::Renderer* Renderer, G3D::DeltaClock* DeltaClock)
	{
		if (!GameStates.empty())
		{
			GameStates.back()->UpdateAndRender(Renderer, DeltaClock);
		}
	}

	inline void UnloadAll()
	{
		while (!GameStates.empty())
		{
			Pop();
		}
	}

	std::vector<std::unique_ptr<GameState>> GameStates;
};