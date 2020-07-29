#pragma once
#ifdef _WIN64
	#include <d3d11.h>
	#include <dxgi.h>
	#include <DirectXMath.h>
	#include <d3dcompiler.h>

	#include "Game/GameSettings.h"

	//@NOTE:Import Libraries for DX
	#pragma comment(lib, "D3D11.lib")
	#pragma comment(lib, "DXGI.lib")
	#pragma comment(lib, "D3DCompiler.lib")
	#pragma comment(lib, "DirectXTK.lib")
#endif

namespace G3D
{
#ifdef _WIN64
	struct Renderer
	{
		//@NOTE: Windows specific rendering data here
		bool Initialize();
		//@TEMP: Do we really need/want to reset these states every frame/call to Clear()?
		//The font rendering code in DirectXTK is the ONLY thing that is messing with our
		//depth stencil state and rasterizer state. So in the future look for an alternative to
		//font rendering, I guess.
		inline void ResetStatesPerFrame()
		{
			Context->OMSetDepthStencilState(DepthStencilState, 1u);

			//@NOTE: Do we actually need to re-set the Rasterizer State here?
			//Context->RSSetState(RasterizerState);
		}

		inline void Clear(float r, float g, float b, float a)
		{
			ResetStatesPerFrame();

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
		//@NOTE: Apple specific rendering data here
		bool Initialize();
		void Shutdown();
	};
#elif __linux__
	struct Renderer
	{
		//@NOTE: Linux specific rendering data here
		bool Initialize();
		void Shutdown();
	};
#endif
}