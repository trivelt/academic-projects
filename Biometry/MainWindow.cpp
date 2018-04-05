#include "MainWindow.h"
#include "CompareRecordingsTab.h"
#include "RecognizeVoiceTab.h"
#include "AddAudioFileTab.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QStyle>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    MainWidget* mainWidget = new MainWidget;
    setCentralWidget(mainWidget);
    setWindowTitle("Voice recognition");
    resize(800, 600);

    setWindowInCentre();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setWindowInCentre()
{
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            qApp->desktop()->availableGeometry()
        ));
}

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    tabWidget = new QTabWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout;

    CompareRecordingsTab* compareRecordingsTab = new CompareRecordingsTab();
    AddAudioFileTab* addAudioFileTab = new AddAudioFileTab();

    connect(addAudioFileTab, SIGNAL(audioAdded()), compareRecordingsTab, SLOT(updateRecordingsList()));

    tabWidget->addTab(compareRecordingsTab, "Compare recordings");
    tabWidget->addTab(new RecognizeVoiceTab(), "Recognize the voice");
    tabWidget->addTab(addAudioFileTab, "Add audio to database");
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
