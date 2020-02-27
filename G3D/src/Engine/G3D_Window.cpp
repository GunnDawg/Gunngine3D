#include "Engine/G3D_Window.h"

namespace G3D
{
	internal bool
	WindowInitialize(G3D::Window* Window)
	{
		#if _DEBUG
			Settings::Display::Windowed = true;
			Settings::Display::Width = GetSystemMetrics(SM_CXSCREEN);
			Settings::Display::Height = GetSystemMetrics(SM_CYSCREEN);
		#else
			Settings::Display::Windowed = false;
			Settings::Display::Width = GetSystemMetrics(SM_CXSCREEN);
			Settings::Display::Height = GetSystemMetrics(SM_CYSCREEN);
		#endif

		Window->wc.cbSize = sizeof(WNDCLASSEX);
		Window->wc.hCursor = LoadCursor(0, IDC_ARROW);
		Window->wc.hInstance = GetModuleHandle(0);
		Window->wc.lpfnWndProc = WndProc;
		Window->wc.lpszClassName = "WindowClass";
		Window->wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
		Window->wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

		if (!RegisterClassEx(&Window->wc))
			return false;

		Window->window_handle = CreateWindowEx(0, Window->wc.lpszClassName, "Gunngine3D", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, Settings::Display::Width, Settings::Display::Height, 0, 0, GetModuleHandle(0), 0);
		if (!Window->window_handle)
			return false;

		return true;
	}

	internal void
	WindowShutdown(G3D::Window* Window)
	{
		UnregisterClass(Window->wc.lpszClassName, GetModuleHandle(0));
		DestroyWindow(Window->window_handle);
	}
}