#ifndef SERVER_H_
#define SERVER_H_

#include <QObject>

QT_BEGIN_NAMESPACE
class QTcpServer;
class QNetworkSession;
class QTcpSocket;
class QTimer;
QT_END_NAMESPACE

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QString ipAddress, int port, QObject *parent = 0);

private slots:
    void newConnectionSlot();
    void sendSlot();

private:
    QTcpServer          *mTcpServer;
    QTcpSocket          *mTcpSocket;
    QTimer              *mSendTimer;
};

#endif /* SERVER_H_ */
