#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <QDebug>
#include "CMT.h"

class ImageThread : public QThread
{
    Q_OBJECT
    void run() override {
        mainLoop([this](SDL_Surface* screen){
            emit resultReady(screen);
        },
        [this](){
            SDL_MouseButtonEvent fake;

            if(!curr_mouse_event_.handled)
            {
                fake.button = SDL_BUTTON_LEFT;
                fake.x = curr_mouse_event_.x;
                fake.y = curr_mouse_event_.y;
                curr_mouse_event_.handled = true;
                return fake;
            }
            fake.x = -1;
            return fake;
        });
    }

private:
    bool handled;
    MouseClickEvent curr_mouse_event_;

public:
    void callback(SDL_Surface* screen);
    void handle_mouse(MouseClickEvent event){
        // qDebug() << event.x << " " << event.y;
        curr_mouse_event_ = event;
        curr_mouse_event_.handled = false;
    }

signals:
    void resultReady(SDL_Surface *screen);
};


int main(int argc, char *argv[])
{
    auto screen = init_game(argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    // MainWindow w(screen);

    ImageThread* img_thread =  new ImageThread;
    QObject::connect(img_thread, &ImageThread::resultReady, &w, &MainWindow::handleResults);
    QObject::connect(&w, &MainWindow::mouseClickEvent, img_thread, &ImageThread::handle_mouse);
    // connect(img_thread, &ImageThread::finished, img_thread, &QObject::deleteLater);
    img_thread->start();

    w.show();

    return a.exec();
}

#include "main.moc"
