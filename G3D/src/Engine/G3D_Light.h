#pragma once

namespace G3D
{
	struct AmbientLight
	{
	public:
		AmbientLight()
		{
			Load();
		}

		AmbientLight(float r, float g, float b, float str)
		{
			Load(r, g, b, str);
		}

		inline void SetColor(float r, float g, float b)
		{
			Color = DirectX::XMFLOAT3(r, g, b);
		}

		inline void SetStrength(float str)
		{
			Strength = str;
		}

		inline void DecreaseStrength(float val)
		{
			Strength -= val;
			if (Strength < 0.0f)
			{
				Strength = 0.0f;
			}
		}

		inline void IncreaseStrength(float val)
		{
			Strength += val;
			if (Strength > 2.0f)
			{
				Strength = 2.0f;
			}
		}

		DirectX::XMFLOAT3 Color;
		float Strength = 0.8f;

	private:
		inline void Load()
		{
			SetColor(1.0f, 1.0f, 1.0f);
			SetStrength(1.0f);
		}

		inline void Load(float r, float g, float b, float str)
		{
			SetColor(r, g, b);
			SetStrength(str);
		}
	};

	struct DirectionalLight
	{

		DirectX::XMMATRIX worldPos;

		DirectX::XMFLOAT3 lightColor;
		DirectX::XMFLOAT3 lightDir;
	};

	struct SpotLight
	{

		DirectX::XMMATRIX worldPos;
	};

	struct PointLight
	{
		DirectX::XMMATRIX worldPos;

		DirectX::XMFLOAT3 lightColor;
		DirectX::XMFLOAT3 lightPos;
	};

	struct AreaLight
	{

		DirectX::XMMATRIX worldPos;
	};

	struct VolumeLight
	{

		DirectX::XMMATRIX worldPos;
	};
}