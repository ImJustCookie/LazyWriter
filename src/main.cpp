#include <iostream>
#include <string>
#include <unistd.h>
#include <random>
#include <bits/stdc++.h>
#include <functional>

#include <QApplication>
#include <QDialog>
#include <QPushButton>

#include "lorem.hpp"
#include "Window.hpp"
#include "writer.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(600, 400);
    window.show();
    return app.exec();
}