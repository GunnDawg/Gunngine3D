#include "Engine/G3D.h"

#ifdef _WIN64
#include "Engine/G3D_Win64Platform.cpp"
#elif __APPLE__
#include "Engine/G3D_ApplePlatform.cpp"
#elif __linux__
#include "Engine/G3D_LinuxPlatform.cpp"
#endif

#include "Engine/G3D_Renderer.cpp"
#include "Engine/G3D_Mouse.cpp"
#include "Engine/G3D_Keyboard.cpp"

#include "Game/Game.cpp"