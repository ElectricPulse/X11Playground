#include <stdbool.h>

bool init(
	Display **const display,
	int *const screen,
	Window *const window,
	unsigned int width,
	unsigned int height,
	GC *gc
);

void term(
	Display *display,
	Window window,
	GC gc
);
