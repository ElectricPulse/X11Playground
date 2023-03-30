#include <stdbool.h>
#include <stdlib.h>

#include <X11/Xlib.h>

bool init(
        Display **const display,
        int *const screen,
        Window *const window,
	unsigned int width,
	unsigned int height,
        GC *const gc
) {
        *display = XOpenDisplay(NULL);
	if(NULL == *display)
		return 1;

        *screen = DefaultScreen(*display);	

        const unsigned long black = BlackPixel(*display, *screen);
        const unsigned long white = WhitePixel(*display, *screen);
	
	*window = XCreateSimpleWindow(*display, DefaultRootWindow(*display), 0, 0, width, height, 0, black, white);	

        XSelectInput(*display, *window, ExposureMask);
            
        *gc = XCreateGC(*display, *window, 0, NULL);

        XSetForeground(*display, *gc, black);
        XSetBackground(*display, *gc, white);

        XMapWindow(*display, *window);

        XEvent event;
        XNextEvent(*display, &event);

	return 0;
}


