#ifndef MESSAGEEXCHANGER_H
#define MESSAGEEXCHANGER_H

#include <QObject>
#include <QDebug>
#include "TcpSocket.h"

class MessageExchanger : public QObject
{
    Q_OBJECT
public:
    explicit MessageExchanger(TcpSocket* socket, QObject *parent = 0);
    
signals:
    void messageFromOpponent(QString message);
    
public slots:
    void send(QString message);
    void runListiningLoop();

private:

    TcpSocket* socket;
    
};

#endif // MESSAGEEXCHANGER_H
