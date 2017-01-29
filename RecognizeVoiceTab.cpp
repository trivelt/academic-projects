#include "RecognizeVoiceTab.h"
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>

RecognizeVoiceTab::RecognizeVoiceTab(QWidget *parent)
    : QWidget(parent)
{
    resize(300, 300);
    QLabel *fileNameLabel = new QLabel(tr("File Name:"));
    QLineEdit *fileNameEdit = new QLineEdit("fileInfo.fileName()");

    QLabel *pathLabel = new QLabel(tr("Path:"));
    QLabel *pathValueLabel = new QLabel("fileInfo.absoluteFilePath()");
    pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *lastModLabel = new QLabel(tr("Last Modified:"));
    QLabel *lastModValueLabel = new QLabel("fileInfo.lastModified().toString()");
    lastModValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(fileNameEdit);
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(pathValueLabel);
    mainLayout->addWidget(lastModLabel);
    mainLayout->addWidget(lastModValueLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
