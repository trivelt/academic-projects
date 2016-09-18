#include "ShipsConfigurator.h"
#include "ui_ShipsConfigurator.h"
#include "ShipsRandomizer.h"
#include <QDebug>

ShipsConfigurator::ShipsConfigurator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShipsConfigurator)
{
    ui->setupUi(this);
    QObject::connect(ui->createShipsButton, SIGNAL(clicked()), this, SLOT(createShips()));
    QObject::connect(ui->randomButton, SIGNAL(clicked()), this, SLOT(getRandomShips()));
}

ShipsConfigurator::~ShipsConfigurator()
{
    delete ui;
}

void ShipsConfigurator::setGameBoard(GameBoardWidget *gameBoard)
{
    this->gameBoard = gameBoard;
}

QList<Ship *> ShipsConfigurator::getShips()
{
    return ships;
}

void ShipsConfigurator::readSingleShipField(QString text)
{
    gameBoard->setSymbol(text, "X");
    Ship* newShip = new Ship(QStringList(text));
    ships.append(newShip);
}

void ShipsConfigurator::readMultiShipField(QString text)
{
    QStringList coords = text.split(":");
    foreach(QString fieldValue, coords)
    {
        gameBoard->setSymbol(fieldValue, "X");
    }
    Ship* newShip = new Ship(coords);
    ships.append(newShip);
}


void ShipsConfigurator::createShips()
{
    readSingleShipField(ui->firstSubmarine->text());
    readSingleShipField(ui->secondSubmarine->text());
    readSingleShipField(ui->thirdSubmarine->text());
    readSingleShipField(ui->fourthSubmarine->text());

    readMultiShipField(ui->firstDestroyer->text());
    readMultiShipField(ui->secondDestroyer->text());
    readMultiShipField(ui->thirdDestroyer->text());

    readMultiShipField(ui->firstCuiser->text());
    readMultiShipField(ui->secondCruiser->text());

    readMultiShipField(ui->battleshipEdit->text());

    ui->createShipsButton->setDisabled(true);
    ui->randomButton->setDisabled(true);
    emit shipsConfigured();
}

void ShipsConfigurator::getRandomShips()
{
 ShipsRandomizer randomizer;
 randomizer.random();

 QStringList submarines = randomizer.getSubmarines();
 ui->firstSubmarine->setText(submarines.at(0));
 ui->secondSubmarine->setText(submarines.at(1));
 ui->thirdSubmarine->setText(submarines.at(2));
 ui->fourthSubmarine->setText(submarines.at(3));

 QStringList destroyers = randomizer.getDestroyers();
 ui->firstDestroyer->setText(destroyers.at(0));
 ui->secondDestroyer->setText(destroyers.at(1));
 ui->thirdDestroyer->setText(destroyers.at(2));

 QStringList cruisers = randomizer.getCruisers();
 ui->firstCuiser->setText(cruisers.at(0));
 ui->secondCruiser->setText(cruisers.at(1));

 QString battleship = randomizer.getBattleship();
 ui->battleshipEdit->setText(battleship);
}
