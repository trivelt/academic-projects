#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QTableWidget>

class GameBoardWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit GameBoardWidget(QWidget *parent = 0);
    void setSymbol(QString where, QString symbol);
    
signals:
    
public slots:

private:
    void makeBoardReadOnlyForUser();
    bool translateCoordinates(QString coordinates);

    int xCoord;
    int yCoord;
};

#endif // GAMEBOARD_H
