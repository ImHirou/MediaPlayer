#include "mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow() : QMainWindow(nullptr) {
    bSizeX = 200;
    bSizeY = 40;
    button = new QPushButton("Click me", this);
    button->resize(bSizeX, bSizeY);
    connect(button, &QPushButton::clicked, this,
        [this]() {
          bSizeX+=5;
          bSizeY+=10;
          button->resize(bSizeX, bSizeY);
        });
    button->show();
}
