#include "G3D_Keyboard.h"

keyboard::Event keyboard::ReadKey()
{
	if (keyBuffer.size() > 0u)
	{
		keyboard::Event e = keyBuffer.front();
		keyBuffer.pop();
		return(e);
	}
	else
		return(keyboard::Event());
}

u16 keyboard::ReadChar()
{
	if (charBuffer.size() > 0u)
	{
		u16 charcode = charBuffer.front();
		charBuffer.pop();

		return(charcode);
	}
	else
		return(0);
}