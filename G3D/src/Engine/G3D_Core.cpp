#include "Engine/G3D_Core.h"

namespace G3D
{
	bool Engine::Initialize()
	{
		if (!deltaClock.Initialize())
			return false;

		if (!window.Initialize())
			return false;

		if (!renderer.Initialize(&window))
			return false;

		if (!mouse.Init())
			return false;

		return true;
	}

	void Engine::Shutdown()
	{
		renderer.Shutdown();
		window.Shutdown();
	}

	//Debug Stuff
	void Engine::OutputPerformanceData()
	{
	#if _DEBUG
		char Buffer[256];
		sprintf(Buffer, "%.04f ms/f,  %.04f FPS, %.04f MC/f\n", deltaClock.MSPerFrame, deltaClock.FPS, deltaClock.MCPF);
		OutputDebugStringA(Buffer);
	#endif
	}
}