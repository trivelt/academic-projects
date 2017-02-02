#include "AddAudioFileTab.h"
#include "XmlDatabaseWriter.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QDateTime>

AddAudioFileTab::AddAudioFileTab(QWidget *parent) :
    QWidget(parent),
    selectedFileEdit(0),
    titleEdit(0),
    authorEdit(0),
    addButton(0),
    resultLabel(0),
    recordingInfoLabel(0),
    audioRecorder(0),
    recordingFilepathEdit(0),
    recordButton(0),
    stopButton(0)
{
    audioRecorder = new QAudioRecorder(this);
    connect(audioRecorder, SIGNAL(durationChanged(qint64)), this,
            SLOT(updateProgress(qint64)));

    QVBoxLayout* rootLayout = new QVBoxLayout;
    QHBoxLayout* filesLayout = new QHBoxLayout;
    QHBoxLayout* titleLayout = new QHBoxLayout;
    QHBoxLayout* authorLayout = new QHBoxLayout;
    QLabel* titleLabel = new QLabel("Title");
    QLabel* authorLabel = new QLabel("Author");
    selectedFileEdit = new QLineEdit("");
    titleEdit = new QLineEdit();
    authorEdit = new QLineEdit();
    QPushButton* selectButton = new QPushButton("...");
    addButton = new QPushButton("Add");
    resultLabel = new QLabel("");

    selectedFileEdit->setDisabled(true);
    titleEdit->setMaximumWidth(700);
    authorEdit->setMaximumWidth(700);
    addButton->setDisabled(true);
    resultLabel->setAlignment(Qt::AlignCenter);

    QFrame* line = new QFrame(this);
    line->setGeometry(QRect(320, 150, 118, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QFrame* line2 = new QFrame(this);
    line2->setGeometry(QRect(320, 150, 118, 3));
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);

    QFrame* line3 = new QFrame(this);
    line3->setGeometry(QRect(320, 150, 118, 3));
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Sunken);

    QLabel* selectFileLabel = new QLabel("Select audio file");
    QFont f( "Arial", 15, QFont::Bold);
    selectFileLabel->setFont(f);
    selectFileLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    selectFileLabel->setMaximumHeight(20);

    QLabel* recordVoiceLabel = new QLabel("Record your voice");
    recordVoiceLabel->setFont(f);
    recordVoiceLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    recordVoiceLabel->setMaximumHeight(20);

    filesLayout->addWidget(selectedFileEdit);
    filesLayout->addWidget(selectButton);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(titleEdit);
    authorLayout->addWidget(authorLabel);
    authorLayout->addWidget(authorEdit);
    rootLayout->addLayout(titleLayout);
    rootLayout->addLayout(authorLayout);
    rootLayout->addWidget(line);
    rootLayout->addWidget(selectFileLabel);
    rootLayout->addLayout(filesLayout);
    rootLayout->addWidget(addButton);
    rootLayout->addWidget(line2);
    rootLayout->addWidget(recordVoiceLabel);

    QHBoxLayout* recordingFileLayout = new QHBoxLayout();
    recordingFilepathEdit = new QLineEdit();
    recordingFilepathEdit->setDisabled(true);
    QPushButton* recordingFileButton = new QPushButton("...");
    recordingFileLayout->addWidget(recordingFilepathEdit);
    recordingFileLayout->addWidget(recordingFileButton);
    rootLayout->addLayout(recordingFileLayout);

    QHBoxLayout* recordingButtonsLayout = new QHBoxLayout();
    recordButton = new QPushButton("Record");
    stopButton = new QPushButton("Stop and save");
    recordingButtonsLayout->addWidget(recordButton);
    recordingButtonsLayout->addWidget(stopButton);
    rootLayout->addLayout(recordingButtonsLayout);

    recordButton->setDisabled(true);
    stopButton->setDisabled(true);

    recordingInfoLabel = new QLabel("");
    recordingInfoLabel->setMaximumHeight(20);
    rootLayout->addWidget(recordingInfoLabel);

    connect(titleEdit, SIGNAL(textChanged(QString)), this, SLOT(checkIfAddButonCanBeEnabled()));
    connect(authorEdit, SIGNAL(textChanged(QString)), this, SLOT(checkIfAddButonCanBeEnabled()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(selectFileClicked()));

    connect(recordButton, SIGNAL(clicked(bool)), this, SLOT(recordClicked()));
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(stopClicked()));
    connect(recordingFileButton, SIGNAL(clicked(bool)), this, SLOT(selectAudioOutputClicked()));

    rootLayout->addWidget(line3);
    rootLayout->addWidget(resultLabel);

    setLayout(rootLayout);
}

