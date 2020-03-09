#pragma once
#include "GameState.h"
#include <vector>
#include <memory>

struct GameStateMachine
{
	inline bool Push(std::unique_ptr<GameState> states)
	{
		//@Speed I haven't tested it yet but I think emplace_back() is faster than push_back() here. Maybe run
		//a test later. Probably not a huge difference either way though.
		GameStates.emplace_back(std::move(states));
		
		if(GameStates.back()->On_load())
			GameStates.back()->On_enter();
		else
		{
			G3D::Core::Shutdown();
			return false;
		}

		return true;
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
			GameStates.back()->Update_and_render();
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