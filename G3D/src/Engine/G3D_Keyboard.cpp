#include "G3D_Keyboard.h"

namespace G3D
{
	Keyboard::Event Keyboard::ReadKey()
	{
		if (keyBuffer.size() > 0u)
		{
			Keyboard::Event e = keyBuffer.front();
			keyBuffer.pop();
			return e ;
		}
		else
			return Keyboard::Event();
	}

	u16 Keyboard::ReadChar()
	{
		if (charBuffer.size() > 0u)
		{
			u16 charcode = charBuffer.front();
			charBuffer.pop();

			return charcode;
		}
		else
			return 0;
	}
}