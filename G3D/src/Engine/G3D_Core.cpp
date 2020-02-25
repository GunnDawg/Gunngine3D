#include "Engine/G3D_Core.h"

namespace G3D
{
	internal bool
	EngineInitialize(G3D::Core_Engine_Data* Engine)
	{
		if (!DeltaClockInitialize(&Engine->DeltaClock))
			return false;

		if (!WindowInitialize(&Engine->Window))
			return false;

		if (!RendererInitialize(&Engine->Renderer, &Engine->Window))
			return false;

		if (!Engine->Mouse.Init())
			return false;

		return true;
	}

	internal void
	EngineShutdown(G3D::Core_Engine_Data* Engine)
	{
		RendererShutdown(&Engine->Renderer);
		WindowShutdown(&Engine->Window);
	}
}