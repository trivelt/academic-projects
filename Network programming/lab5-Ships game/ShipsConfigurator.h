#ifndef SHIPSCONFIGURATOR_H
#define SHIPSCONFIGURATOR_H

#include <QWidget>
#include "GameBoardWidget.h"
#include "Ship.h"

namespace Ui {
class ShipsConfigurator;
}

class ShipsConfigurator : public QWidget
{
    Q_OBJECT
    
public:
    explicit ShipsConfigurator(QWidget *parent = 0);
    ~ShipsConfigurator();
    void setGameBoard(GameBoardWidget* gameBoard);
    QList<Ship*> getShips();

signals:
    void shipsConfigured();

public slots:
    void createShips();
    void getRandomShips();
    
private:
    void readSingleShipField(QString text);
    void readMultiShipField(QString text);

    Ui::ShipsConfigurator *ui;
    GameBoardWidget* gameBoard;
    QList<Ship*> ships;
};

#endif // SHIPSCONFIGURATOR_H
