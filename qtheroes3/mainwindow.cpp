#include <QDebug>
#include <QBitmap>
#include <QPixmap>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

void MainWindow::handleResults(const QString & res){
    qDebug() << res;
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
    QPixmap image;
    bool success = image.load("/home/joakim/vcmi/build/bin/Screen_c.bmp");
    if(!success)
    {
        std::cout << "THIS DID NOT WORK OMG REPORTED\n";
        exit(2);
    }
    ui->label->setPixmap(image);
}

MainWindow::~MainWindow()
{
    delete ui;
}
