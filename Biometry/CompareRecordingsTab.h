#ifndef COMPARERECORDINGSTAB_H
#define COMPARERECORDINGSTAB_H
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include "Recording.h"

class CompareRecordingsTab : public QWidget
{
    Q_OBJECT

public:
    explicit CompareRecordingsTab(QWidget *parent = 0);

public slots:
    void listItemChanged();
    void compareButtonClicked();
    void updateRecordingsList();
    void playFirstAudio();
    void playSecondAudio();

private:
    QString prepareDetailsText(Recording recording);

    QList<Recording> recordings;
    QListWidget* firstListWidget;
    QListWidget* secondListWidget;
    QLabel* firstItemInfoLabel;
    QLabel* secondItemInfoLabel;
    QLabel* resultLabel;
    QPushButton* compareButton;
    QPushButton* firstPlayButton;
    QPushButton* secondPlayButton;
};

#endif // COMPARERECORDINGSTAB_H
