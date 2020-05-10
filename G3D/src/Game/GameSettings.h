#pragma once

namespace Settings
{
	namespace Display
	{
		static u16 Width = 0u;
		static u16 Height = 0u;
		static bool Windowed = true;
		static bool VSync = true;
	}

	namespace Audio
	{

	}

	namespace Graphics
	{
		static bool MSAA = true;
		static UINT MSAAQuality = 0u;
		static float DrawDistance = 100.0f;
	}

	namespace Controls
	{
		//static float MouseSensitivity = 0.005f;
		static float MouseSensitivity = 0.0005f;

	}

	namespace Camera
	{
		static bool FreeRoam = true;
		static float FOV = 59.0f; // Vertical FoV
		static float CameraSpeed = 0.02f;
	}
}