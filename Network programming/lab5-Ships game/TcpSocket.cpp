#include "TcpSocket.h"
#include <QDebug>

TcpSocket::TcpSocket(int socketDescriptor, QObject *parent) :
    QObject(parent)
{
    this->socketDescriptor = socketDescriptor;
}

void TcpSocket::send(QString data)
{
    const char* messageToSend = data.toStdString().c_str();
    bzero( buffer, sizeof( buffer ) );
    strcpy( buffer, messageToSend);
    if(( ::send( socketDescriptor, buffer, strlen( buffer ), 0 ) ) <= 0 )
    {
        throw "send() ERROR";
    }
}


QString TcpSocket::receive()
{
    bzero(buffer, sizeof( buffer ) );

    int receivedBytes = recv( socketDescriptor, buffer, sizeof( buffer ), 0 );
    if(receivedBytes <= 0 )
    {
        throw "recv() ERROR";
    }
    return QString(buffer).mid(0, receivedBytes);
}

void TcpSocket::close()
{
::close(socketDescriptor);
}