void AddAudioFileTab::addButtonClicked()
{
    QDateTime currentDate = QDateTime::currentDateTime();
    QString date = currentDate.toString("d MMMM yyyy hh:mm:ss");
    Recording recording(titleEdit->text(), selectedFileEdit->text(), authorEdit->text(), date);
    bool success = XmlDatabaseWriter::addRecordingToDatabase(recording);
    if(success)
    {
        resultLabel->setText("Audio added to database");
        titleEdit->setText("");
        authorEdit->setText("");
        selectedFileEdit->setText("");
        emit audioAdded();
    }
    else
    {
        resultLabel->setText("Could not add audio to database");
    }
}

void AddAudioFileTab::checkIfAddButonCanBeEnabled()
{
    bool fieldsNotEmpty =!titleEdit->text().isEmpty() && !authorEdit->text().isEmpty();

    bool enable = !selectedFileEdit->text().isEmpty() && fieldsNotEmpty;
    addButton->setEnabled(enable);

    bool enableRecord = !recordingFilepathEdit->text().isEmpty() && fieldsNotEmpty;
    recordButton->setEnabled(enableRecord);
}

void AddAudioFileTab::selectFileClicked()
{
    QString selectedFile = QFileDialog::getOpenFileName(this, "Select audio file", "", "WAV files (*.wav)");
    selectedFileEdit->setText(selectedFile);
    checkIfAddButonCanBeEnabled();
}

void AddAudioFileTab::recordClicked()
{
    qDebug() << "Recorder state=" << audioRecorder->state();

    QString outputFile = recordingFilepathEdit->text();
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(outputFile));
    audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());

    QAudioEncoderSettings settings;
    settings.setCodec(QString());
    settings.setSampleRate(0);
    settings.setBitRate(0);
    settings.setChannelCount(1);
    settings.setQuality(QMultimedia::VeryHighQuality);
    settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);

    QString container = "wav";
    QStringList containers = audioRecorder->supportedContainers();
    if(containers.contains("audio/x-wav"))
        container = "audio/x-wav";

    audioRecorder->setEncodingSettings(settings, QVideoEncoderSettings(), container);
    stopButton->setEnabled(true);
    audioRecorder->record();

}

void AddAudioFileTab::stopClicked()
{
    audioRecorder->stop();
    stopButton->setDisabled(true);

    QDateTime currentDate = QDateTime::currentDateTime();
    QString date = currentDate.toString("d MMMM yyyy hh:mm:ss");
    Recording recording(titleEdit->text(), recordingFilepathEdit->text(), authorEdit->text(), date);
    bool success = XmlDatabaseWriter::addRecordingToDatabase(recording);
    if(success)
    {
        resultLabel->setText("Your recording was added to database");
        titleEdit->setText("");
        authorEdit->setText("");
        selectedFileEdit->setText("");
        emit audioAdded();
    }
    else
    {
        resultLabel->setText("Could not add audio to database");
    }
}

void AddAudioFileTab::updateProgress(qint64 progress)
{
    if(audioRecorder->status() == QMediaRecorder::RecordingStatus)
    {
        QString text = QString("Recorded %1 sec").arg(progress / 1000);
        recordingInfoLabel->setText(text);
    }
    else
    {
        recordingInfoLabel->setText("");
    }

}

void AddAudioFileTab::selectAudioOutputClicked()
{
    QString selectedFile = QFileDialog::getSaveFileName(this, "Create audio file", "", "WAV files (*.wav)");
    recordingFilepathEdit->setText(selectedFile);
    checkIfAddButonCanBeEnabled();
}
