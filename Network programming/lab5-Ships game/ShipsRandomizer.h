#ifndef SHIPSRANDOMIZER_H
#define SHIPSRANDOMIZER_H

#include <QObject>
#include <QStringList>

class ShipsRandomizer : public QObject
{
    Q_OBJECT
public:
    explicit ShipsRandomizer(QObject *parent = 0);
    void random();
    QStringList getSubmarines();
    QStringList getDestroyers();
    QStringList getCruisers();
    QString getBattleship();

signals:
    
public slots:

private:
    void randShipsDb(int randNumber);

    QStringList submarines;
    QStringList destroyers;
    QStringList cruisers;
    QString battleship;
    
};

#endif // SHIPSRANDOMIZER_H
