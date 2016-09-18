#include "Ship.h"
#include <QDebug>

Ship::Ship(QStringList coordinates)
{
    qDebug() << "Added new Ship with coord=" << coordinates;
    sunk = false;
    this->coordinates = coordinates;
    switch(coordinates.length())
    {
    case 1:
        shipType = "submarine";
        break;
    case 2:
        shipType = "destroyer";
        break;
    case 3:
        shipType = "cruiser";
        break;
    case 4:
        shipType = "battleship";
        break;
    default:
        shipType = "undefined";
        break;
    }
}

void Ship::hit(QString shotCoordinates)
{
    qDebug() << "I am Ship and I was hit to my coords=" << coordinates << " by shot at " << shotCoordinates;
    coordinates.removeOne(shotCoordinates);
    qDebug() << "coords removed = " << coordinates;
    if(coordinates.isEmpty())
        sunk = true;
}

bool Ship::contains(QString coord)
{
    return coordinates.contains(coord);
}

bool Ship::isSunk()
{
    return sunk;
}

QString Ship::type()
{
    return shipType;
}
