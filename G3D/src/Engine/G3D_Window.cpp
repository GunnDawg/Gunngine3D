#include "Engine/G3D_Window.h"

namespace G3D
{
	bool Window::Initialize(const HINSTANCE& instance)
	{
	#if _DEBUG
		Settings::Display::Windowed = true;
		Settings::Display::Width = 1600u;
		Settings::Display::Height = 900u;
	#else
		Settings::Display::Windowed = false;
		Settings::Display::Width = GetSystemMetrics(SM_CXSCREEN);
		Settings::Display::Height = GetSystemMetrics(SM_CYSCREEN);
	#endif

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

	#if _DEBUG
		if (!CreateDebugWindow(instance))
			return G3D_ERROR;
	#else
		if (!CreateWindow(instance))
			return G3D_ERROR;
	#endif

		return G3D_OK;
	}

	bool Window::CreateWindow(const HINSTANCE& instance)
	{
		WindowHandle = CreateWindowEx(0, wc.lpszClassName, "Gunngine3D - Release Build", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, 0, 0, instance, 0);
		if (!WindowHandle)
			return G3D_ERROR;

		return G3D_OK;
	}

	bool Window::CreateDebugWindow(const HINSTANCE& instance)
	{
		local_persist u16 centerX = (GetSystemMetrics(SM_CXSCREEN) - wr.right) / 2;
		local_persist u16 centerY = (GetSystemMetrics(SM_CYSCREEN) - wr.bottom) / 2;

		WindowHandle = CreateWindowEx(0, wc.lpszClassName, "Gunngine3D - Debug Build", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, centerX, centerY, wr.right - wr.left, wr.bottom - wr.top, 0, 0, instance, 0);
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