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
}

namespace Settings::Controls
{
	static float MouseSensitivity = 0.020f;
}