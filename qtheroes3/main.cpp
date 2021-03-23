#include "mainwindow.h"
#include <QApplication>
#include "CMT.h"

int main(int argc, char *argv[])
{
    // return 0;
    init_game(argc, argv);
    mainLoop();
    // removeGUI();
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    // return a.exec();
}
