#include <iostream>
#include <QCoreApplication>
#include "Server.h"

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    QString ipaddress = QString(argv[1]);
    int port = atoi(argv[2]);
    Server* server = new Server(ipaddress, port);
    int retVal = app.exec();
    return retVal;
}
