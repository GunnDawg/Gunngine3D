#pragma once

namespace G3D
{
	struct Window
	{
		bool Initialize();
		void Shutdown();

		HWND WindowHandle = {};
		WNDCLASSEX wc = {};
	};
}