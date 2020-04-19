#pragma once

namespace Settings::Display
{
	static u16 Width = 0u;
	static u16 Height = 0u;
	static bool Windowed = true;
	static bool VSync = true;
}

namespace Settings::Audio
{

}

namespace Settings::Graphics
{
	static bool MSAA = true;
	static UINT MSAAQuality = 0u;
	static float DrawDistance = 100.0f;
}

namespace Settings::Controls
{
	static float MouseSensitivity = 0.005f;
}

namespace Settings::Camera
{
	static bool FreeRoam = true;
	static float FOV = 90.0f;
	static float CameraSpeed = 0.02f;
}