#include "Engine/G3D_Core.h"

namespace G3D
{
	internal bool
	EngineInitialize(G3D::Core_Engine_Data* Engine)
	{
		if (!G3D::DeltaClockInitialize(&Engine->DeltaClock))
			return false;

		if (!G3D::WindowInitialize(&Engine->Window))
			return false;

		if (!G3D::RendererInitialize(&Engine->Renderer, &Engine->Window))
			return false;

		if (!Engine->Mouse.Init())
			return false;

		return true;
	}

	internal void
	EngineShutdown(G3D::Core_Engine_Data* Engine)
	{
		G3D::RendererShutdown(&Engine->Renderer);
		G3D::WindowShutdown(&Engine->Window);
	}
}