#include "RecognizeVoiceTab.h"
#include "AudioFilesComparator.h"
#include "InitParameters.h"
#include <QBoxLayout>
#include <QFileDialog>
#include <QDebug>

RecognizeVoiceTab::RecognizeVoiceTab(QWidget *parent)
    : QWidget(parent),
      selectedFile(""),
      compareFilesButton(0),
      selectedFileEdit(0),
      resultLabel(0),
      recordingLabel(0)
{
    audioRecorder = new QAudioRecorder(this);
    connect(audioRecorder, SIGNAL(durationChanged(qint64)), this,
            SLOT(updateProgress(qint64)));
    connect(audioRecorder, SIGNAL(statusChanged(QMediaRecorder::Status)), this,
            SLOT(updateStatus(QMediaRecorder::Status)));
    connect(audioRecorder, SIGNAL(stateChanged(QMediaRecorder::State)),
            this, SLOT(onStateChanged(QMediaRecorder::State)));
    connect(audioRecorder, SIGNAL(error(QMediaRecorder::Error)), this,
            SLOT(displayErrorMessage()));

    resize(300, 300);

    QVBoxLayout* rootLayout = new QVBoxLayout;
    rootLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* selectFileLabel = new QLabel("Select audio file");
    QFont f( "Arial", 15, QFont::Bold);
    selectFileLabel->setFont(f);
    selectFileLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    selectFileLabel->setMaximumHeight(20);
    rootLayout->addWidget(selectFileLabel);

    QHBoxLayout* filesLayout = new QHBoxLayout;
    selectedFileEdit = new QLineEdit("");
    QPushButton* selectButton = new QPushButton("...");
    compareFilesButton = new QPushButton("Compare");
    selectedFileEdit->setDisabled(true);
    compareFilesButton->setDisabled(true);
    filesLayout->addWidget(selectedFileEdit);
    filesLayout->addWidget(selectButton);
    rootLayout->addLayout(filesLayout);
    rootLayout->addWidget(compareFilesButton);

    QFrame* line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(320, 150, 118, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    rootLayout->addWidget(line);

    QLabel* recordVoiceLabel = new QLabel("Record your voice");
    recordVoiceLabel->setFont(f);
    recordVoiceLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    recordVoiceLabel->setMaximumHeight(20);
    rootLayout->addWidget(recordVoiceLabel);

    QHBoxLayout* recordingsButtonLayout = new QHBoxLayout;
    QPushButton* recordButton = new QPushButton("Record");
    QPushButton* stopButton = new QPushButton("Stop and compare");
//    stopButton->setDisabled(true);
    recordingsButtonLayout->addWidget(recordButton);
    recordingsButtonLayout->addWidget(stopButton);
    rootLayout->addLayout(recordingsButtonLayout);

    recordingLabel = new QLabel("");
    recordingLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    recordingLabel->setMaximumHeight(20);
    rootLayout->addWidget(recordingLabel);

    QFrame* line2 = new QFrame(this);
    line2->setObjectName(QString::fromUtf8("line"));
    line2->setGeometry(QRect(320, 150, 118, 3));
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    rootLayout->addWidget(line2);

    resultLabel = new QLabel("");
    resultLabel->setMaximumHeight(100);
    resultLabel->setAlignment(Qt::AlignCenter);
    rootLayout->addWidget(resultLabel);

    connect(selectButton, SIGNAL(clicked(bool)), this, SLOT(selectFileClicked()));
    connect(compareFilesButton, SIGNAL(clicked(bool)), this, SLOT(compareFilesClicked()));
    connect(recordButton, SIGNAL(clicked(bool)), this, SLOT(recordClicked()));
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopClicked()));

    setLayout(rootLayout);
}

void RecognizeVoiceTab::selectFileClicked()
{
    selectedFile = QFileDialog::getOpenFileName(this, "Select audio file", "", "WAV files (*.wav)");
    compareFilesButton->setEnabled(selectedFile != "");
    selectedFileEdit->setText(selectedFile);
}

void RecognizeVoiceTab::compareFilesClicked()
{
    AudioFilesComparator audioComparator;
    QString resultString = audioComparator.recognizeVoice(selectedFile);
    resultLabel->setText(resultString);
}

void RecognizeVoiceTab::recordClicked()
{
    qDebug() << "Recorder state=" << audioRecorder->state();

    audioRecorder->setOutputLocation(QUrl::fromLocalFile(InitParameters::audioOutputFile()));
    audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());

    QAudioEncoderSettings settings;
    settings.setCodec(QString());
    settings.setSampleRate(0);
    settings.setBitRate(0);
    settings.setChannelCount(-1);
    settings.setQuality(QMultimedia::VeryHighQuality);
    settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);

    QString container = "wav";
    QStringList containers = audioRecorder->supportedContainers();
    if(containers.contains("audio/x-wav"))
        container = "audio/x-wav";

    audioRecorder->setEncodingSettings(settings, QVideoEncoderSettings(), container);
    audioRecorder->record();

}

void RecognizeVoiceTab::stopClicked()
{
    audioRecorder->stop();
    AudioFilesComparator audioComparator;
    QString resultString = audioComparator.recognizeVoice(InitParameters::audioOutputFile());
    resultLabel->setText(resultString);
}

void RecognizeVoiceTab::updateProgress(qint64 progress)
{
    if(audioRecorder->status() == QMediaRecorder::RecordingStatus)
    {
        QString text = QString("Recorded %1 sec").arg(progress / 1000);
        recordingLabel->setText(text);
    }
    else
    {
        recordingLabel->setText("");
    }

}

void RecognizeVoiceTab::updateStatus(QMediaRecorder::Status status)
{
    qDebug() << "Status=" << status;
}

void RecognizeVoiceTab::onStateChanged(QMediaRecorder::State state)
{
    qDebug() << "State=" << state;
}

void RecognizeVoiceTab::displayErrorMessage()
{
    qDebug() << "Error ocurred";
}
