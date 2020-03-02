#include "Engine/G3D_Core.h"

namespace G3D
{
	bool Core::Initialize()
	{
		if (!DeltaClock.Initialize())
			return false;

		if (!Window.Initialize())
			return false;

		if (!Renderer.Initialize())
			return false;

		if (!Mouse.Initialize())
			return false;

		return true;
	}

	void Core::Shutdown()
	{
		Renderer.Shutdown();
		Window.Shutdown();
	}

	//Debug Stuff
	void Core::OutputPerformanceData()
	{
	#if _DEBUG
		char Buffer[256];
		sprintf(Buffer, "%.04f ms/f,  %.04f FPS, %.04f MC/f\n", DeltaClock.MSPerFrame, DeltaClock.FPS, DeltaClock.MCPF);
		OutputDebugStringA(Buffer);
	#endif
	}
}