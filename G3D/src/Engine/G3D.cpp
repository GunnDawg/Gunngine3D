#include "G3D.h"

#ifdef _WIN64
#include "G3D_Win64Platform.cpp"
#elif __APPLE__
#include "G3D_ApplePlatform.cpp"
#elif __linux__
#include "G3D_LinuxPlatform.cpp"
#endif

#include "G3D_Renderer.cpp"
#include "Game/Game.cpp"