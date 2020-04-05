#pragma once
#include <Engine/G3D_Windows.h>

namespace G3D
{
#ifdef	_WIN64
	struct Window
	{
		//@NOTE: Windows specific window data here
		bool Initialize(const HINSTANCE& instance);
		void Shutdown();

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