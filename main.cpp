#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

int main() {
    Display *d = XOpenDisplay(NULL);
    int s = DefaultScreen(d);
    Window w = XCreateSimpleWindow(d, RootWindow(d, s), 100, 100, 400, 400, 1, BlackPixel(d, s), WhitePixel(d, s));
    
    XFontStruct *font = XLoadQueryFont(d, "fixed");
    if (!font) font = XLoadQueryFont(d, "10x20"); 
    
    GC gc = XCreateGC(d, w, 0, NULL);
    if (font) XSetFont(d, gc, font->fid);
    
    XSelectInput(d, w, ExposureMask | ButtonPressMask);
    XMapWindow(d, w);
    
    XEvent e;
    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            XDrawRectangle(d, w, gc, 150, 120, 40, 25);  
            XDrawString(d, w, gc, 158, 138, "Exit", 4);
        }
        if (e.type == ButtonPress) break;  
    }
    
    XCloseDisplay(d);
    return 0;
}
