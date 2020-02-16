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
void RendererClear(renderer* Renderer, DirectX::XMFLOAT4 color);
void RendererPresent(renderer* Renderer);
void RendererShutdown(renderer* Renderer);