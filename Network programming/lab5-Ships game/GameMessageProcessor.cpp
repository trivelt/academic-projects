#include "GameMessageProcessor.h"
#include <QDebug>

GameMessageProcessor::GameMessageProcessor(QObject *parent) :
    QObject(parent)
{
}

void GameMessageProcessor::processMessage(QString message)
{
    if(message.startsWith("/shoot"))
    {
        opponentShooted(message);
        emit yourTurn();
    }
    else if(message.startsWith("/hit"))
    {
        userHitOpponentsShip(message);
    }
    else if(message.startsWith("/mishit"))
    {
        userMishitOpponentsShip(message);
    }
    else if(message.startsWith("/configured"))
    {
        emit opponentShipsConfigured();
    }
}


void GameMessageProcessor::setUserGameBoard(GameBoardWidget *gameBoard)
{
    this->userBoard = gameBoard;
}

void GameMessageProcessor::setOpponentGameboard(GameBoardWidget *gameBoard)
{
    this->opponentBoard = gameBoard;
}

void GameMessageProcessor::setShips(QList<Ship *> ships)
{
    userShips = ships;
}

void GameMessageProcessor::opponentShooted(QString message)
{
    QString coordinates = getCoordinateFromShootMessage(message);
    bool shipHit = false;
    foreach(Ship* ship, userShips)
    {
        if(ship->contains(coordinates))
        {
            shipHitByOpponent(ship, coordinates);
            shipHit = true;
        }
    }
    if(shipHit == false)
    {
        emit log("Your opponent shot at " + coordinates + " and he mishit");
        emit sendMessage("/mishit " + coordinates);
        userBoard->setSymbol(coordinates, "-");
    }
}

QString GameMessageProcessor::getCoordinateFromShootMessage(QString message)
{
    QString coordinates = message.mid(7);
    return coordinates;
}

QString GameMessageProcessor::getCoordinateFromHitMessage(QString message)
{
    QString coordinates = message.mid(5);
    return coordinates;
}

QString GameMessageProcessor::getCoordinateFromHitAndSunkMessage(QString message)
{
    QString coordinates = message.mid(12);
    return coordinates;
}

QString GameMessageProcessor::getCoordinateFromMishitMessage(QString message)
{
    QString coordinates = message.mid(8);
    return coordinates;
}

void GameMessageProcessor::shipHitByOpponent(Ship *ship, QString coordinates)
{
    ship->hit(coordinates);
    userBoard->setSymbol(coordinates, "+");
    QString message = "Your ship ";
    message += ship->type();
    if(ship->isSunk())
    {
        emit log(message + " was hit and sunk by the opponent at " + coordinates);
        emit sendMessage("/hitandsunk " + coordinates);
    }
    else
    {
        emit log(message + " was hit by the opponent at " + coordinates);
        emit sendMessage("/hit " + coordinates);
    }
}

void GameMessageProcessor::userHitOpponentsShip(QString message)
{
    QString coordinates;
    if(message.startsWith("/hitandsunk"))
    {
        coordinates = getCoordinateFromHitAndSunkMessage(message);
        emit log("You hit and sunk opponent's ship at " + coordinates);
    }
    else
    {
        coordinates = getCoordinateFromHitMessage(message);
        emit log("You hit opponent's ship at " + coordinates);
    }
    opponentBoard->setSymbol(coordinates, "+");
}

void GameMessageProcessor::userMishitOpponentsShip(QString message)
{
    QString coordinates = getCoordinateFromMishitMessage(message);
    opponentBoard->setSymbol(coordinates, "-");
    emit log("You mishit at " + coordinates);
}
