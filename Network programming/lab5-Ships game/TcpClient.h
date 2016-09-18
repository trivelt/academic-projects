#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "TcpSocket.h"

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = 0);
    TcpSocket* connect(QString address, int port);
    
signals:
    
public slots:

private:
    void writeZeroIntoStructures(bool withServerStruct);
    void configureServerSocket(QString address, int port);
    void setAddressOnSocketStructure(const char* address);
    void createSocket();
    void connectToSocket();

    struct sockaddr_in serverStruct;
    int clientSocket;
    char buffer[4096];
    
};

#endif // TCPCLIENT_H
