#include "Engine/G3D_Window.h"

namespace G3D
{
	bool Window::Initialize(HINSTANCE instance)
	{
		#if _DEBUG
			Settings::Display::Windowed = true;
		#else
			Settings::Display::Windowed = false;
		#endif

		Settings::Display::Width = GetSystemMetrics(SM_CXSCREEN);
		Settings::Display::Height = GetSystemMetrics(SM_CYSCREEN);

		RECT wr;
		wr.left = 0u;
		wr.top = 0u;
		wr.right = wr.left + Settings::Display::Width;
		wr.bottom = wr.top + Settings::Display::Height;
		AdjustWindowRect(&wr, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, false);

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hInstance = instance;
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = "WindowClass";
		wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

		if (!RegisterClassEx(&wc))
			return G3D_ERROR;

		WindowHandle = CreateWindowEx(0, wc.lpszClassName, "Gunngine3D", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, 0, 0, instance, 0);
		if (!WindowHandle)
			return G3D_ERROR;

		return G3D_OK;
	}

	void Window::Shutdown()
	{
		if (WindowHandle)
		{
			//@NOTE: We could check this for errors, but I feel like that's just making things even slower...
			DestroyWindow(WindowHandle);
			WindowHandle = 0;
		}

		//@NOTE: Could also error check this, but again, probably just a waste of time when all you want to do,
		//is get out!
		UnregisterClass(wc.lpszClassName, wc.hInstance);
	}
}