#ifndef ADDAUDIOFILETAB_H
#define ADDAUDIOFILETAB_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class AddAudioFileTab : public QWidget
{
    Q_OBJECT
public:
    explicit AddAudioFileTab(QWidget *parent = 0);


signals:
    void audioAdded();

public slots:
    void addButtonClicked();
    void selectFileClicked();
    void checkIfAddButonCanBeEnabled();

private:
    QLineEdit* selectedFileEdit;
    QLineEdit* titleEdit;
    QLineEdit* authorEdit;
    QPushButton* addButton;
    QLabel* resultLabel;

};

#endif // ADDAUDIOFILETAB_H
