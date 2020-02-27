#include "Game/Game.h"
#include "Engine/G3D_Assert.h"

bool Game::Initialize()
{
	IsRunning = true;

	return true;
}

void Game::HandleInput(G3D::Keyboard* Keyboard, G3D::Mouse* Mouse, G3D::DeltaClock* dt)
{
	//Keyboard Input
	if (Keyboard->KeyIsPressed(VK_ESCAPE))
		IsRunning = false;
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

void Game::UpdateAndRender(G3D::Renderer* Renderer, G3D::DeltaClock* dt)
{
	//Update

	//Render
	Renderer->Clear(0.0f, 0.0f, 0.0f, 1.0f);

	Renderer->Present();
}

void Game::Shutdown()
{

}