#include <X11/Xlib.h>

void term(
        Display *const display,
        Window window,
        const GC gc
) {
        XEvent event;
        XNextEvent(display, &event);
        
        XFreeGC(display, gc);
        XDestroyWindow(display, window);
        XCloseDisplay(display);

}

