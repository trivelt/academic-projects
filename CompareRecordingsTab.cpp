#include "CompareRecordingsTab.h"
#include "XmlDatabaseReader.h"

#include <QLineEdit>
#include <QBoxLayout>
#include <QPushButton>
#include <QtCore>

CompareRecordingsTab::CompareRecordingsTab(QWidget *parent)
    : QWidget(parent),
      firstListWidget(0),
      secondListWidget(0),
      firstItemInfoLabel(0),
      secondItemInfoLabel(0)
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

    mainLayout->addWidget(firstItemInfoLabel);
    mainLayout->addWidget(firstListWidget);
    mainLayout->addWidget(secondListWidget);
    mainLayout->addWidget(secondItemInfoLabel);


    QVBoxLayout* rootLayout = new QVBoxLayout;
    rootLayout->addLayout(mainLayout);

    QFrame* line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(320, 150, 118, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    rootLayout->addWidget(line);

    QLabel* resultLabel = new QLabel("");
    resultLabel->setMinimumHeight(100);
    resultLabel->setAlignment(Qt::AlignCenter);
    rootLayout->addWidget(resultLabel);

    QFrame* line2 = new QFrame(this);
    line2->setObjectName(QString::fromUtf8("line"));
    line2->setGeometry(QRect(320, 150, 118, 3));
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    rootLayout->addWidget(line2);

    QPushButton* btn1 = new QPushButton("Compare");
    rootLayout->addWidget(btn1);

    setLayout(rootLayout);

    XmlDatabaseReader::getRecordings();
}

void CompareRecordingsTab::listItemChanged()
{
    QListWidget* listWidget = (QListWidget*) sender();
    QListWidgetItem* item = listWidget->selectedItems().at(0);
    Recording recording = recordings[listWidget->row(item)];
    QString detailsText = prepareDetailsText(recording);
    if(listWidget == firstListWidget)
    {
        firstItemInfoLabel->setText(detailsText);
    }
    else
    {
        secondItemInfoLabel->setText(detailsText);
    }
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
