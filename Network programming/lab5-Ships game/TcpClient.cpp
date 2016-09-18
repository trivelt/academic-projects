#include "TcpClient.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent) :
    QObject(parent)
{
}

TcpSocket* TcpClient::connect(QString address, int port)
{
    writeZeroIntoStructures(true);
    configureServerSocket(address, port);
    connectToSocket();
    TcpSocket* tcpClientSocket = new TcpSocket(clientSocket);
    return tcpClientSocket;
}

void TcpClient::writeZeroIntoStructures(bool withServerStruct)
{
    bzero(buffer, sizeof( buffer ) );
    if(withServerStruct)
        bzero(&serverStruct, sizeof( serverStruct ));
}

void TcpClient::configureServerSocket(QString address, int port)
{
    const char* serverIp = address.toStdString().c_str();
    serverStruct.sin_family = AF_INET;
    serverStruct.sin_port = htons(port);
    setAddressOnSocketStructure(serverIp);
    createSocket();
}


void TcpClient::setAddressOnSocketStructure(const char *address)
{
    if( inet_pton(AF_INET, address, &serverStruct.sin_addr) <= 0 )
    {
        qDebug() << "inet_pton ERROR";
        throw "inet_pton ERROR";
    }
}

void TcpClient::createSocket()
{
    if(( clientSocket = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
        qDebug() << "socket() ERROR";
        throw "socket() ERROR";
    }
}

void TcpClient::connectToSocket()
{
    socklen_t len = sizeof( serverStruct );
    if( ::connect( clientSocket,( struct sockaddr * ) & serverStruct, len ) < 0 )
    {
        qDebug() << "connect() ERROR";
        throw "connect() ERROR";
    }
}
