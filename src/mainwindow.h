#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;

class MainWindow : public QMainWindow {
Q_OBJECT
private:
  QPushButton* button;
  int bSizeX;
  int bSizeY;
public: 
    MainWindow();
    ~MainWindow() = default;
};

#endif // ! MAINWINDOW_H
