#include "Engine/G3D_Core.h"

namespace G3D
{
	bool Core::Initialize()
	{
		if (!DeltaClock.Initialize())
			return G3D_ERROR;

		if (!Window.Initialize())
			return G3D_ERROR;

		if (!Renderer.Initialize())
			return G3D_ERROR;

		if (!Mouse.Initialize())
			return G3D_ERROR;

		return G3D_OK;
	}

	void Core::Shutdown()
	{
		Renderer.Shutdown();
		Window.Shutdown();
	}

	//Debug Stuff
	void Core::OutputPerformanceData()
	{
	#if 0
		char Buffer[256];
		sprintf(Buffer, "%.04f ms/f,  %.04f FPS, %.04f MC/f\n", DeltaClock.MSPerFrame, DeltaClock.FPS, DeltaClock.MCPF);
		OutputDebugStringA(Buffer);
	#endif
	}
}