#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <iostream>

#include "KeyboardSimulator.hpp"

void KeyboardSimulator::simulateKeyPress(Display* display, Window window, char key) {
    // Convert the character to a keycode
    KeySym keySym = XStringToKeysym(std::string(1, key).c_str());  // Convert char to string and then to KeySym
    if (keySym == NoSymbol) {
        std::cerr << "Invalid key symbol" << std::endl;
        return;
    }

    // Create and configure key press and key release events
    XKeyEvent keyPressEvent;
    keyPressEvent.display = display;
    keyPressEvent.window = window;
    keyPressEvent.root = XRootWindow(display, 0);
    keyPressEvent.subwindow = None;
    keyPressEvent.time = CurrentTime;
    keyPressEvent.x = 0;
    keyPressEvent.y = 0;
    keyPressEvent.x_root = 0;
    keyPressEvent.y_root = 0;
    keyPressEvent.state = 0;
    keyPressEvent.keycode = keySym;
    keyPressEvent.type = KeyPress;

    XKeyEvent keyReleaseEvent = keyPressEvent;
    keyReleaseEvent.type = KeyRelease;

    // Simulate key press and release
    XSendEvent(display, window, True, KeyPressMask, (XEvent*)&keyPressEvent);
    XFlush(display); // Flush the event queue
    usleep(10000); // Small delay for the key press to register
    XSendEvent(display, window, True, KeyReleaseMask, (XEvent*)&keyReleaseEvent);
    XFlush(display); // Flush again to release the key
}