#pragma once
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <iostream>


namespace KeyboardSimulator
{
    void simulateKeyPress(Display* display, Window window, char key);

} // namespace KeyboardSimulator
