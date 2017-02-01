#ifndef RECOGNIZEVOICETAB_H
#define RECOGNIZEVOICETAB_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class RecognizeVoiceTab : public QWidget
{
    Q_OBJECT

public:
    explicit RecognizeVoiceTab(QWidget *parent = 0);

public slots:
    void selectFileClicked();
    void compareFilesClicked();

private:
    QString selectedFile;
    QPushButton* compareFilesButton;
    QLineEdit* selectedFileEdit;
    QLabel* resultLabel;
};

#endif // RECOGNIZEVOICETAB_H
