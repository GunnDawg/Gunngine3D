#pragma once

struct BasicVertex
{
	float x;
	float y;
	float z;
};

struct ColoredVertex
{
	float x;
	float y;
	float z;

	DirectX::XMFLOAT4 color;
};