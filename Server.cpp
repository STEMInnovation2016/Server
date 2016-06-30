#include "Server.h"
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QDateTime>
#include <QSettings>
#include <QFile>
#include <QProcess>

Server::Server(QString ipAddress, int port, QObject *parent) :
    QObject(parent), mTcpServer(0), mTcpSocket(0)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));
    if (!mTcpServer->listen(QHostAddress(ipAddress), port)) {
        std::cout << "Unable to start the server: " << mTcpServer->errorString().toStdString() << std::endl;
        return;
    }

    std::cout << "The server is running on\n\nIP: "<< ipAddress.toStdString()
            << "\nport: " << mTcpServer->serverPort() << "\n\nRun the Client now.\n" << std::endl;
}

void Server::newConnectionSlot()
{
    mTcpSocket = mTcpServer->nextPendingConnection();
    connect(mTcpSocket, SIGNAL(disconnected()),
            mTcpSocket, SLOT(deleteLater()));

    // setup timer to send data at a given interval
    mSendTimer = new QTimer(this);
    connect(mSendTimer, SIGNAL(timeout()),
            this, SLOT(sendSlot()));
    mSendTimer->start(40);
}

void Server::sendSlot()
{
    if(!mTcpSocket)
        return;

    qint64 blockSize = 9600; //in bytes

    qint64 imagesInQue = mTcpSocket->bytesToWrite()/blockSize;
    int maxPendingImages = 25;
    if(imagesInQue > maxPendingImages)
    {
        std::cout << "Dumping." << std::endl;
        return;
    }

    QProcess process;
    process.start("./frame.exe");
    process.waitForFinished();

    QFile in("lepton.dat");
    in.open(QIODevice::ReadOnly);
    QByteArray data = in.readAll();
quint64 written = mTcpSocket->write(data);
}

