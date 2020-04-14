#include "Engine/G3D_Win64Platform.h"

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

		//@NOTE: Keyboard Messages
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if (!(lParam & 0x40000000 || G3D::Core::Keyboard.AutorepeatIsEnabled()))
			{
				G3D::Core::Keyboard.OnKeyPressed(static_cast<u16>(wParam));
			}
		} break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			G3D::Core::Keyboard.OnKeyReleased(static_cast<u16>(wParam));
		} break;

		case WM_CHAR:
		{
			G3D::Core::Keyboard.OnChar(static_cast<u16>(wParam));
		} break;

		//@NOTE: Mouse Messages
		case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(lParam);
			if (pt.x >= 0 && pt.x < Settings::Display::Width && pt.y >= 0 && pt.y < Settings::Display::Height)
			{
				G3D::Core::Mouse.OnMouseMove(pt.x, pt.y);
				if (!G3D::Core::Mouse.IsInWindow())
				{
					SetCapture(hwnd);
					G3D::Core::Mouse.OnMouseEnter();
				}
			}
			else
			{
				//@NOTE: 0x0001 is Left Mouse and 0x0002 is Right Mouse
				if (wParam & (0x0001 | 0x0002))
				{
					G3D::Core::Mouse.OnMouseMove(pt.x, pt.y);
				}
				else
				{
					ReleaseCapture();
					G3D::Core::Mouse.OnMouseLeave();
				}
			}
		} break;

		case WM_INPUT:
		{
			//@REFACTOR: If we're trying to keep as much of the game code separate from the engine code
			//then this should probably be refactored out into such a way that only the game handles it.
			if (Game::Pause != PAUSED)
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
							G3D::Core::Mouse.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
						}
					}
				}
			}

			return DefWindowProc(hwnd, msg, wParam, lParam);
		} break;

		case WM_LBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			G3D::Core::Mouse.OnLeftPressed(pt.x, pt.y);
		} break;

		case WM_RBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			G3D::Core::Mouse.OnRightPressed(pt.x, pt.y);
			//@NOTE: We only want to disable the cursor if the game is NOT paused, otherwise
			//we want the cursor to always be enabled when pause state is active.
			//@REFACTOR: If we're trying to keep as much of the game code separate from the engine code
			//then this should probably be refactored out into such a way that only the game handles it.
			if (Game::Pause != PAUSED)
			{
				if (!G3D::Core::Mouse.IsCursorEnabled())
					G3D::Core::Mouse.EnableCursor();
				else
					G3D::Core::Mouse.DisableCursor();
			}
		} break;

		case WM_LBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			G3D::Core::Mouse.OnLeftReleased(pt.x, pt.y);
		} break;

		case WM_RBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			G3D::Core::Mouse.OnRightReleased(pt.x, pt.y);
		} break;

		case WM_MOUSEWHEEL:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				G3D::Core::Mouse.OnWheelUp(pt.x, pt.y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			{
				G3D::Core::Mouse.OnWheelDown(pt.x, pt.y);
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
	//@NOTE: Initialize Engine
	if (G3D::Core::Initialize(instance) != G3D_OK)
		return -1;

	//@NOTE: Initialize Game
	if (Game::Initialize() != G3D_OK)
		return -1;

	MSG msg;
	while (Game::IsRunning)
	{
		//@NOTE: Windows message loop
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				Game::IsRunning = false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//@NOTE: Game Loop
		Game::HandleInput();
		Game::UpdateAndRender();

		if (Game::Pause != PAUSED)
		{
			G3D::Core::PerformanceClock.Tick();
		}
	}

	//@NOTE: Shut everything down
	Game::Shutdown();
	G3D::Core::Shutdown();

	return 0;
}