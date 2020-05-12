#pragma once

struct CB_VS_TransformConstantBuffer
{
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projMatrix;
};

struct CB_PS_AmbientLight
{
	DirectX::XMFLOAT3 ambientLightColor;
	float ambientLightStrength;
};