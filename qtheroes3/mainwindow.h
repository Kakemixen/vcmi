#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CMT.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(SDL_Surface* screen);
    ~MainWindow();
    void handleResults(const QString & res);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
