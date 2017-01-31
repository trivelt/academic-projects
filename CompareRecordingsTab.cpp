#include "CompareRecordingsTab.h"
#include "XmlDatabaseReader.h"

#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QListWidget>
#include <QPushButton>

CompareRecordingsTab::CompareRecordingsTab(QWidget *parent)
    : QWidget(parent)
{
    resize(300, 300);
//    QLabel *fileNameLabel = new QLabel(tr("File Name:"));
//    QLineEdit *fileNameEdit = new QLineEdit("fileInfo.fileName()");

//    QLabel *pathLabel = new QLabel(tr("Path:"));
//    QLabel *pathValueLabel = new QLabel("fileInfo.absoluteFilePath()");
//    pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

//    QLabel *sizeLabel = new QLabel(tr("Size:"));
//    QLabel *sizeValueLabel = new QLabel("size");
//    sizeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

//    QLabel *lastReadLabel = new QLabel(tr("Last Read:"));
//    QLabel *lastReadValueLabel = new QLabel("fileInfo.lastRead().toString()");
//    lastReadValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

//    QLabel *lastModLabel = new QLabel(tr("Last Modified:"));
//    QLabel *lastModValueLabel = new QLabel("fileInfo.lastModified().toString()");
//    lastModValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QHBoxLayout *mainLayout = new QHBoxLayout;
//    mainLayout->addWidget(fileNameLabel);
//    mainLayout->addWidget(fileNameEdit);
//    mainLayout->addWidget(pathLabel);
//    mainLayout->addWidget(pathValueLabel);
//    mainLayout->addWidget(sizeLabel);
//    mainLayout->addWidget(sizeValueLabel);
//    mainLayout->addWidget(lastReadLabel);
//    mainLayout->addWidget(lastReadValueLabel);
//    mainLayout->addWidget(lastModLabel);
//    mainLayout->addWidget(lastModValueLabel);
//    mainLayout->addStretch(1);

    QListWidgetItem* item1 = new QListWidgetItem("ABC");
    QListWidgetItem* item2 = new QListWidgetItem("ABC");
    QListWidgetItem* item3 = new QListWidgetItem("ABC");
    QListWidgetItem* item4 = new QListWidgetItem("ABC");
    QListWidgetItem* item5 = new QListWidgetItem("ABC");

    QListWidget* firstListWidget = new QListWidget(this);
    firstListWidget->addItem(item1);
    firstListWidget->addItem(item2);
    firstListWidget->addItem(item3);
    firstListWidget->addItem(item4);
    firstListWidget->addItem(item5);

    QListWidgetItem* item7 = new QListWidgetItem("ABC");

    QListWidget* secondListWidget = new QListWidget(this);
    secondListWidget->addItem(item7);
    secondListWidget->addItem(item2);
    secondListWidget->addItem(item3);
    secondListWidget->addItem(item4);
    secondListWidget->addItem(item5);


    mainLayout->addWidget(firstListWidget);
    mainLayout->addWidget(secondListWidget);

//    setLayout(mainLayout);

    QVBoxLayout* rootLayout = new QVBoxLayout;
    rootLayout->addLayout(mainLayout);

    QPushButton* btn1 = new QPushButton("Compare");
    rootLayout->addWidget(btn1);
    setLayout(rootLayout);

    XmlDatabaseReader::getRecordings();
}
