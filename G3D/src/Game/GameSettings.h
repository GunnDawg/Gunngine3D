#pragma once

namespace Settings
{
	namespace Dev
	{
		static bool DevModeEnabled = false;
		static bool ShowBasicDebugInformationEnabled = false;
		static bool ShowLightInformationEnabled = false;
		static bool DebugOverlayEnabled = true;
		static bool RequirementChecksEnabled = true;
	}

	namespace General
	{

	}

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
		static bool IsUsingGamepad = false;
		static float MouseSensitivity = 0.005f;
		//static float MouseSensitivity = 0.0005f;
	}

	namespace Camera
	{
		enum class CameraType { FreeRoam, FPS, ThirdPerson, Overhead };

		CameraType Type = CameraType::FreeRoam;
		static float FOV = 59.0f; // Vertical FoV
		static float CameraSpeed = 0.02f;
	}
}