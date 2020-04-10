#include "Scene02.h"
#include "Game/Scenes/Scene01.h"

bool Scene02::On_load()
{
	OutputDebugString("S2 On_Load\n");

	return true;
}

void Scene02::On_enter()
{
	OutputDebugString("S2 On_Enter\n");
	Game::GameCamera.SetPosition(0.0f, 0.0f, -2.0f);
}

void Scene02::On_exit()
{
	OutputDebugString("S2 On_Exit\n\n");
}

void Scene02::Handle_input()
{
	if (G3D::Core::Keyboard.KeyIsPressed(0x1B))
	{
		Game::IsRunning = false;
	}

	if (G3D::Core::Keyboard.KeyIsPressed(0x25))
	{
		Game::GSM.Pop();

		std::unique_ptr<Scene01> S1 = std::make_unique<Scene01>();
		Game::GSM.Push(std::move(S1));
	}
}

void Scene02::Update_and_render()
{
	//Update

	//Render
	//@NOTE: Calling clear here is not entirely necessary. The game loop handles that. We're just doing it
	//to make sure multiple scene support is working. But usually you wouldn't do this in every scene.
	G3D::Core::Renderer.Clear(1.0f, 0.0f, 0.0f, 1.0f);
}