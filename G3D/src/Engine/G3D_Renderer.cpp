#include "Engine/G3D_Renderer.h"
#include "Engine/G3D_Assert.h"

#ifdef _DEBUG
UINT debugFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
UINT debugFlags = 0u;
#endif

internal bool
RendererInitialize(renderer* Renderer)
{
	ASSERT(Renderer);
	HRESULT Result = 0u;

	//Create our Device
	D3D_FEATURE_LEVEL featureLevel;
	Result = D3D11CreateDevice(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		debugFlags,
		0, 0,
		D3D11_SDK_VERSION,
		&Renderer->Device,
		&featureLevel,
		&Renderer->Context
	);
	if (FAILED(Result))
		return false;

	//Check for MSAA quality support
	UINT m4xMsaaQuality = 0u;
	Result = Renderer->Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4u, &m4xMsaaQuality);
	if (FAILED(Result))
		return false;

	ASSERT(m4xMsaaQuality > 0u);

	IDXGIDevice* dxgiDevice = 0u;
	Result = Renderer->Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	if (FAILED(Result))
		return false;

	IDXGIAdapter* dxgiAdapter = 0u;
	Result = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
	if (FAILED(Result))
		return false;

	IDXGIFactory* dxgiFactory;
	Result = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
	if (FAILED(Result))
		return false;

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
	if (Renderer->Enable4xMsaa)
	{
		scd.SampleDesc.Count = 4u;
		scd.SampleDesc.Quality = m4xMsaaQuality - 1u;
	}
	else
	{
		scd.SampleDesc.Count = 1u;
		scd.SampleDesc.Quality = 0u;
	}
	scd.Windowed = Settings::Display::Windowed;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	if(Renderer->Enable4xMsaa)
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	else
		scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	//Create swap chain
	Result = dxgiFactory->CreateSwapChain(Renderer->Device, &scd, &Renderer->SwapChain);
	if (FAILED(Result))
		return false;

	dxgiFactory->Release();
	dxgiFactory = 0u;

	dxgiDevice->Release();
	dxgiDevice = 0u;

	dxgiAdapter->Release();
	dxgiAdapter = 0u;

#if 1
	if (!Settings::Display::Windowed)
		Result = Renderer->SwapChain->SetFullscreenState(true, 0u);
	if (FAILED(Result))
		return false;
#endif

	//Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	Result = Renderer->SwapChain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	if (FAILED(Result))
		return false;

	//Create our Render Target
	Result = Renderer->Device->CreateRenderTargetView(BackBuffer, NULL, &Renderer->RenderTargetView);
	if (FAILED(Result))
		return false;

	BackBuffer->Release();

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

	Result = Renderer->Device->CreateTexture2D(&depthStencilDesc, 0u, &Renderer->DepthStencilBuffer);
	if (FAILED(Result))
		return false;

	D3D11_DEPTH_STENCIL_VIEW_DESC DSVdesc;
	ZeroMemory(&DSVdesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	DSVdesc.Format = DXGI_FORMAT_D32_FLOAT;
	DSVdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	DSVdesc.Texture2D.MipSlice = 0u;

	Result = Renderer->Device->CreateDepthStencilState(&depthStencilStateDesc, &Renderer->DepthStencilState);
	if (FAILED(Result))
		return false;

	Result = Renderer->Device->CreateDepthStencilView(Renderer->DepthStencilBuffer, &DSVdesc, &Renderer->DepthStencilView);
	if (FAILED(Result))
		return false;

	Renderer->Context->OMSetRenderTargets(1u, &Renderer->RenderTargetView, Renderer->DepthStencilView);
	Renderer->Context->OMSetDepthStencilState(Renderer->DepthStencilState, 1u);

	//Set Default Rasterizer State
	D3D11_RASTERIZER_DESC RastDesc;
	ZeroMemory(&RastDesc, sizeof(D3D11_RASTERIZER_DESC));
	RastDesc.FillMode = D3D11_FILL_SOLID;
	RastDesc.CullMode = D3D11_CULL_NONE;
	RastDesc.MultisampleEnable = true;
	RastDesc.AntialiasedLineEnable = true;

	Result = Renderer->Device->CreateRasterizerState(&RastDesc, &Renderer->RasterizerState);
	if (FAILED(Result))
		return false;

	Renderer->Context->RSSetState(Renderer->RasterizerState);

	//Create our viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Width = Settings::Display::Width;
	viewport.Height = Settings::Display::Height;
	viewport.TopLeftX = 0u;
	viewport.TopLeftY = 0u;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	Renderer->Context->RSSetViewports(1u, &viewport);

	//@Temp: All this is doing is getting the video card information. Stuff like memory, vendorID, etc, etc
	//However, it needs to be moved elsewhere!!
	IDXGIAdapter* adapter = 0u;
	DXGI_OUTPUT_DESC outputDesc;
	IDXGIOutput* pOutput = 0u;
	DXGI_ADAPTER_DESC desc;
	IDXGIFactory* pDXGIFactory = 0u;

	Result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pDXGIFactory));
	if (FAILED(Result))
		return false;

	Result = pDXGIFactory->EnumAdapters(0u, &adapter);
	if (FAILED(Result))
		return false;

	Result = adapter->GetDesc(&desc);
	if (FAILED(Result))
		return false;

	Result = adapter->EnumOutputs(0u, &pOutput);
	if (FAILED(Result))
		return false;

	Result = pOutput->GetDesc(&outputDesc);
	if (FAILED(Result))
		return false;

	adapter->Release();
	adapter = 0u;

	pOutput->Release();
	pOutput = 0u;

	pDXGIFactory->Release();
	pDXGIFactory = 0u;

	return true;
}

