#include "Engine/G3D_Renderer.h"
#include "Engine/G3D_Assert.h"
#include "Engine/G3D_AdapterReader.h"

#include <vector>

#ifdef _DEBUG
UINT debugFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
UINT debugFlags = 0u;
#endif

template<typename T>
void SAFE_RELEASE(T& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = 0;
	}
}

namespace G3D
{
	bool Renderer::Initialize()
	{
		HRESULT Result = 0u;

		std::vector<AdapterData> adapters = AdapterReader::GetAdapters();
		if (adapters.size() < 1)
			return G3D_ERROR;

		//Create our Device
		D3D_FEATURE_LEVEL featureLevel;

		Result = D3D11CreateDevice(
			0,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			debugFlags,
			0, 0,
			D3D11_SDK_VERSION,
			&Device,
			&featureLevel,
			&Context
		);
		if (FAILED(Result))
			return G3D_ERROR;

		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
			return G3D_ERROR;

		//Check for MSAA quality support
		if (Settings::Graphics::MSAA)
		{
			Result = Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4u, &Settings::Graphics::MSAAQuality);
			if (FAILED(Result))
				return G3D_ERROR;

			if (Settings::Graphics::MSAA)
			{
				ASSERT(Settings::Graphics::MSAAQuality > 0u);
			}
		}

		IDXGIDevice* dxgiDevice = 0u;
		Result = Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
		if (FAILED(Result))
		{
			SAFE_RELEASE(dxgiDevice);
			return G3D_ERROR;
		}

		IDXGIAdapter* dxgiAdapter = 0u;
		Result = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
		if (FAILED(Result))
		{
			SAFE_RELEASE(dxgiAdapter);
			SAFE_RELEASE(dxgiDevice);
			return G3D_ERROR;
		}

		IDXGIFactory* dxgiFactory = 0u;
		Result = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
		if (FAILED(Result))
		{
			SAFE_RELEASE(dxgiFactory);
			SAFE_RELEASE(dxgiAdapter);
			SAFE_RELEASE(dxgiDevice);
			return G3D_ERROR;
		}

		//Create our swap chain buffer description
		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
		bufferDesc.Width = Settings::Display::Width;
		bufferDesc.Height = Settings::Display::Height;
		bufferDesc.RefreshRate.Numerator = 60u;
		bufferDesc.RefreshRate.Denominator = 1u;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		//Create swap chain description
		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		scd.BufferDesc = bufferDesc;
		scd.BufferCount = 2u;
		scd.OutputWindow = GetActiveWindow();
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.Windowed = Settings::Display::Windowed;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		if (Settings::Graphics::MSAA)
		{
			scd.SampleDesc.Count = 4u;
			scd.SampleDesc.Quality = Settings::Graphics::MSAAQuality - 1u;
		}
		else
		{
			scd.SampleDesc.Count = 1u;
			scd.SampleDesc.Quality = 0u;
		}

		//Create swap chain
		Result = dxgiFactory->CreateSwapChain(Device, &scd, &SwapChain);
		if (FAILED(Result))
		{
			SAFE_RELEASE(dxgiFactory);
			return G3D_ERROR;
		}

		SAFE_RELEASE(dxgiFactory);
		SAFE_RELEASE(dxgiAdapter);
		SAFE_RELEASE(dxgiDevice);

		//Create our BackBuffer
		ID3D11Texture2D* BackBuffer;
		Result = SwapChain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
		if (FAILED(Result))
			return G3D_ERROR;

		//Create our Render Target
		Result = Device->CreateRenderTargetView(BackBuffer, NULL, &RenderTargetView);
		if (FAILED(Result))
			return G3D_ERROR;

		SAFE_RELEASE(BackBuffer);

		//Create our depth stencil state
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
		depthStencilDesc.Width = Settings::Display::Width;
		depthStencilDesc.Height = Settings::Display::Height;
		depthStencilDesc.MipLevels = 1u;
		depthStencilDesc.ArraySize = 1u;
		depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilDesc.SampleDesc.Count = scd.SampleDesc.Count;
		depthStencilDesc.SampleDesc.Quality = scd.SampleDesc.Quality;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
		ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		depthStencilStateDesc.DepthEnable = TRUE;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		depthStencilStateDesc.StencilEnable = TRUE;
		depthStencilStateDesc.StencilReadMask = 0xFF;
		depthStencilStateDesc.StencilWriteMask = 0xFF;

		depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		Result = Device->CreateTexture2D(&depthStencilDesc, 0u, &DepthStencilBuffer);
		if (FAILED(Result))
			return G3D_ERROR;

		D3D11_DEPTH_STENCIL_VIEW_DESC DSVdesc;
		ZeroMemory(&DSVdesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		DSVdesc.Format = DXGI_FORMAT_D32_FLOAT;
		DSVdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		DSVdesc.Texture2D.MipSlice = 0u;

		Result = Device->CreateDepthStencilState(&depthStencilStateDesc, &DepthStencilState);
		if (FAILED(Result))
			return G3D_ERROR;

		Result = Device->CreateDepthStencilView(DepthStencilBuffer, &DSVdesc, &DepthStencilView);
		if (FAILED(Result))
			return G3D_ERROR;

		Context->OMSetRenderTargets(1u, &RenderTargetView, DepthStencilView);
		Context->OMSetDepthStencilState(DepthStencilState, 1u);

		//Set Default Rasterizer State
		D3D11_RASTERIZER_DESC RastDesc;
		ZeroMemory(&RastDesc, sizeof(D3D11_RASTERIZER_DESC));
		RastDesc.FillMode = D3D11_FILL_SOLID;
		RastDesc.CullMode = D3D11_CULL_NONE;
		RastDesc.MultisampleEnable = Settings::Graphics::MSAA;
		RastDesc.AntialiasedLineEnable = Settings::Graphics::MSAA;

		Result = Device->CreateRasterizerState(&RastDesc, &RasterizerState);
		if (FAILED(Result))
			return G3D_ERROR;

		Context->RSSetState(RasterizerState);

		//Create our viewport
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		viewport.Width = Settings::Display::Width;
		viewport.Height = Settings::Display::Height;
		viewport.TopLeftX = 0u;
		viewport.TopLeftY = 0u;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		Context->RSSetViewports(1u, &viewport);

		//Set fullscreen state
		if (!Settings::Display::Windowed)
			Result = SwapChain->SetFullscreenState(true, 0u);
		if (FAILED(Result))
			return G3D_ERROR;


		return G3D_OK;
	}

	void Renderer::Shutdown()
	{
		SwapChain->SetFullscreenState(false, 0u);

		SAFE_RELEASE(Device);
		SAFE_RELEASE(Context);
		SAFE_RELEASE(SwapChain);
		SAFE_RELEASE(RenderTargetView);
		SAFE_RELEASE(RasterizerState);
		SAFE_RELEASE(DepthStencilState);
		SAFE_RELEASE(DepthStencilBuffer);
		SAFE_RELEASE(DepthStencilView);
	}
}