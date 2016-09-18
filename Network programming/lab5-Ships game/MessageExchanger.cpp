#include "MessageExchanger.h"

MessageExchanger::MessageExchanger(TcpSocket *socket, QObject *parent) :
    QObject(parent),
    socket(socket)
{
    qDebug() << "Message exchanger initialized";
}

void MessageExchanger::send(QString message)
{
    socket->send(message);
}

void MessageExchanger::runListiningLoop()
{
    while(1)
    {
        qDebug() << "Trying to receive";
        QString data = socket->receive();
        emit messageFromOpponent(data);
    }
}
