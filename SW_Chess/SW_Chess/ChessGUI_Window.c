#include <stdlib.h>
#include "ChessGUI_Window.h"

void destroyWindow(ChessWindow* src)
{
	if(!src)
		return;
	
	destroyChessGame(src->game);

	if(src->prevWindow)
		src->destroyWindow(src->prevWindow);

	src->destroyWindow(src);
}




