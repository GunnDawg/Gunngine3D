#include "Engine/G3D_Win64Platform.h"
#include <memory>

//@NOTE: Globals for now.
global_variable game* Game = new game;

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
			if (!(lParam & 0x40000000 || Game->Keyboard->AutorepeatIsEnabled()))
			{
				Game->Keyboard->OnKeyPressed(static_cast<u16>(wParam));
			}
		} break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			Game->Keyboard->OnKeyReleased(static_cast<u16>(wParam));
		} break;

		case WM_CHAR:
		{
			Game->Keyboard->OnChar(static_cast<u16>(wParam));
		} break;


		//Mouse Messages
		case WM_MOUSEMOVE:
		{
			POINTS pt = MAKEPOINTS(lParam);
			if (pt.x >= 0 && pt.x < Settings::Display::Width && pt.y >= 0 && pt.y < Settings::Display::Height)
			{
				Game->Mouse->OnMouseMove(pt.x, pt.y);
				if (!Game->Mouse->IsInWindow())
				{
					SetCapture(hwnd);
					Game->Mouse->OnMouseEnter();
				}
			}
			else
			{
				if (wParam & (MK_LBUTTON | MK_RBUTTON))
				{
					Game->Mouse->OnMouseMove(pt.x, pt.y);
				}
				else
				{
					ReleaseCapture();
					Game->Mouse->OnMouseLeave();
				}
			}
		} break;

		case WM_INPUT:
		{
			UINT dataSize;
			GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, 0u, &dataSize, sizeof(RAWINPUTHEADER));
			if (dataSize > 0)
			{
				std::unique_ptr<BYTE[]> rawData = std::make_unique<BYTE[]>(dataSize);
				if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawData.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
				{
					RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawData.get());
					if (raw->header.dwType == RIM_TYPEMOUSE)
					{
						Game->Mouse->OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
					}
				}
			}

			return(DefWindowProc(hwnd, msg, wParam, lParam));
		} break;

		case WM_LBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Game->Mouse->OnLeftPressed(pt.x, pt.y);
		} break;

		case WM_RBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Game->Mouse->OnRightPressed(pt.x, pt.y);
		} break;

		case WM_LBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Game->Mouse->OnLeftReleased(pt.x, pt.y);
		} break;

		case WM_RBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			Game->Mouse->OnRightReleased(pt.x, pt.y);
		} break;

		case WM_MOUSEWHEEL:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				Game->Mouse->OnWheelUp(pt.x, pt.y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			{
				Game->Mouse->OnWheelDown(pt.x, pt.y);
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

#if 0
	//@Temp: We're getting the users native screen resolution here before passing that
	//information off to CreateWindow() and the SwapChain. Not sure if leaving it here is 
	//best, or if it should be pushed to another function elsewhere.
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

	if (!GameInitialize(Game))
		return -1;


	//@TEMP: Do we keep this here in the platform layer or move it out to a mouse init function()?
	RAWINPUTDEVICE rid;
	ZeroMemory(&rid, sizeof(RAWINPUTDEVICE));
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0u;
	rid.hwndTarget = 0u;

	if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
		return -1;

	Game->Mouse->DisableCursor();

	LARGE_INTEGER LastCounter;
	QueryPerformanceCounter(&LastCounter);

	UINT64 LastCycleCount = __rdtsc();

	MSG msg;
	while (Game->IsRunning)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				Game->IsRunning = false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Main Loop
		GameHandleInput(Game);
		GameUpdateAndRender(Game);

		//Query Performance Data
		UINT64 EndCycleCount = __rdtsc();

		LARGE_INTEGER EndCounter;
		QueryPerformanceCounter(&EndCounter);

		UINT64 CyclesElapsed = EndCycleCount - LastCycleCount;
		INT64 TimeElapsed = EndCounter.QuadPart - LastCounter.QuadPart;
		float MSPerFrame = ((1000.0f * TimeElapsed) / (float)PerfCountFrequency);
		float FPS = (float)PerfCountFrequency / (float)TimeElapsed;
		float MCPF = (float)CyclesElapsed / (1000.0f * 1000.0f);

		Game->DeltaTime = MSPerFrame;

#if 0
		char Buffer[256];
		sprintf(Buffer, "%.04f ms/f,  %.04f FPS, %.04f MC/f\n", MSPerFrame, FPS, MCPF);
		OutputDebugStringA(Buffer);
#endif

		LastCounter = EndCounter;
		LastCycleCount = EndCycleCount;
	}

	//Shut everything down
	GameShutdown(Game);
	delete Game;
	Game = 0;

	return 0;
}