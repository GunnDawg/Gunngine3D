#pragma once

struct BasicVertex
{
	DirectX::XMFLOAT3 Position;

	BasicVertex(float x, float y, float z) :
		Position(x, y, z)
	{

	}
};

struct ColoredVertex
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT4 Color;

	ColoredVertex(float x, float y, float z, float r, float g, float b, float a) :
		Position(x, y, z), Color(r, g, b, a)
	{

	}
};

struct TexturedVertex
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 TextureCoord;

	TexturedVertex(float x, float y, float z, float u, float v) :
		Position(x, y, z), TextureCoord(u, v)
	{

	}
};