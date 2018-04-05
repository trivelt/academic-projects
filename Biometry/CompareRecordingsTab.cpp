#include "CompareRecordingsTab.h"
#include "XmlDatabaseReader.h"
#include "AudioFilesComparator.h"

#include <QLineEdit>
#include <QBoxLayout>
#include <QtCore>
#include <QSound>
#include <QMediaPlayer>

CompareRecordingsTab::CompareRecordingsTab(QWidget *parent)
    : QWidget(parent),
      firstListWidget(0),
      secondListWidget(0),
      firstItemInfoLabel(0),
      secondItemInfoLabel(0),
      resultLabel(0),
      compareButton(0),
      firstPlayButton(0),
      secondPlayButton(0)
{
    resize(300, 300);
    QHBoxLayout *mainLayout = new QHBoxLayout;

    firstListWidget = new QListWidget(this);
    secondListWidget = new QListWidget(this);

    recordings = XmlDatabaseReader::getRecordings();
    foreach (Recording recording, recordings)
    {
        QListWidgetItem* firstItem = new QListWidgetItem(recording.getTitle());
        QListWidgetItem* secondItem = new QListWidgetItem(recording.getTitle());
        firstListWidget->addItem(firstItem);
        secondListWidget->addItem(secondItem);
    }

    connect(firstListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(listItemChanged()));
    connect(secondListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(listItemChanged()));

    firstItemInfoLabel = new QLabel("");
    secondItemInfoLabel = new QLabel("");

    firstItemInfoLabel->setMinimumWidth(220);
    secondItemInfoLabel->setMinimumWidth(220);
    firstItemInfoLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    secondItemInfoLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    firstItemInfoLabel->setWordWrap(true);
    secondItemInfoLabel->setWordWrap(true);

    mainLayout->addWidget(firstItemInfoLabel);
    mainLayout->addWidget(firstListWidget);
    mainLayout->addWidget(secondListWidget);
    mainLayout->addWidget(secondItemInfoLabel);


    QVBoxLayout* rootLayout = new QVBoxLayout;
    rootLayout->addLayout(mainLayout);

    QHBoxLayout* audioPlayLayout = new QHBoxLayout;
    firstPlayButton = new QPushButton("Play");
    secondPlayButton = new QPushButton("Play");
    firstPlayButton->setDisabled(true);
    secondPlayButton->setDisabled(true);
    audioPlayLayout->addWidget(firstPlayButton);
    audioPlayLayout->addWidget(secondPlayButton);
    rootLayout->addLayout(audioPlayLayout);

    QFrame* line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(320, 150, 118, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    rootLayout->addWidget(line);

    resultLabel = new QLabel("");
    resultLabel->setMinimumHeight(100);
    resultLabel->setAlignment(Qt::AlignCenter);
    rootLayout->addWidget(resultLabel);

    QFrame* line2 = new QFrame(this);
    line2->setObjectName(QString::fromUtf8("line"));
    line2->setGeometry(QRect(320, 150, 118, 3));
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    rootLayout->addWidget(line2);

    compareButton = new QPushButton("Compare");
    rootLayout->addWidget(compareButton);
    compareButton->setEnabled(false);

    connect(compareButton, SIGNAL(clicked()), this, SLOT(compareButtonClicked()));
    connect(firstPlayButton, SIGNAL(clicked(bool)), this, SLOT(playFirstAudio()));
    connect(secondPlayButton, SIGNAL(clicked(bool)), this, SLOT(playSecondAudio()));

    setLayout(rootLayout);

    XmlDatabaseReader::getRecordings();
}

void CompareRecordingsTab::listItemChanged()
{
    QListWidget* listWidget = (QListWidget*) sender();
    if(listWidget->selectedItems().isEmpty())
    {
        firstItemInfoLabel->setText("");
        secondItemInfoLabel->setText("");
        return;
    }
    QListWidgetItem* item = listWidget->selectedItems().at(0);
    Recording recording = recordings[listWidget->row(item)];
    QString detailsText = prepareDetailsText(recording);
    if(listWidget == firstListWidget)
    {
        firstItemInfoLabel->setText(detailsText);
        firstPlayButton->setEnabled(true);
    }
    else
    {
        secondItemInfoLabel->setText(detailsText);
        secondPlayButton->setEnabled(true);
    }

    if(firstListWidget->selectedItems().size() > 0 && secondListWidget->selectedItems().size() > 0)
    {
        compareButton->setEnabled(true);
    }
}

void CompareRecordingsTab::compareButtonClicked()
{
    QListWidgetItem* firstItem = firstListWidget->selectedItems().at(0);
    Recording firstRecording = recordings[firstListWidget->row(firstItem)];

    QListWidgetItem* secondItem = firstListWidget->selectedItems().at(0);
    Recording secondRecording = recordings[firstListWidget->row(secondItem)];

    AudioFilesComparator audioComparator;
    double correlation = audioComparator.compareTwoFiles(firstRecording.getFilepath(), secondRecording.getFilepath());
    QString resultText = "Correlation: <b>" + QString::number(correlation) + "</b><br /><br />";
    if(audioComparator.isTheSameVoice(correlation))
    {
        resultText += "<b>These voices belong to the same person</b>";
    }
    else
    {
        resultText += "<b>These voices belong to the different people</b>";
    }
    resultLabel->setText(resultText);
}

QString CompareRecordingsTab::prepareDetailsText(Recording recording)
{
    QString text = "<b>Title:</b><br />";
    text += recording.getTitle();
    text += "<br /><br /><b>File:</b><br />";
    text += recording.getFilepath();
    text += "<br /><br /><b>Author:</b><br />";
    text += recording.getAuthor();
    text += "<br /><br /><b>Date:</b><br />";
    text += recording.getDate();
    return text;
}

void CompareRecordingsTab::updateRecordingsList()
{
    firstListWidget->clear();
    secondListWidget->clear();
    recordings = XmlDatabaseReader::getRecordings();
    foreach (Recording recording, recordings)
    {
        QListWidgetItem* firstItem = new QListWidgetItem(recording.getTitle());
        QListWidgetItem* secondItem = new QListWidgetItem(recording.getTitle());
        firstListWidget->addItem(firstItem);
        secondListWidget->addItem(secondItem);
    }
}

void CompareRecordingsTab::playFirstAudio()
{
    if(firstListWidget->selectedItems().isEmpty())
        return;
    QListWidgetItem* item = firstListWidget->selectedItems().at(0);
    Recording recording = recordings[firstListWidget->row(item)];
    QString filepath = recording.getFilepath();
    qDebug() << "filepath=" << filepath;
//    QSound::play(filepath);

    QMediaPlayer* player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(filepath));
    player->play();
}

void CompareRecordingsTab::playSecondAudio()
{
    if(secondListWidget->selectedItems().isEmpty())
        return;
    QListWidgetItem* item = secondListWidget->selectedItems().at(0);
    Recording recording = recordings[secondListWidget->row(item)];
    QString filepath = recording.getFilepath();

    QMediaPlayer* player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(filepath));
    player->play();
}
