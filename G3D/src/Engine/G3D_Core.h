#pragma once
#include "Engine/G3D_Window.h"
#include "Engine/G3D_Renderer.h"
#include "Engine/G3D_Keyboard.h"
#include "Engine/G3D_Mouse.h"
#include "Engine/G3D_Timer.h"
#include "Engine/G3D_Font.h"

namespace G3D
{
	struct Core
	{
		//Core Functionality
		inline static bool Initialize(const HINSTANCE& instance);
		inline static void Shutdown();

		//Debug Functionality
		inline static void ShowDebugInformation();
		inline static G3D::Font DebugFont;

		//Core Engine Components
		inline static G3D::Window Window = {};
		inline static G3D::Renderer Renderer = {};
		inline static G3D::Keyboard Keyboard = {};
		inline static G3D::Mouse Mouse = {};
		inline static G3D::PerformanceClock PerformanceClock = {};
		inline static G3D::Timer Wallclock = {};

		inline static bool AppIsRunning = false;
	};
}