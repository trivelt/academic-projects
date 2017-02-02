#ifndef ADDAUDIOFILETAB_H
#define ADDAUDIOFILETAB_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QAudioRecorder>

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

    void selectAudioOutputClicked();
    void recordClicked();
    void stopClicked();
    void updateProgress(qint64 progress);

private:
    QLineEdit* selectedFileEdit;
    QLineEdit* titleEdit;
    QLineEdit* authorEdit;
    QPushButton* addButton;
    QLabel* resultLabel;
    QLabel* recordingInfoLabel;
    QAudioRecorder* audioRecorder;
    QLineEdit* recordingFilepathEdit;
    QPushButton* recordButton;
    QPushButton* stopButton;
};

#endif // ADDAUDIOFILETAB_H
