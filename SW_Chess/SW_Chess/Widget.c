#include <stdlib.h>
#include "Widget.h"

void destroyWidget(Widget* src) {//Making NULL Safe Destroy
	if (!src)
		return;

	src->destroyWidget(src);
}
