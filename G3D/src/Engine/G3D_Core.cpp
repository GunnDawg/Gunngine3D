#include "Engine/G3D_Core.h"

namespace G3D
{
	bool Core::Initialize()
	{
		if (DeltaClock.Initialize() != G3D_OK)
			return G3D_ERROR;

		if (Window.Initialize() != G3D_OK)
			return G3D_ERROR;

		if (Renderer.Initialize() != G3D_OK)
			return G3D_ERROR;

		if (Mouse.Initialize() != G3D_OK)
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
	#if 1
		char Buffer[256];
		sprintf(Buffer, "%.04f ms/f,  %.04f FPS, %.04f MC/f\n", DeltaClock.MSPerFrame, DeltaClock.FPS, DeltaClock.MCPF);
		OutputDebugStringA(Buffer);
	#endif
	}
}