#include "G3D_Game.h"
#include "G3D_Assert.h"

internal bool
GameStartup(game* Game)
{
	ASSERT(Game != nullptr);

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
	ASSERT(Game != nullptr);
}

internal void
GameUpdateAndRender(game* Game, float dt)
{
	ASSERT(Game != nullptr);
	//Update
#if 0
	char Buffer[256];
	sprintf(Buffer, "DT: %.04f\n", dt);
	OutputDebugStringA(Buffer);
#endif

	//Render
	RendererClear(Game->Renderer, DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	RendererPresent(Game->Renderer);
}

internal void
GameShutdown(game* Game)
{
	ASSERT(Game != nullptr);

	RendererShutdown(Game->Renderer);
	delete Game->Renderer;
	Game->Renderer = nullptr;
}