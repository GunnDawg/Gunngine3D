#include "G3D_Mouse.h"

namespace G3D
{
	bool Mouse::Initialize()
	{
		RAWINPUTDEVICE rid;
		ZeroMemory(&rid, sizeof(RAWINPUTDEVICE));
		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = 0u;
		rid.hwndTarget = 0u;

		if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
		{
			MessageBox(nullptr, "Error registering RAW input device. Most likely a mouse", "RAW Input Startup Error", MB_OK);
			return G3D_ERROR;
		}

		DisableCursor();

		return G3D_OK;
	}

	Mouse::Event Mouse::Read()
	{
		if (buffer.size() > 0u)
		{
			Mouse::Event e = buffer.front();
			buffer.pop();
			return e;
		}
		else
		{
			return Mouse::Event();
		}
	}

	void Mouse::OnMouseMove(u16 newX, u16 newY)
	{
		x = newX;
		y = newY;

		buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
		TrimBuffer();
	}

	void Mouse::OnMouseMoveRaw(u16 newX, u16 newY)
	{
		if (RawMouseEnabled)
		{
			dx = newX;
			dy = newY;

			buffer.push(Mouse::Event(Mouse::Event::Type::RAW_MOVE, *this));
			TrimBuffer();
		}
	}
}