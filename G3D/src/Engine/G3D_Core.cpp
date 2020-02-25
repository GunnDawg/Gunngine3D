#include "Engine/G3D_Core.h"

internal bool
EngineInitialize(core_engine_data* Engine)
{
	if (!DeltaClockInitialize(&Engine->DeltaClock))
		return false;

	if (!RendererInitialize(&Engine->Renderer))
		return false;

	if (!Engine->Mouse.Init())
		return false;

	return true;
}