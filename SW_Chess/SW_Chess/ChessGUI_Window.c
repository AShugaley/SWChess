#include <stdlib.h>
#include "ChessGUI_Window.h"

void destroyWindow(ChessWindow* src)
{
	if(!src)
		return;
	
	if(src->prevWindow)
		src->destroyWindow(src->prevWindow);

	src->destroyWindow(src);
}




