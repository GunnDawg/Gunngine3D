#pragma once

namespace G3D
{
	struct Window
	{
		HWND window_handle;
		WNDCLASSEX wc;
	};

	bool WindowInitialize(G3D::Window* Window);
	void WindowShutdown(G3D::Window* Window);
}