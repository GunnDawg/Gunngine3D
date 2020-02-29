#pragma once
#include "Engine/G3D_Windows.h"
#include "Engine/G3D_Window.h"
#include "Engine/G3D_Renderer.h"
#include "Engine/G3D_Keyboard.h"
#include "Engine/G3D_Mouse.h"
#include "Engine/G3D_Timers.h"

namespace G3D
{
	struct Engine
	{
		//Core Functionality
		inline static bool Initialize();
		inline static void Shutdown();

		//Debug Functionality
		inline static void OutputPerformanceData();

		inline static G3D::Window Window = {};
		inline static G3D::Renderer Renderer = {};
		inline static G3D::Keyboard Keyboard = {};
		inline static G3D::Mouse Mouse = {};
		inline static G3D::DeltaClock DeltaClock = {};
	};
}