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
		bool Initialize();
		void Shutdown();

		//Debug Functionality
		//@NOTE: Only passing this a Delta_Clock for now, because it's the only data that's
		//being used. If at some point we need more than the Delta_Clock, we'll pass the whole
		//Core_Engine_Data object.
		void OutputPerformanceData();

		G3D::Window Window = {};
		G3D::Renderer Renderer = {};
		G3D::Keyboard Keyboard = {};
		G3D::Mouse Mouse = {};
		G3D::DeltaClock DeltaClock = {};
	};
}