#ifndef CLIENT_H
#define CLIENT_H

#include <QLabel>
#include <QDataStream>
#include <QDialog>
#include <QTcpSocket>

class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
class QNetworkSession;

class Client : public QLabel
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);

private slots:
    void requestNewFortune();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);
    // void enableGetFortuneButton();
    void sessionOpened();

private:
    // QComboBox *hostCombo = nullptr;
    // QLineEdit *portLineEdit = nullptr;
    // QLabel *statusLabel = nullptr;
    // QPushButton *getFortuneButton = nullptr;

    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    // QString currentFortune;
    QPixmap currentFortune;

    QNetworkSession *networkSession = nullptr;
};

#endif