internal void
RendererClear(renderer* Renderer, DirectX::XMFLOAT4 color)
{
	ASSERT(Renderer);

	local_persist const float clearColor[4] = { color.x, color.y, color.z, color.w };
	Renderer->Context->ClearRenderTargetView(Renderer->RenderTargetView, clearColor);
	Renderer->Context->ClearDepthStencilView(Renderer->DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
}

internal void 
RendererClear(renderer* Renderer, float r, float g, float b, float a)
{
	ASSERT(Renderer);

	local_persist const float clearColor[4] = { r, g, b, a };
	Renderer->Context->ClearRenderTargetView(Renderer->RenderTargetView, clearColor);
	Renderer->Context->ClearDepthStencilView(Renderer->DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
}

internal void
RendererPresent(renderer* Renderer)
{
	ASSERT(Renderer);

	HRESULT Result = 0;
	Result = Renderer->SwapChain->Present(Settings::Display::VSync, 0u);
	if (FAILED(Result))
	{
		//@NOTE This shouldn't actually fail, but maybe in the future recreate the renderer
		//if it does.
	}
}

internal void
RendererShutdown(renderer* Renderer)
{
	ASSERT(Renderer);

	Renderer->SwapChain->SetFullscreenState(false, 0u);

	if (Renderer->Device)
	{
		Renderer->Device->Release();
		Renderer->Device = 0u;
	}

	if (Renderer->Context)
	{
		Renderer->Context->Release();
		Renderer->Context = 0u;
	}

	if (Renderer->SwapChain)
	{
		Renderer->SwapChain->Release();
		Renderer->SwapChain = 0u;
	}

	if (Renderer->RenderTargetView)
	{
		Renderer->RenderTargetView->Release();
		Renderer->RenderTargetView = 0u;
	}

	if (Renderer->RasterizerState)
	{
		Renderer->RasterizerState->Release();
		Renderer->RasterizerState = 0u;
	}

	if (Renderer->DepthStencilState)
	{
		Renderer->DepthStencilState->Release();
		Renderer->DepthStencilState = 0u;
	}

	if (Renderer->DepthStencilBuffer)
	{
		Renderer->DepthStencilBuffer->Release();
		Renderer->DepthStencilBuffer = 0u;
	}

	if (Renderer->DepthStencilView)
	{
		Renderer->DepthStencilView->Release();
		Renderer->DepthStencilView = 0u;
	}
}