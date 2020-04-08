#pragma once
#include <Engine/G3D_Windows.h>

#ifdef CreateWindow
#undef CreateWindow
#endif

namespace G3D
{
#ifdef	_WIN64
	struct Window
	{
		//@NOTE: Windows specific window data here
		bool Initialize(const HINSTANCE& instance);
		bool CreateWindow(const HINSTANCE& instance);
		bool CreateDebugWindow(const HINSTANCE& instance);
		void Shutdown();

		RECT wr;
		HWND WindowHandle = {};
		WNDCLASSEX wc = {};
	};
#elif __APPLE__
	struct Window
	{
		//@NOTE: Apple specific window data here
	};
#elif __linux__
	struct Window
	{
		//@NOTE: Linux specific window data here

	};
#endif
}