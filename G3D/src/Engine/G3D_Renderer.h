#pragma once
#ifdef _WIN64
#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>

#include "Game/GameSettings.h"

//@NOTE:Import Libraries for DX
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#endif

namespace G3D
{
#ifdef _WIN64
	struct Renderer
	{
		bool Initialize();
		//@NOTE: This is a DirectX specific solution because of passing a DirectX matrix. The more platform agnostic
		//way of doing it imo, is to just pass the r, g, b, a, as float values, or implement our own matrix types.
		inline void Clear(DirectX::XMFLOAT4 color)
		{
			const float clearColor[] = { color.x, color.y, color.z, color.w };
			Context->ClearRenderTargetView(RenderTargetView, clearColor);
			Context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
		}

		//@NOTE: This is more cross-platform, as almost all platforms will have some way to take in 4 float values
		//and pack them into their own platform/renderer specific format.
		inline void Clear(float r, float g, float b, float a)
		{
			const float clearColor[] = { r, g, b, a };
			Context->ClearRenderTargetView(RenderTargetView, clearColor);
			Context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
		}

		inline void Present()
		{
			local_persist HRESULT Result = 0;
			Result = SwapChain->Present(Settings::Display::VSync, 0u);
			if (FAILED(Result))
			{
				//@NOTE This shouldn't actually fail, but maybe in the future recreate the renderer
				//if it does.
			}
		}

		void Shutdown();

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
	struct Renderer
	{
		//Apple specific rendering data here
	};
#elif __linux__
	struct Renderer
	{
		//Linux specific rendering data here
	};
#endif
}