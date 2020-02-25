#pragma once

struct window
{
	HWND window_handle;
	WNDCLASSEX wc;
};

bool WindowInitialize(window* Window);
void WindowShutdown(window* Window);