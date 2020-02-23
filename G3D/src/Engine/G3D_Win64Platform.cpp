#include "Engine/G3D_Win64Platform.h"
#include <memory>

//@NOTE: Globals for now.
global_variable renderer Renderer;
global_variable keyboard Keyboard;
global_variable mouse Mouse;
global_variable game Game;

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
			if (!(lParam & 0x40000000 || Keyboard.AutorepeatIsEnabled()))
			{
				Keyboard.OnKeyPressed(static_cast<u16>(wParam));
			}
		} break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			Keyboard.OnKeyReleased(static_cast<u16>(wParam));
		} break;

		case WM_CHAR:
		{
			Keyboard.OnChar(static_cast<u16>(wParam));
		} break;


		//Mouse Messages
		case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(lParam);
			if (pt.x >= 0 && pt.x < Settings::Display::Width && pt.y >= 0 && pt.y < Settings::Display::Height)
			{
				Mouse.OnMouseMove(pt.x, pt.y);
				if (!Mouse.IsInWindow())
				{
					SetCapture(hwnd);
					Mouse.OnMouseEnter();
				}
			}
			else
			{
				if (wParam & (MK_LBUTTON | MK_RBUTTON))
				{
					Mouse.OnMouseMove(pt.x, pt.y);
				}
				else
				{
					ReleaseCapture();
					Mouse.OnMouseLeave();
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
						Mouse.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
					}
				}
			}

			return(DefWindowProc(hwnd, msg, wParam, lParam));
		} break;

		case WM_LBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Mouse.OnLeftPressed(pt.x, pt.y);
		} break;

		case WM_RBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Mouse.OnRightPressed(pt.x, pt.y);
		} break;

		case WM_LBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Mouse.OnLeftReleased(pt.x, pt.y);
		} break;

		case WM_RBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Mouse.OnRightReleased(pt.x, pt.y);
		} break;

		case WM_MOUSEWHEEL:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				Mouse.OnWheelUp(pt.x, pt.y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			{
				Mouse.OnWheelDown(pt.x, pt.y);
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
	WNDCLASSEX wc = {};
	HWND hWnd = {};

#if _DEBUG
	Settings::Display::Windowed = true;
#else
	Settings::Display::Windowed = false;
	Settings::Display::Width = GetSystemMetrics(SM_CXSCREEN);
	Settings::Display::Height = GetSystemMetrics(SM_CYSCREEN);
#endif

	LARGE_INTEGER PerfCountFrequencyResult;
	QueryPerformanceFrequency(&PerfCountFrequencyResult);
	INT64 PerfCountFrequency = PerfCountFrequencyResult.QuadPart;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hInstance = instance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "WindowClass";
	wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	if (!RegisterClassEx(&wc))
		return -1;

	hWnd = CreateWindowEx(0, wc.lpszClassName, "Gunngine3D", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, Settings::Display::Width, Settings::Display::Height, 0, 0, instance, 0);
	if (!hWnd)
		return -1;

	if (!RendererInitialize(&Renderer))
		return -1;

	if (!Mouse.Init())
		return -1;

	if (!GameInitialize(&Game))
		return -1;

	LARGE_INTEGER LastCounter;
	QueryPerformanceCounter(&LastCounter);

	UINT64 LastCycleCount = __rdtsc();

	MSG msg;
	while (Game.IsRunning)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				Game.IsRunning = false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Main Loop
		GameHandleInput(&Game, &Keyboard, &Mouse);
		GameUpdateAndRender(&Game, &Renderer);

		//Query Performance Data
		UINT64 EndCycleCount = __rdtsc();

		LARGE_INTEGER EndCounter;
		QueryPerformanceCounter(&EndCounter);

		UINT64 CyclesElapsed = EndCycleCount - LastCycleCount;
		INT64 TimeElapsed = EndCounter.QuadPart - LastCounter.QuadPart;
		float MSPerFrame = ((1000.0f * TimeElapsed) / (float)PerfCountFrequency);
		float FPS = (float)PerfCountFrequency / (float)TimeElapsed;
		float MCPF = (float)CyclesElapsed / (1000.0f * 1000.0f);

		Game.DeltaTime = MSPerFrame;

#if 0
		char Buffer[256];
		sprintf(Buffer, "%.04f ms/f,  %.04f FPS, %.04f MC/f\n", MSPerFrame, FPS, MCPF);
		OutputDebugStringA(Buffer);
#endif

		LastCounter = EndCounter;
		LastCycleCount = EndCycleCount;
	}

	//Shut everything down
	RendererShutdown(&Renderer);
	GameShutdown(&Game);

	return 0;
}