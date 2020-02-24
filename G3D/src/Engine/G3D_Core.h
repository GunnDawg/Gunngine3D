#pragma once
#include "Engine/G3D_Windows.h"
#include "Engine/G3D_Renderer.h"
#include "Engine/G3D_Keyboard.h"
#include "Engine/G3D_Mouse.h"
#include "Engine/G3D_Timers.h"

struct core_engine_data
{
	renderer Renderer;
	keyboard Keyboard;
	mouse Mouse;
	delta_clock DeltaClock;
};