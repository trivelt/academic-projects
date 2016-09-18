#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocket(int socketDescriptor, QObject *parent = 0);
    void send(QString data);
    QString receive();
    void close();
    
signals:
    
public slots:

private:
    int socketDescriptor;
    char buffer[4096];

};

#endif // TCPSOCKET_H
