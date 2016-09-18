#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "TcpSocket.h"

#define MAX_MSG_LEN 4096

enum
{
    CLIENT,
    SERVER
};

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    
signals:
    void newConnection(TcpSocket* clientSocket);
    void informUi(QString);
    
public slots:
    void listen(QString address, int port);
    void stop();

private:
    void writeZeroIntoStructures(int mode);
    void configureServerSocket(QString address, int port);
    void setAddressOnSocketStructure(const char* address);
    void createSocket();
    void bindSocket();
    void setListeningOnSocket();
    void runListeningLoop();
    void acceptConnection();

    struct sockaddr_in serverStruct;
    struct sockaddr_in clientStruct;
    char buffer[MAX_MSG_LEN];
    int serverSocket;
    int clientSocket;

};

#endif // TCPSERVER_H
