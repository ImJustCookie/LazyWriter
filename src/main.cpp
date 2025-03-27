#include <iostream>
#include <string>
#include <unistd.h>
#include <random>
#include <bits/stdc++.h>
#include <functional>

#include <QApplication>

#include "lorem.hpp"
#include "Window.hpp"
#include "writer.hpp"
#include <X11/Xlib.h>
#include "KeyboardSimulator.hpp"

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);
//     MainWindow window;
//     window.show();
//     return app.exec();
// }

int main() {
    // Open X display
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Unable to open X display" << std::endl;
        return -1;
    }
    sleep(5);
    // Get the root window (or you can use a specific window ID)
    Window rootWindow = DefaultRootWindow(display);

    // Simulate pressing the 'A' key
    KeyboardSimulator::simulateKeyPress(display, rootWindow, 'A');

    // Close the display connection
    XCloseDisplay(display);

    return 0;
}
