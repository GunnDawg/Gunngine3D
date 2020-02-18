#include "Game/Game.h"
#include "Engine/G3D_Assert.h"

internal bool
GameInitialize(game* Game)
{
	ASSERT(Game != 0);

	Game->Renderer = new renderer;
	if (!Game->Renderer)
		return false;

	if (!RendererInitialize(Game->Renderer))
		return false;

	Game->IsRunning = true;

	return true;
}

internal void
GameHandleInput(game* Game)
{
	ASSERT(Game != 0);
}

internal void
GameUpdateAndRender(game* Game)
{
	ASSERT(Game != 0);
	//Update
#if 1
	char Buffer[256];
	sprintf(Buffer, "DT: %.04f\n", Game->DeltaTime);
	OutputDebugStringA(Buffer);
#endif

	//Render
	RendererClear(Game->Renderer, 0.0f, 0.0f, 0.0f, 1.0f);

	RendererPresent(Game->Renderer);
}

internal void
GameShutdown(game* Game)
{
	ASSERT(Game != 0);

	RendererShutdown(Game->Renderer);
	delete Game->Renderer;
	Game->Renderer = 0;
}