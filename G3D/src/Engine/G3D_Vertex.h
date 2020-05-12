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
	DirectX::XMFLOAT2 TextureCoords;
	DirectX::XMFLOAT3 Normal;

	TexturedVertex(float x, float y, float z, float u, float v, float nx, float ny, float nz) :
		Position(x, y, z), TextureCoords(u, v), Normal(nx, ny, nz)
	{

	}
};