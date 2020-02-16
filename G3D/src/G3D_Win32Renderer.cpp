#include "G3D_Win32Renderer.h"
#include "G3D_Assert.h"

#ifdef _DEBUG
UINT debugFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
UINT debugFlags = 0u;
#endif

internal bool
RendererInitialize(Win32Renderer* Renderer)
{
	ASSERT(Renderer != nullptr);
	HRESULT Result = 0u;

	//Create our swap chain buffer description
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Width = Settings::Display::Width;
	bufferDesc.Height = Settings::Display::Height;
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
	scd.SampleDesc.Count = 1u;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = Settings::Display::Windowed;
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//Create our swap chain and device
	Result = D3D11CreateDeviceAndSwapChain(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		debugFlags,
		0,
		0u,
		D3D11_SDK_VERSION,
		&scd,
		&Renderer->SwapChain,
		&Renderer->Device,
		0,
		&Renderer->Context
	);

	if (FAILED(Result))
		return false;

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

	Renderer->Context->RSSetViewports(1, &viewport);

	//@Temp: All this is doing is getting the video card information. Stuff like memory, vendorID, etc, etc
	//However, it needs to be moved elsewhere!!
	IDXGIAdapter* adapter = nullptr;
	DXGI_OUTPUT_DESC outputDesc;
	IDXGIOutput* pOutput = nullptr;
	DXGI_ADAPTER_DESC desc;
	IDXGIFactory* pDXGIFactory = nullptr;

	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pDXGIFactory));

	Result = pDXGIFactory->EnumAdapters(0, &adapter);
	if (FAILED(Result)) // DXGIERR_NOT_FOUND is expected when the end of the list is hit
		return false;

	Result = adapter->GetDesc(&desc);
	if (FAILED(Result))
		return false;

	Result = adapter->EnumOutputs(0, &pOutput);
	if (FAILED(Result))
		return false;

	Result = pOutput->GetDesc(&outputDesc);
	if (FAILED(Result))
		return false;

	adapter->Release();
	pOutput->Release();
	pDXGIFactory->Release();

	return true;
}

internal void
RendererClear(Win32Renderer* Renderer, DirectX::XMFLOAT4 color)
{
	ASSERT(Renderer != nullptr);

	const float clearColor[4] = { color.x, color.y, color.z, color.w };
	Renderer->Context->ClearRenderTargetView(Renderer->RenderTargetView, clearColor);
	Renderer->Context->ClearDepthStencilView(Renderer->DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
}

internal void
RendererPresent(Win32Renderer* Renderer)
{
	ASSERT(Renderer != nullptr);

	HRESULT Result = 0;
	Result = Renderer->SwapChain->Present(Settings::Display::VSync, 0u);
	if (FAILED(Result))
	{
		//@NOTE This shouldn't actually fail, but maybe in the future recreate the renderer
		//if it does.
	}
}

internal void
RendererShutdown(Win32Renderer* Renderer)
{
	ASSERT(Renderer != nullptr);

	if(Renderer->Device)
		Renderer->Device->Release();

	if (Renderer->Context)
		Renderer->Context->Release();

	if (Renderer->SwapChain)
		Renderer->SwapChain->Release();

	if (Renderer->RenderTargetView)
		Renderer->RenderTargetView->Release();

	if (Renderer->RasterizerState)
		Renderer->RasterizerState->Release();

	if (Renderer->DepthStencilState)
		Renderer->DepthStencilState->Release();

	if (Renderer->DepthStencilBuffer)
		Renderer->DepthStencilBuffer->Release();

	if (Renderer->DepthStencilView)
		Renderer->DepthStencilView->Release();
}