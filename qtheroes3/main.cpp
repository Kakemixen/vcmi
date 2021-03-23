#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include "CMT.h"

class ImageThread : public QThread
{
    Q_OBJECT
    void run() override {
        mainLoop([this](SDL_Surface* screen){
            QString test{"I am alive!"};
            emit resultReady(test);
        });
        // while(true)
        // {
        //     QString test{"I am alive!"};
        //     emit resultReady(test);
        // }
    }

public:
    void callback(SDL_Surface* screen);

signals:
    void resultReady(const QString &str);
};

int main(int argc, char *argv[])
{
    auto screen = init_game(argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    // MainWindow w(screen);

    ImageThread* img_thread =  new ImageThread;
    QObject::connect(img_thread, &ImageThread::resultReady, &w, &MainWindow::handleResults);
    // connect(img_thread, &ImageThread::finished, img_thread, &QObject::deleteLater);
    img_thread->start();

    w.show();

    return a.exec();
}

#include "main.moc"
