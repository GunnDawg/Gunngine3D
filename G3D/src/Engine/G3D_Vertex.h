#pragma once

struct BasicVertex
{
	DirectX::XMFLOAT3 position;
};

struct ColoredVertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};

struct TexturedVertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 textureCoord;
};