#include "ShipsRandomizer.h"
#include <QDebug>
#include <cstdlib>
#include <ctime>

ShipsRandomizer::ShipsRandomizer(QObject *parent) :
    QObject(parent)
{
}

void ShipsRandomizer::random()
{
    srand(time(NULL));
    int randNumber = rand() % 10;
    qDebug() << "Random number = " << randNumber;
    randShipsDb(randNumber);
}

QStringList ShipsRandomizer::getSubmarines()
{
    return submarines;
}

QStringList ShipsRandomizer::getDestroyers()
{
    return destroyers;
}

QStringList ShipsRandomizer::getCruisers()
{
    return cruisers;
}

QString ShipsRandomizer::getBattleship()
{
    return battleship;
}

void ShipsRandomizer::randShipsDb(int randNumber)
{
    switch(randNumber)
    {
        case 0:
            submarines << "A1" <<  "A3" << "B5" << "D9";
            destroyers << "J1:J2" << "H9:I9" << "F5:G5";
            cruisers << "F1:G1:H1" << "J4:J5:J6";
            battleship = "D1:D2:D3:D4";
            break;
        case 1:
            submarines << "J1" <<  "H3" << "B5" << "D9";
            destroyers << "A9:A10" << "F9:F10" << "C1:D1";
            cruisers << "D4:D5:D6" << "F3:F4:F5";
            battleship = "G6:H6:I6:J6";
            break;
        case 2:
            submarines << "H6" <<  "H3" << "B5" << "D9";
            destroyers << "A9:A10" << "F9:F10" << "C1:D1";
            cruisers << "A3:B3:C3" << "F3:F4:F5";
            battleship = "H7:H8:H9:H10";
            break;
        case 3:
            submarines << "F1" <<  "H1" << "H4" << "J6";
            destroyers << "H10:I10" << "F9:F10" << "C1:D1";
            cruisers << "A3:B3:C3" << "D7:E7:F7";
            battleship = "A5:B5:C5:D5";
            break;
        case 4:
            submarines << "A5" <<  "D3" << "D10" << "J1";
            destroyers << "H10:I10" << "F9:F10" << "C1:D1";
            cruisers << "A1:A2:A3" << "D7:E7:F7";
            battleship = "B7:B8:B9:B10";
            break;
        case 5:
            submarines << "A5" <<  "C5" << "D10" << "G5";
            destroyers << "H10:I10" << "F9:F10" << "H7:H8";
            cruisers << "J6:J7:J8" << "D7:E7:F7";
            battleship = "B7:B8:B9:B10";
            break;
        case 6:
            submarines << "E3" <<  "C10" << "D10" << "G5";
            destroyers << "H10:I10" << "F9:F10" << "H7:H8";
            cruisers << "J6:J7:J8" << "D7:E7:F7";
            battleship = "D1:E1:F1:G1";
            break;
        case 7:
            submarines << "E3" <<  "C10" << "D10" << "B4";
            destroyers << "H10:I10" << "F9:F10" << "H4:H5";
            cruisers << "J6:J7:J8" << "E7:F7:G8";
            battleship = "F1:G1:H1:I1";
            break;
        case 8:
            submarines << "A1" <<  "C1" << "G1" << "B10";
            destroyers << "G4:G5" << "I4:J4" << "I7:J7";
            cruisers << "C4:C5:C6" << "E4:E5:E6";
            battleship = "A4:A5:A6:A7";
            break;
        case 9:
            submarines << "A3" <<  "C1" << "C3" << "B10";
            destroyers << "G4:G5" << "I4:J4" << "I7:J7";
            cruisers << "B8:C8:D8" << "H1:I1:J1";
            battleship = "E10:F10:G10:H10";
            break;
        default:
            break;
    }
}
