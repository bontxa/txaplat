#include "include/getScreenResolution.h"
#ifdef __linux__
#include <X11/Xlib.h>

int getScreenResolution() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Can't open server X connection\n");
        return 2;
    }

    int screenWidth = DisplayWidth(display, DefaultScreen(display));
    int screenHeight = DisplayHeight(display, DefaultScreen(display));

    if (screenWidth < 1920 || screenHeight < 1080) {

        fprintf(stderr, "Screen resolution must be at least 1920x1080\n");
        printf("Your screen resolution is %dx%d\n", screenWidth, screenHeight);
        XCloseDisplay(display);
        return 1;
    }

    XCloseDisplay(display);

    return 0;
}

#elif defined(_WIN32)
#include <windows.h>
int getScreenResolution() {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    if (screenWidth < 1920 || screenHeight < 1080) {

        fprintf(stderr, "Screen resolution must be at least 1920x1080\n");
        printf("Your screen resolution is %dx%d\n", screenWidth, screenHeight);
        return 1;
    }
    
    return 0;
}
#endif