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
		void RunWindowsMessageLoop();
		void Shutdown();

		RECT WindowRect = {};
		HWND WindowHandle = {};
		WNDCLASSEX WindowClass = {};
		MSG Msg = {};

		DWORD ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		DWORD styles = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;

	private:
		void Finalizewindow();
	};
#elif __APPLE__
	struct Window
	{
		//@NOTE: Apple specific window data here
		bool Initialize();
		bool CreateWindow();
		void Shutdown();
	};
#elif __linux__
	struct Window
	{
		//@NOTE: Linux specific window data here
		bool Initialize();
		bool CreateWindow();
		void Shutdown();
	};
#endif
}