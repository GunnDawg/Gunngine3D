#include "Engine/G3D_Window.h"

namespace G3D
{
	bool Window::Initialize()
	{
		#if _DEBUG
			Settings::Display::Windowed = true;
		#else
			Settings::Display::Windowed = false;
		#endif

		Settings::Display::Width = GetSystemMetrics(SM_CXSCREEN);
		Settings::Display::Height = GetSystemMetrics(SM_CYSCREEN);

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hInstance = GetModuleHandle(0);
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = "WindowClass";
		wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

		if (!RegisterClassEx(&wc))
			return false;

		window_handle = CreateWindowEx(0, wc.lpszClassName, "Gunngine3D", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, Settings::Display::Width, Settings::Display::Height, 0, 0, GetModuleHandle(0), 0);
		if (!window_handle)
			return false;

		return true;
	}

	void Window::Shutdown()
	{
		UnregisterClass(wc.lpszClassName, GetModuleHandle(0));
		DestroyWindow(window_handle);
	}
}