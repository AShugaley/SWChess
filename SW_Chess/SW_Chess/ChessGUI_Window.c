#include <stdlib.h>
#include "ChessGUI_Window.h"

void destroyWindow(ChessWindow* src)
{
	if(!src)
		return;
	src->destroyWindow(src);
}




