#pragma once
#include "Game/GameStateMachine.h"
#include "Engine/G3D_Camera.h"

struct Game
{
	inline static bool Initialize();
	inline static void HandleInput();
	//@NOTE: So incase someone other than myself is reading this and wonders why I'm putting Update and Render into the same
	//function, it has to do with something I heard during Handmade Hero Casey's video on platform architecture, and had to do with
	//keeping everything as close as possible in the L1 cache, or at least give it as much chance to surive on the cache, before the update
	//code grabs it and does what it needs to do with it. If you have any input on any truth to this or want to say something about it,
	//please do!
	inline static void UpdateAndRender();
	inline static void Shutdown();

	inline static bool IsRunning = false;
	inline static GameStateMachine GSM;
	inline static G3D::Camera GameCamera;
};