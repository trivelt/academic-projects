#include "TcpServer.h"
#include <QDebug>

TcpServer::TcpServer(QObject *parent) :
    QObject(parent)
{
}

void TcpServer::listen(QString address, int port)
{
    try
    {
        writeZeroIntoStructures(SERVER);
        configureServerSocket(address, port);
        bindSocket();
        setListeningOnSocket();
        runListeningLoop();
    }
    catch(...)
    {
        emit informUi("Error server");
        stop();
    }
}

void TcpServer::writeZeroIntoStructures(int mode)
{
    bzero(buffer, sizeof( buffer ) );
    if(mode == SERVER)
        bzero(&serverStruct, sizeof( serverStruct ));
    else if(mode == CLIENT)
        bzero(&clientStruct, sizeof( clientStruct ));
}

void TcpServer::configureServerSocket(QString address, int port)
{
    const char* serverIp = address.toStdString().c_str();
    serverStruct.sin_family = AF_INET;
    serverStruct.sin_port = htons(port);
    setAddressOnSocketStructure(serverIp);
    createSocket();
}

void TcpServer::setAddressOnSocketStructure(const char *address)
{
    if( inet_pton(AF_INET, address, &serverStruct.sin_addr) <= 0 )
    {
        throw "inet_pton ERROR";
    }
}

void TcpServer::createSocket()
{
    if(( serverSocket = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
        throw "socket() ERROR";
    }
}

void TcpServer::bindSocket()
{
    int yes = 1;
    if ( setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
    {
        throw "setsockopt() ERROR";
    }

    socklen_t length = sizeof(serverStruct);
    if( bind(serverSocket, (struct sockaddr*) &serverStruct, length ) < 0 )
    {
        qDebug() << "Bind problem";
        throw "bind() ERROR";
    }
}

void TcpServer::setListeningOnSocket()
{
    if( ::listen( serverSocket, 1 ) < 0 )
    {
        throw "listen() ERROR";
    }
}

void TcpServer::runListeningLoop()
{
        clientSocket = 0;
        emit informUi("Waiting for a client...");
        acceptConnection();
        writeZeroIntoStructures(CLIENT);

        TcpSocket* clientTcpSocket = new TcpSocket(clientSocket);
        emit newConnection(clientTcpSocket);
}

void TcpServer::acceptConnection()
{
    socklen_t len = sizeof(serverStruct);
    if(( clientSocket = accept(serverSocket, (struct sockaddr*) &clientStruct, &len )) < 0 )
    {
        throw "accept() ERROR";
    }
}

void TcpServer::stop()
{
    shutdown( clientSocket, SHUT_RDWR );
}
