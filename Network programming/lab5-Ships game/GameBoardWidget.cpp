#include "GameBoardWidget.h"
#include <QDebug>

GameBoardWidget::GameBoardWidget(QWidget *parent) :
    QTableWidget(parent)
{
    setRowCount(10);
    setColumnCount(10);
    char name = 'A';
    for(int i=0; i<10; i++)
    {
        setColumnWidth(i,29);
        setRowHeight(i, 25);

        QTableWidgetItem *header = new QTableWidgetItem(QString(name));
        setVerticalHeaderItem(i, header);
        name++;
    }
    setSelectionMode(QAbstractItemView::SingleSelection);
    makeBoardReadOnlyForUser();
}

void GameBoardWidget::makeBoardReadOnlyForUser()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setFlags((item->flags() ^ Qt::ItemIsEditable));
            setItem(i, j, item);
        }
    }
}

void GameBoardWidget::setSymbol(QString where, QString symbol)
{
    bool translatingSuccess = translateCoordinates(where);
    if(translatingSuccess)
    {
        QTableWidgetItem* item = new QTableWidgetItem(symbol);
        setItem(xCoord, yCoord, item);
    }
}

bool GameBoardWidget::translateCoordinates(QString coordinates)
{
    if(coordinates.length() == 3)
    {
        if(coordinates[2] == '0')
        {
            char firstLetter = coordinates.toStdString()[0];
            xCoord = firstLetter-'A';
            yCoord = coordinates.mid(1,2).toInt()-1;
            return true;
        }
    }
    else if(coordinates.length() == 2)
    {
        char firstLetter = coordinates.toStdString()[0];
        xCoord = firstLetter-'A';
        yCoord = QString(coordinates[1]).toInt()-1;
        return true;
    }
    return false;
}
