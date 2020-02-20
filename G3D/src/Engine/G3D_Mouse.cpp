#include "G3D_Mouse.h"

bool mouse::Init()
{
	RAWINPUTDEVICE rid;
	ZeroMemory(&rid, sizeof(RAWINPUTDEVICE));
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0u;
	rid.hwndTarget = 0u;

	if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
		return -1;
}

mouse::Event mouse::Read()
{
	if (buffer.size() > 0u)
	{
		mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else

	{
		return mouse::Event();
	}
}

void mouse::OnMouseMove(u16 newX, u16 newY)
{
	x = newX;
	y = newY;

	buffer.push(mouse::Event(mouse::Event::Type::Move, *this));
	TrimBuffer();
}

void mouse::OnMouseMoveRaw(u16 newX, u16 newY)
{
	dx = newX;
	dy = newY;

	buffer.push(mouse::Event(mouse::Event::Type::RAW_MOVE, *this));
	TrimBuffer();
}