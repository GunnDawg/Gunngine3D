#pragma once

struct BasicVertex
{
	DirectX::XMFLOAT3 Position;
};

struct ColoredVertex
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT4 Color;
};

struct TexturedVertex
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 TextureCoord;
};