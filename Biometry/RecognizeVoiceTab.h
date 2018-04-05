#ifndef RECOGNIZEVOICETAB_H
#define RECOGNIZEVOICETAB_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QAudioRecorder>
#include <QMediaRecorder>

class RecognizeVoiceTab : public QWidget
{
    Q_OBJECT

public:
    explicit RecognizeVoiceTab(QWidget *parent = 0);

public slots:
    void selectFileClicked();
    void compareFilesClicked();
    void recordClicked();
    void stopClicked();

    void updateProgress(qint64 progress);
    void updateStatus(QMediaRecorder::Status status);
    void onStateChanged(QMediaRecorder::State state);
    void displayErrorMessage();

private:
    QString selectedFile;
    QPushButton* compareFilesButton;
    QLineEdit* selectedFileEdit;
    QLabel* resultLabel;
    QAudioRecorder *audioRecorder;
    QLabel* recordingLabel;
    QPushButton* stopButton;
};

#endif // RECOGNIZEVOICETAB_H
