#include "Engine/G3D.h"

//Platform Stuff
#ifdef _WIN64
#include "Engine/G3D_Win64Platform.cpp"
#elif __APPLE__
#include "Engine/G3D_ApplePlatform.cpp"
#elif __linux__
#include "Engine/G3D_LinuxPlatform.cpp"
#endif

//Engine Stuff
#include "Engine/G3D_Core.cpp"
#include "Engine/G3D_Debug.cpp"
#include "Engine/G3D_Window.cpp"
#include "Engine/G3D_Renderer.cpp"
#include "Engine/G3D_Mesh.cpp"
#include "Engine/G3D_Shader.cpp"
#include "Engine/G3D_Texture.cpp"
#include "Engine/G3D_Light.cpp"
#include "Engine/G3D_Camera.cpp"
#include "Engine/G3D_Font.cpp"
#include "Engine/G3D_AdapterReader.cpp"
#include "Engine/G3D_Keyboard.cpp"
#include "Engine/G3D_Mouse.cpp"
#include "Engine/G3D_Timer.cpp"

//Game Stuff
#include "Game/Game.cpp"
#include "Game/Player.cpp"
#include "Game/Scenes/Scene01.cpp"
#include "Game/Scenes/Scene02.cpp"