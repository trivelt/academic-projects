#include "MainWindow.h"
#include "CompareRecordingsTab.h"
#include "RecognizeVoiceTab.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    MainWidget* mainWidget = new MainWidget;
    setCentralWidget(mainWidget);
    setWindowTitle("Voice recognition");
    resize(400, 400);
}

MainWindow::~MainWindow()
{
}

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    tabWidget = new QTabWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    tabWidget->addTab(new CompareRecordingsTab(), "Compare recordings");
    tabWidget->addTab(new RecognizeVoiceTab(), "Recognize the voice");
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
