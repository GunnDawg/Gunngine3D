#include "G3D_Keyboard.h"

bool G3D::Keyboard::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}

std::optional<G3D::Keyboard::Event> G3D::Keyboard::ReadKey() noexcept
{
	if (keybuffer.size() > 0u)
	{
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	return {};
}

bool G3D::Keyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

std::optional<char> G3D::Keyboard::ReadChar() noexcept
{
	if (charbuffer.size() > 0u)
	{
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	return {};
}

bool G3D::Keyboard::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void G3D::Keyboard::FlushKey() noexcept
{
	keybuffer = std::queue<Event>();
}

void G3D::Keyboard::FlushChar() noexcept
{
	charbuffer = std::queue<char>();
}

void G3D::Keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void G3D::Keyboard::EnableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void G3D::Keyboard::DisableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool G3D::Keyboard::AutorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

void G3D::Keyboard::OnKeyPressed(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
	TrimBuffer(keybuffer);
}

void G3D::Keyboard::OnKeyReleased(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
	TrimBuffer(keybuffer);
}

void G3D::Keyboard::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void G3D::Keyboard::ClearState() noexcept
{
	keystates.reset();
}

template<typename T>
void G3D::Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}

