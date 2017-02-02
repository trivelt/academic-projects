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
    resultLabel(0)
{
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

    filesLayout->addWidget(selectedFileEdit);
    filesLayout->addWidget(selectButton);
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(titleEdit);
    authorLayout->addWidget(authorLabel);
    authorLayout->addWidget(authorEdit);
    rootLayout->addLayout(filesLayout);
    rootLayout->addLayout(titleLayout);
    rootLayout->addLayout(authorLayout);
    rootLayout->addWidget(addButton);
    rootLayout->addWidget(resultLabel);


    QFrame* line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(320, 150, 118, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    rootLayout->addWidget(line);

    connect(titleEdit, SIGNAL(textChanged(QString)), this, SLOT(checkIfAddButonCanBeEnabled()));
    connect(authorEdit, SIGNAL(textChanged(QString)), this, SLOT(checkIfAddButonCanBeEnabled()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(selectFileClicked()));

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
    bool enable = !selectedFileEdit->text().isEmpty() && !titleEdit->text().isEmpty() && !authorEdit->text().isEmpty();
    addButton->setEnabled(enable);
}

void AddAudioFileTab::selectFileClicked()
{
    QString selectedFile = QFileDialog::getOpenFileName(this, "Select audio file", "", "WAV files (*.wav)");
    selectedFileEdit->setText(selectedFile);
    checkIfAddButonCanBeEnabled();
}
