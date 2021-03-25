#include "StdInc.h"

#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <QDebug>
#include "CMT.h"
#include <SDL.h>
#include <iostream>

#include "gui/CGuiHandler.h"
extern CGuiHandler GH;
#include "CServerHandler.h"
extern CServerHandler* CSH;


class ImageThread : public QThread
{
    Q_OBJECT
    void run() override {

        GH.mainFPSmng->init();
        bufferSwapped = true;

        unsigned int size = screen->w * screen->pitch;
        unsigned char* qt_pixels = new unsigned char[size]; 
        //std::cout << ((long*)qt_pixels[0]) << "!\n";

        while(1) //main SDL events loop
        {
            SDL_Event ev;

            while(1 == SDL_PollEvent(&ev))
            {
                handleEvent(ev);
            }

            /*
             * create fake event
             */
            if(!curr_mouse_event_.handled)
            {
                SDL_Event fake;
                fake.button.type = SDL_MOUSEBUTTONDOWN;
                fake.button.button = SDL_BUTTON_LEFT;
                fake.button.x = curr_mouse_event_.x;
                fake.button.y = curr_mouse_event_.y;
                curr_mouse_event_.handled = true;

                SDL_Event fake2;
                fake2.type = SDL_MOUSEMOTION;
                fake2.motion.x = fake.button.x;
                fake2.motion.y = fake.button.y;
                std::cout << fake2.motion.x << ", " << fake2.motion.y << "\n\n\n\n";
                handleEvent(fake2);

                fake.motion.x = fake.button.x;
                fake.motion.y = fake.button.y;
                std::cout << fake.type << "\n";
                handleEvent(fake);

                SDL_Event fake3;
                fake3.button = fake.button;
                fake3.motion.x = fake.button.x;
                fake3.motion.y = fake.button.y;
                fake3.type = SDL_MOUSEBUTTONUP;
                std::cout << fake3.type << "\n";
                handleEvent(fake3);
                // fake.button.x = -1;
            }

            CSH->applyPacksOnLobbyScreen();
            GH.renderFrame();

            while(!bufferSwapped){} // avoid bus error

            SDL_LockSurface(screen);
            //SDL_SaveBMP(screen, "/tmp/Screen_homm3.bmp");
            void* sdl_pixels = screen->pixels;
            memcpy(qt_pixels, sdl_pixels, size);
            emit resultReady(qt_pixels, size);
            SDL_UnlockSurface(screen);
        }
    }

private:
    bool bufferSwapped;
    MouseClickEvent curr_mouse_event_;

public:
    void handle_mouse(MouseClickEvent event){
        // qDebug() << event.x << " " << event.y;
        curr_mouse_event_ = event;
    }
    void handleFinishedBufferSwap(){
        bufferSwapped = true;
    }

signals:
    void resultReady(const unsigned char* pixels, unsigned int size);
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
