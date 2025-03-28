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

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

