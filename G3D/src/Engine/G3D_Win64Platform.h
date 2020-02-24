#pragma once
#include "Engine/G3D_Windows.h"
#include "Game/Game.h"
//@Temp: We're only using 'stdio.h' to output our telemtery data, and should look for
//better ways to handle that in the future
#include <stdio.h>

struct game_data
{
	renderer Renderer;
	keyboard Keyboard;
	mouse Mouse;
	game Game;
};