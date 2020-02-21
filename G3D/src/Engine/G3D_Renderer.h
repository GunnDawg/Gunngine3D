#pragma once
#ifdef _WIN64
#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

struct renderer
{
	//Basic DirectX
	ID3D11Device* Device;
	ID3D11DeviceContext* Context;
	IDXGISwapChain* SwapChain;
	ID3D11RenderTargetView* RenderTargetView;
	bool Enable4xMsaa = false;

	//Rasterizer
	ID3D11RasterizerState* RasterizerState;

	//Depth Stencil
	ID3D11DepthStencilState* DepthStencilState;
	ID3D11Texture2D* DepthStencilBuffer;
	ID3D11DepthStencilView* DepthStencilView;
};
#elif __APPLE__
struct renderer
{
	//Apple specific rendering data here
};
#elif __linux__
struct renderer
{
	//Linux specific rendering data here
};
#endif

bool RendererInitialize(renderer* Renderer);
//@NOTE: This is a DirectX specific solution because of passing a DirectX matrix. The more platform agnostic
//way of doing it imo, is to just pass the r, g, b, a, as float values, or implement our own matrix types.
void RendererClear(renderer* Renderer, DirectX::XMFLOAT4 color);
void RendererClear(renderer* Renderer, float r, float g, float b, float a);
void RendererPresent(renderer* Renderer);
void RendererShutdown(renderer* Renderer);