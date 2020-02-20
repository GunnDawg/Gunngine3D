#include "Game/Game.h"
#include "Engine/G3D_Assert.h"

internal bool
GameInitialize(game* Game)
{
	ASSERT(Game);

	Game->Renderer = new renderer;
	if (!Game->Renderer)
		return false;

	if (!RendererInitialize(Game->Renderer))
		return false;

	Game->Keyboard = new keyboard;
	if (!Game->Keyboard)
		return false;

	Game->Mouse = new mouse;
	if (!Game->Mouse)
		return false;

	if (!Game->Mouse->Init())
		return false;

	//Game->Mouse->DisableCursor();

	Game->IsRunning = true;

	return true;
}

internal void
GameHandleInput(game* Game)
{
	ASSERT(Game);
	//Keyboard Input
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

	//Mouse Input
	const auto e = Game->Mouse->Read();
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
	RendererClear(Game->Renderer, 0.0f, 0.0f, 0.0f, 1.0f);

	RendererPresent(Game->Renderer);
}

internal void
GameShutdown(game* Game)
{
	ASSERT(Game);

	delete Game->Keyboard;
	Game->Keyboard = 0;

	delete Game->Mouse;
	Game->Mouse = 0;

	RendererShutdown(Game->Renderer);
	delete Game->Renderer;
	Game->Renderer = 0;
}