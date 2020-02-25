#include "Engine/G3D_Core.h"

internal bool
EngineInitialize(core_engine_data* Engine)
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
EngineShutdown(core_engine_data* Engine)
{
	RendererShutdown(&Engine->Renderer);
	WindowShutdown(&Engine->Window);
}