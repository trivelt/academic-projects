#ifndef COMPARERECORDINGSTAB_H
#define COMPARERECORDINGSTAB_H
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include "Recording.h"

class CompareRecordingsTab : public QWidget
{
    Q_OBJECT

public:
    explicit CompareRecordingsTab(QWidget *parent = 0);

public slots:
    void listItemChanged();

private:
    QString prepareDetailsText(Recording recording);

    QList<Recording> recordings;
    QListWidget* firstListWidget;
    QListWidget* secondListWidget;
    QLabel* firstItemInfoLabel;
    QLabel* secondItemInfoLabel ;
};

#endif // COMPARERECORDINGSTAB_H
