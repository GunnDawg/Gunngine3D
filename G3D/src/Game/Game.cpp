#include "Game/Game.h"
#include "Engine/G3D_Assert.h"

internal bool
GameInitialize(game* Game)
{
	ASSERT(Game);

	if (!RendererInitialize(&Game->Renderer))
		return false;

	if (!Game->Mouse.Init())
		return false;

#if 0
	Game->Mouse.DisableCursor();
#endif

	Game->IsRunning = true;

	return true;
}

internal void
GameHandleInput(game* Game)
{
	ASSERT(Game);
	//Keyboard Input
	if (Game->Keyboard.KeyIsPressed(VK_ESCAPE))
		Game->IsRunning = false;
#if 1
	if (Game->Keyboard.KeyIsPressed('D'))
	{
		char Buffer[256];
		sprintf(Buffer, "DT: %.04f\n", Game->DeltaTime);
		OutputDebugStringA(Buffer);
	}
#endif

	//Mouse Input
	const auto e = Game->Mouse.Read();
	//if (e.GetType() == G3D::Mouse::Event::Type::Move)
	//if (e.GetType() == mouse::Event::Type::RAW_MOVE)
	if (e.GetType() == mouse::Event::Type::LPress)
		OutputDebugStringA("L Mouse Pressed");
	if (e.GetType() == mouse::Event::Type::RPress)
		OutputDebugStringA("R Mouse Pressed");
	if (e.GetType() == mouse::Event::Type::WheelUp)
		OutputDebugStringA("Mouse Wheel Up");
	if (e.GetType() == mouse::Event::Type::WheelDown)
		OutputDebugStringA("Mouse Wheel Down");
}

internal void
GameUpdateAndRender(game* Game)
{
	ASSERT(Game);
	//Update

	//Render
	RendererClear(&Game->Renderer, 0.0f, 0.0f, 0.0f, 1.0f);

	RendererPresent(&Game->Renderer);
}

internal void
GameShutdown(game* Game)
{
	ASSERT(Game);

	RendererShutdown(&Game->Renderer);
}