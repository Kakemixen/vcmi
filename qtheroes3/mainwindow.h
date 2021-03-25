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
    ~MainWindow();
    void handleResults(const unsigned char* pixels, int width, int height);
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Ui::MainWindow *ui;
    QPixmap image;
    int labx, laby, labh, labw;


signals:
    void mouseClickEvent(MouseClickEvent event);
    bool finishedBufferSwap();
};




#endif // MAINWINDOW_H
