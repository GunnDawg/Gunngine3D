#pragma once
#include "Engine/G3D_Font.h"
#include "Engine/G3D_Timers.h"

namespace G3D
{
	class DebugData
	{
		bool Load();
		void Update();
		void Draw();
		void Unload();

		G3D::Font DebugFont;
	};
}