#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TcpSocket.h"
#include "GameBoardWidget.h"
#include "MessageExchanger.h"
#include "Logger.h"
#include "ShipsConfigurator.h"
#include "GameMessageProcessor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sigListen(QString, int);

public slots:
    void chooseServerMode();
    void chooseClientMode();
    void startGameAsServer();
    void startGameAsClient();
    void sendChatMessage();
    void startGameWhenUserShipsConfigured();
    void startGameWhenOpponentShipsConfigured();

    void newClient(TcpSocket* tcpSocket);
    void messageFromOpponent(QString message);
    void shoot();
    void sendMessageToOpponent(QString message);

    void yourTurn();
    void opponentTurn();

private:
    void configureStartScreen();
    void configureModeOptionsScreen();
    void configureGameScreen();
    void configureMessageExchanger(TcpSocket* socket);

    QString translateCoordsToGameCoords(int row, int column);

    Ui::MainWindow *ui;
    GameBoardWidget* userBoard;
    GameBoardWidget* opponentBoard;
    MessageExchanger* exchanger;
    Logger* logger;
    ShipsConfigurator* shipsWidget;
    GameMessageProcessor* gameProcessor;

    bool usersShipsConfigured;
    bool opponentsShipConfigured;

};

#endif // MAINWINDOW_H
