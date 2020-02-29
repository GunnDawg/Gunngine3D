#pragma once
#include "GameState.h"
#include "Engine/G3D_Core.h"

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

	inline void HandleInput()
	{
		if (!GameStates.empty())
		{
			GameStates.back()->Handle_input();
		}
	}

	inline void UpdateAndRender()
	{
		if (!GameStates.empty())
		{
			GameStates.back()->UpdateAndRender();
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