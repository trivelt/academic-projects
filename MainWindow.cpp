#include "MainWindow.h"
#include "CompareRecordingsTab.h"
#include "RecognizeVoiceTab.h"

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
    tabWidget->addTab(new CompareRecordingsTab(), "Compare recordings");
    tabWidget->addTab(new RecognizeVoiceTab(), "Recognize the voice");
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
