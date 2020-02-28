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

		if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
			return false;

		if (Settings::Display::Windowed)
			EnableCursor();
		else
			DisableCursor();

		return true;
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
		dx = newX;
		dy = newY;

		buffer.push(Mouse::Event(Mouse::Event::Type::RAW_MOVE, *this));
		TrimBuffer();
	}
}