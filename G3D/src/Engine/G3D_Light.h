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
			if (AmbientLightStrength < 0.0f)
			{
				AmbientLightStrength = 0.0f;
			}
		}

		inline void IncreaseStrength(float val)
		{
			AmbientLightStrength += val;
			if (AmbientLightStrength > 1.0f)
			{
				AmbientLightStrength = 1.0f;
			}
		}

		DirectX::XMFLOAT3 AmbientLightColor = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		float AmbientLightStrength = 0.8f;
	};

	struct SpotLight
	{

		DirectX::XMMATRIX worldPos;
	};

	struct PointLight
	{

		DirectX::XMMATRIX worldPos;
	};

	struct AreaLight
	{

		DirectX::XMMATRIX worldPos;
	};

	struct VolumeLight
	{

		DirectX::XMMATRIX worldPos;
	};

	struct DirectionalLight
	{

		DirectX::XMMATRIX worldPos;
	};
}