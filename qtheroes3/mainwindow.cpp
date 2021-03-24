#include <QMouseEvent>
#include <QDebug>
#include <QBitmap>
#include <QPixmap>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

void MainWindow::handleResults(SDL_Surface* screen){
    // qDebug() << "got frame";
    // bool success = image.loadFromData((const uchar*) screen->pixels, screen->h * screen->pitch);
    bool success = image.load("/tmp/Screen_homm3.bmp");
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
        event->x() - 11,
        event->y() - 11 - 22,
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

MainWindow::MainWindow(SDL_Surface* screen) :
    QMainWindow(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // QPixmap image("~/vcmi/build/bin/Screen_c.bmp"); 
    // QPixmap image;
//     bool success = image.load("/home/joakim/vcmi/build/bin/Screen_c.bmp");
//     if(!success)
//     {
//         std::cout << "THIS DID NOT WORK OMG REPORTED\n";
//         exit(2);
//     }
//     ui->label->setPixmap(image);
}

MainWindow::~MainWindow()
{
    delete ui;
}
