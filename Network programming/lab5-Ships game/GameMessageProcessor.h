#ifndef GAMEMESSAGEPROCESSOR_H
#define GAMEMESSAGEPROCESSOR_H

#include <QObject>
#include "GameBoardWidget.h"
#include "Ship.h"

class GameMessageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit GameMessageProcessor(QObject *parent = 0);
    void processMessage(QString message);
    void setUserGameBoard(GameBoardWidget* gameBoard);
    void setOpponentGameboard(GameBoardWidget* gameBoard);
    void setShips(QList<Ship*> ships);
    
signals:
    void log(QString);
    void sendMessage(QString);
    void opponentShipsConfigured();
    void yourTurn();
    
public slots:

private:
    void opponentShooted(QString message);

    QString getCoordinateFromShootMessage(QString message);
    QString getCoordinateFromHitMessage(QString message);
    QString getCoordinateFromHitAndSunkMessage(QString message);
    QString getCoordinateFromMishitMessage(QString message);

    void shipHitByOpponent(Ship* ship, QString coordinates);
    void userHitOpponentsShip(QString message);
    void userMishitOpponentsShip(QString message);

    GameBoardWidget* userBoard;
    GameBoardWidget* opponentBoard;
    QList<Ship*> userShips;
    
};

#endif // GAMEMESSAGEPROCESSOR_H
