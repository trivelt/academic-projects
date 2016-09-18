#ifndef SHIP_H
#define SHIP_H

#include <QStringList>

class Ship
{
public:
    Ship(QStringList coordinates);
    void hit(QString shotCoordinates);
    bool isSunk();
    bool contains(QString coord);
    QString type();

private:
    QStringList coordinates;
    QString shipType;
    bool sunk;
    
};

#endif // SHIP_H
