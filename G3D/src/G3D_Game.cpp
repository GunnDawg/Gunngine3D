#include "G3D_Game.h"
#include "G3D_Assert.h"

internal bool
GameInitialize(game* Game)
{
	ASSERT(Game != nullptr);

	Game->IsRunning = true;

	return true;
}

internal void
GameHandleInput(game* Game)
{
	ASSERT(Game != nullptr);
}

internal void
GameUpdateAndRender(game* Game, Win32Renderer* Renderer, float dt)
{
	ASSERT(Game != nullptr);
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

}