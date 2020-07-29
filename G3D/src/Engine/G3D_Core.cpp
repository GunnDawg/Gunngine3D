#include "Engine/G3D_Core.h"

namespace G3D
{
	bool Core::Initialize(const HINSTANCE& instance)
	{
		if (!PerformanceClock.Initialize())
		{
			MessageBox(nullptr, "Error initializing performance clock. Please restart.", "Game Startup Error", MB_OK);
			return G3D_ERROR;
		}

#ifdef _WIN64
		if (!Window.Initialize(instance))
		{
			MessageBox(nullptr, "Error initializing game window. Please restart.", "Game Startup Error", MB_OK);
			return G3D_ERROR;
		}
#else
		if (!Window.Initialize())
		{
			//TODO: Error Handling.
			return G3D_ERROR;
		}
#endif

		if (!Renderer.Initialize())
		{
			MessageBox(nullptr, "Error initializing rendering API. Please restart.", "Game Startup Error", MB_OK);
			return G3D_ERROR;
		}

		if (!Mouse.Initialize())
		{
			MessageBox(nullptr, "Error initializing one or more input devices/controllers. Please restart.", "Game Startup Error", MB_OK);
			return G3D_ERROR;
		}

		if (!DebugFont.Load("Debug", "Some Text"))
		{
			MessageBox(nullptr, "Error loading debug font panel", "Game Startup Error", MB_OK);
			return G3D_ERROR;
		}

		#ifdef _DEBUG
			Settings::Dev::DevMode = true;
		#endif

		return G3D_OK;
	}

	void Core::ShowDebugInformation()
	{
		DebugFont.Draw();
	}

	void Core::Shutdown()
	{
		DebugFont.Unload();
		Renderer.Shutdown();
		Window.Shutdown();
	}
}