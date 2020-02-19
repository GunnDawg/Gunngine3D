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

	Game->Keyboard = new keyboard;
	if (!Game->Keyboard)
		return false;

	Game->IsRunning = true;

	return true;
}

internal void
GameHandleInput(game* Game)
{
	ASSERT(Game != 0);
	if (Game->Keyboard->KeyIsPressed(VK_ESCAPE))
		Game->IsRunning = false;
#if 1
	if (Game->Keyboard->KeyIsPressed('D'))
	{
		char Buffer[256];
		sprintf(Buffer, "DT: %.04f\n", Game->DeltaTime);
		OutputDebugStringA(Buffer);
	}
#endif

}

internal void
GameUpdateAndRender(game* Game)
{
	ASSERT(Game != 0);
	//Update

	//Render
	RendererClear(Game->Renderer, 0.0f, 0.0f, 0.0f, 1.0f);

	RendererPresent(Game->Renderer);
}

internal void
GameShutdown(game* Game)
{
	ASSERT(Game != 0);

	delete Game->Keyboard;
	Game->Keyboard = 0;

	RendererShutdown(Game->Renderer);
	delete Game->Renderer;
	Game->Renderer = 0;
}