#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CMT.h"

namespace Ui {
class MainWindow;
}

struct MouseClickEvent
{
    int x;
    int y;
    bool handled;
};

Q_DECLARE_METATYPE(MouseClickEvent)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(SDL_Surface* screen);
    ~MainWindow();
    void handleResults(const unsigned char* pixels, unsigned int size);
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Ui::MainWindow *ui;
    QPixmap image;
    int labx, laby, labh, labw;


signals:
    void mouseClickEvent(MouseClickEvent event);
};




#endif // MAINWINDOW_H
