#include "Engine/G3D_Win64Platform.h"

//@NOTE: Globals for now.
global_variable G3D::Engine Engine;

LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch (msg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
		} break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;

		//Keyboard Messages
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if (!(lParam & 0x40000000 || Engine.Keyboard.AutorepeatIsEnabled()))
			{
				Engine.Keyboard.OnKeyPressed(static_cast<u16>(wParam));
			}
		} break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			Engine.Keyboard.OnKeyReleased(static_cast<u16>(wParam));
		} break;

		case WM_CHAR:
		{
			Engine.Keyboard.OnChar(static_cast<u16>(wParam));
		} break;

		//Mouse Messages
		case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(lParam);
			if (pt.x >= 0 && pt.x < Settings::Display::Width && pt.y >= 0 && pt.y < Settings::Display::Height)
			{
				Engine.Mouse.OnMouseMove(pt.x, pt.y);
				if (!Engine.Mouse.IsInWindow())
				{
					SetCapture(hwnd);
					Engine.Mouse.OnMouseEnter();
				}
			}
			else
			{
				if (wParam & (MK_LBUTTON | MK_RBUTTON))
				{
					Engine.Mouse.OnMouseMove(pt.x, pt.y);
				}
				else
				{
					ReleaseCapture();
					Engine.Mouse.OnMouseLeave();
				}
			}
		} break;

		case WM_INPUT:
		{
			UINT dataSize = 0u;
			GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, 0u, &dataSize, sizeof(RAWINPUTHEADER));
			if (dataSize > 0)
			{
				std::unique_ptr<BYTE[]> rawData = std::make_unique<BYTE[]>(dataSize);
				if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawData.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
				{
					RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawData.get());
					if (raw->header.dwType == RIM_TYPEMOUSE)
					{
						Engine.Mouse.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
					}
				}
			}

			return(DefWindowProc(hwnd, msg, wParam, lParam));
		} break;

		case WM_LBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Engine.Mouse.OnLeftPressed(pt.x, pt.y);
		} break;

		case WM_RBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Engine.Mouse.OnRightPressed(pt.x, pt.y);
		} break;

		case WM_LBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Engine.Mouse.OnLeftReleased(pt.x, pt.y);
		} break;

		case WM_RBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Engine.Mouse.OnRightReleased(pt.x, pt.y);
		} break;

		case WM_MOUSEWHEEL:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				Engine.Mouse.OnWheelUp(pt.x, pt.y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			{
				Engine.Mouse.OnWheelDown(pt.x, pt.y);
			}
		} break;

		default:
			Result = DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return Result;
}

int CALLBACK
WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR cmdLine, _In_ int cmdShow)
{
	if (!Engine.Initialize())
		return -1;

	if (!Game::Initialize())
		return -1;

	//Main Loop
	MSG msg;
	while (Game::IsRunning)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				Game::IsRunning = false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Game Loop
		Game::HandleInput(&Engine.Keyboard, &Engine.Mouse, &Engine.DeltaClock);
		Game::UpdateAndRender(&Engine.Renderer, &Engine.DeltaClock);

		Engine.DeltaClock.Tick();
		//Engine.OutputPerformanceData();
		Engine.DeltaClock.Reset();
	}

	//Shut everything down
	Game::Shutdown();
	Engine.Shutdown();

	return 0;
}