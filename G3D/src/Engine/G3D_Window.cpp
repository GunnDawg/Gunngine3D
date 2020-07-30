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

		WindowRect.left = 0u;
		WindowRect.top = 0u;
		WindowRect.right = WindowRect.left + Settings::Display::Width;
		WindowRect.bottom = WindowRect.top + Settings::Display::Height;

		AdjustWindowRectEx(&WindowRect, styles, false, ex_style);

		WindowClass.cbSize = sizeof(WNDCLASSEX);
		WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
		WindowClass.hInstance = instance;
		WindowClass.lpfnWndProc = WndProc;
		WindowClass.lpszClassName = "WindowClass";
		WindowClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
		WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

		if (!RegisterClassEx(&WindowClass))
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
		WindowHandle = CreateWindowEx(0, WindowClass.lpszClassName, "Gunngine3D - Release Build", styles, WindowRect.left, WindowRect.top, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, 0, 0, instance, 0);
		if (!WindowHandle)
			return G3D_ERROR;

		FinalizeWindow();

		return G3D_OK;
	}

	bool Window::CreateDebugWindow(const HINSTANCE& instance)
	{
		local_persist u16 centerX = (GetSystemMetrics(SM_CXSCREEN) - WindowRect.right) / 2;
		local_persist u16 centerY = (GetSystemMetrics(SM_CYSCREEN) - WindowRect.bottom) / 2;

		WindowHandle = CreateWindowEx(0, WindowClass.lpszClassName, "Gunngine3D - Debug Build", styles, centerX, centerY, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, 0, 0, instance, 0);
		if (!WindowHandle)
			return G3D_ERROR;

		FinalizeWindow();

		return G3D_OK;
	}

	void Window::FinalizeWindow()
	{
		ShowWindow(WindowHandle, true);
		SetForegroundWindow(WindowHandle);
		SetFocus(WindowHandle);
	}

	void Window::RunWindowsMessageLoop()
	{
		while (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
		{
			if (Msg.message == WM_QUIT)
				G3D::Core::AppIsRunning = false;

			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
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
		UnregisterClass(WindowClass.lpszClassName, WindowClass.hInstance);
	}
}