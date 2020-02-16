#pragma warning(disable:6011)
#include "G3D_Win32Platform.h"

global_variable game* Game = new game;

LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch (msg)
	{
		case WM_CLOSE:
		{
			Game->IsRunning = false;
		} break;

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					Game->IsRunning = false;
				} break;

				default:
					break;
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
	local_persist float DeltaTime = 0.0f;
	local_persist Win32Renderer* Renderer = new Win32Renderer;

#if 1
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

	if (!RendererInitialize(Renderer))
		return -1;

	if (!GameInitialize(Game))
		return -1;

	LARGE_INTEGER LastCounter;
	QueryPerformanceCounter(&LastCounter);

	UINT64 LastCycleCount = __rdtsc();

	MSG msg;
	while (Game->IsRunning)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Main Loop
		GameHandleInput(Game);
		//TODO:Pass the frame time / delta time to this update function.
		GameUpdateAndRender(Game, Renderer, DeltaTime);

		//Query Performance Data
		UINT64 EndCycleCount = __rdtsc();

		LARGE_INTEGER EndCounter;
		QueryPerformanceCounter(&EndCounter);

		UINT64 CyclesElapsed = EndCycleCount - LastCycleCount;
		INT64 TimeElapsed = EndCounter.QuadPart - LastCounter.QuadPart;
		float MSPerFrame = ((1000.0f * TimeElapsed) / (float)PerfCountFrequency);
		float FPS = (float)PerfCountFrequency / (float)TimeElapsed;
		float MCPF = (float)CyclesElapsed / (1000.0f * 1000.0f);

		DeltaTime = MSPerFrame;

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
	Game = nullptr;

	RendererShutdown(Renderer);
	delete Renderer;
	Renderer = nullptr;

	return 0;
}