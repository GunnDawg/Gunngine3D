#pragma once

namespace G3D
{
#ifdef	_WIN64
	struct Window
	{
		bool Initialize();
		void Shutdown();

		HWND WindowHandle = {};
		WNDCLASSEX wc = {};
	};
#elif __APPLE__
	struct Window
	{

	};
#elif __linux__
	struct Window
	{

	};
#endif
}