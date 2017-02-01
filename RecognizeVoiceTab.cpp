#include "RecognizeVoiceTab.h"
#include "AudioFilesComparator.h"
#include <QBoxLayout>
#include <QFileDialog>
#include <QDebug>

RecognizeVoiceTab::RecognizeVoiceTab(QWidget *parent)
    : QWidget(parent),
      selectedFile(""),
      compareFilesButton(0),
      selectedFileEdit(0),
      resultLabel(0)
{
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
    stopButton->setDisabled(true);
    recordingsButtonLayout->addWidget(recordButton);
    recordingsButtonLayout->addWidget(stopButton);
    rootLayout->addLayout(recordingsButtonLayout);


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
