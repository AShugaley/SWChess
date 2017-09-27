#include <stdio.h>
#include <stdlib.h>

#include "Chess_ConsoleFlowMain.h"
#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>

#include "unitTest.h"
#include "Chess_gameParser.h"
#include "Chess_gameSettingsParser.h"
#include "Chess_ArrayList.h"
#include "Chess_GUIFlowMain.h"


int main(int argc, const char* argv[])
{

	//if (argc == 2 && strcmp(argv[1], "-g") == 0)
		return GUIMain();
	//else
		//consoleMode();

	return 0;
}





