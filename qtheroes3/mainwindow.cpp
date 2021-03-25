#include <QMouseEvent>
#include <QDebug>
#include <QBitmap>
#include <QPixmap>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

void MainWindow::handleResults(const unsigned char* pixels, int width, int height){

    // While I guess I would like it if this worked, alas it does not
    // bool success = image.loadFromData(pixels, size, QImage::Format_RGB32);

    QImage tmp_img(pixels, width, height, QImage::Format_RGB32);
    bool success = image.convertFromImage(tmp_img);
    emit finishedBufferSwap();
    if(!success)
    {
        std::cout << "THIS DID NOT WORK OMG REPORTED\n";
        exit(2);
    }
    ui->label->setPixmap(image);
    labx = ui->label->x();
    laby = ui->label->y();
    labw = ui->label->width();
    labh = ui->label->height();

}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    std::cout << labx << ", " << laby << ", " << labw << ", " << labh << "\n";
    MouseClickEvent event_ {
        event->x() - labx,
        event->y() - laby - 22,
        false,
    };

    emit mouseClickEvent(event_);   

    QMainWindow::mouseReleaseEvent(event);
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

