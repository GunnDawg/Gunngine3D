#include "Engine/G3D_Core.h"

namespace G3D
{
	bool Core::Initialize(HINSTANCE instance)
	{
		if (!PerformanceClock.Initialize())
			return G3D_ERROR;

		if (!Window.Initialize(instance))
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
	//@TEMPORARY: At some point we'll be displaying this information in the window itself,
	//rather than printing it to the VS output window.
	void Core::OutputPerformanceData()
	{
	#if 0
		char Buffer[256];
		sprintf(Buffer, "%.04f ms/f,  %.04f FPS, %.04f MC/f\n", PerformanceClock.DeltaTime, PerformanceClock.FPS, PerformanceClock.MCPF);
		OutputDebugStringA(Buffer);
	#endif
	}
}