#include "G3D_Game.h"
#include "G3D_Assert.h"

internal bool
GameInitialize(game* Game)
{
	ASSERT(Game != 0);

	Game->IsRunning = true;

	return true;
}

internal void
GameHandleInput(game* Game)
{
	ASSERT(Game != 0);
}

internal void
GameUpdateAndRender(game* Game, renderer* Renderer, float dt)
{
	ASSERT(Game != 0);
	//Update
#if 0
	char Buffer[256];
	sprintf(Buffer, "DT: %.04f\n", dt);
	OutputDebugStringA(Buffer);
#endif

	//Render
	RendererClear(Renderer, DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	RendererPresent(Renderer);
}

internal void
GameShutdown(game* Game)
{
	ASSERT(Game != 0);
}