#pragma once

namespace G3D
{
	struct AmbientLight
	{
		inline void SetLightColor(float r, float g, float b)
		{
			AmbientLightColor = DirectX::XMFLOAT3(r, g, b);
		}

		inline void SetLightStrength(float str)
		{
			AmbientLightStrength = str;
		}

		inline void DecreaseStrength(float val)
		{
			AmbientLightStrength -= val;
		}

		inline void IncreaseStrength(float val)
		{
			AmbientLightStrength += val;
		}

		DirectX::XMFLOAT3 AmbientLightColor = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		float AmbientLightStrength = 0.8f;
	};
}