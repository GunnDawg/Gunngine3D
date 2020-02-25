#include "Game/Game.h"
#include "Engine/G3D_Assert.h"

internal bool
GameInitialize(game* Game)
{
	ASSERT(Game);

	Game->IsRunning = true;

	return true;
}

internal void
GameHandleInput(game* Game, G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::Delta_Clock* dt)
{
	ASSERT(Game);
	//Keyboard Input
	if (Keyboard->KeyIsPressed(VK_ESCAPE))
		Game->IsRunning = false;
#if 1
	if (Keyboard->KeyIsPressed('D'))
	{
		char Buffer[256];
		sprintf(Buffer, "DT: %.04f\n", dt->MSPerFrame);
		OutputDebugStringA(Buffer);
	}
#endif

	//Mouse Input
	const auto e = Mouse->Read();
	//if (e.GetType() == G3D::Mouse::Event::Type::Move)
	//if (e.GetType() == mouse::Event::Type::RAW_MOVE)
	if (e.GetType() == G3D::Mouse::Event::Type::LPress)
		OutputDebugStringA("L Mouse Pressed");
	if (e.GetType() == G3D::Mouse::Event::Type::RPress)
		OutputDebugStringA("R Mouse Pressed");
	if (e.GetType() == G3D::Mouse::Event::Type::WheelUp)
		OutputDebugStringA("Mouse Wheel Up");
	if (e.GetType() == G3D::Mouse::Event::Type::WheelDown)
		OutputDebugStringA("Mouse Wheel Down");
}

internal void
GameUpdateAndRender(game* Game, G3D::Renderer* Renderer, G3D::Delta_Clock* dt)
{
	ASSERT(Game);
	//Update

	//Render
	RendererClear(Renderer, 0.0f, 0.0f, 0.0f, 1.0f);

	RendererPresent(Renderer);
}

internal void
GameShutdown(game* Game)
{
	ASSERT(Game);
}