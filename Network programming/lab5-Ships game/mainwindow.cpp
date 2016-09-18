#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TcpServer.h"
#include "TcpClient.h"
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logger = new Logger(ui->textBrowser, ui->chatBrowser);

    QObject::connect(ui->serverButton, SIGNAL(clicked()), this, SLOT(chooseServerMode()));
    QObject::connect(ui->clientButton, SIGNAL(clicked()), this, SLOT(chooseClientMode()));
    QObject::connect(ui->listenButton, SIGNAL(clicked()), this, SLOT(startGameAsServer()));
    QObject::connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(startGameAsClient()));
    QObject::connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendChatMessage()));
    QObject::connect(ui->shootButton, SIGNAL(clicked()), this, SLOT(shoot()));

    shipsWidget = new ShipsConfigurator(ui->centralWidget);
    gameProcessor = new GameMessageProcessor();

    QObject::connect(shipsWidget, SIGNAL(shipsConfigured()), this, SLOT(startGameWhenUserShipsConfigured()));
    QObject::connect(gameProcessor, SIGNAL(sendMessage(QString)), this, SLOT(sendMessageToOpponent(QString)));
    QObject::connect(gameProcessor, SIGNAL(log(QString)), logger, SLOT(logGameMessage(QString)));
    QObject::connect(gameProcessor, SIGNAL(opponentShipsConfigured()), this, SLOT(startGameWhenOpponentShipsConfigured()));
    QObject::connect(gameProcessor, SIGNAL(yourTurn()), this, SLOT(yourTurn()));

    configureStartScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureStartScreen()
{
    ui->clientButton->show();
    ui->serverButton->show();

    ui->youLabel->hide();
    ui->opponentLabel->hide();
    ui->addressLabel->hide();
    ui->addressLineEdit->hide();
    ui->portLabel->hide();
    ui->portLineEdit->hide();
    ui->connectButton->hide();
    ui->listenButton->hide();
    ui->shootButton->hide();
    shipsWidget->hide();

    ui->shootButton->setDisabled(true);

    ui->addressLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("7777");

    usersShipsConfigured = false;
    opponentsShipConfigured = false;
}

void MainWindow::chooseServerMode()
{
    configureModeOptionsScreen();
    ui->listenButton->show();
}

void MainWindow::chooseClientMode()
{
    configureModeOptionsScreen();
    ui->connectButton->show();
    ui->shootButton->setDisabled(true);
}

void MainWindow::startGameAsServer()
{
    QString serverAddress = ui->addressLineEdit->text();
    uint port = ui->portLineEdit->text().toInt();

    TcpServer* tcpServer = new TcpServer();
    QThread* tcpServerThread = new QThread(this);
    tcpServer->moveToThread(tcpServerThread);
    tcpServerThread->start();

    QObject::connect(tcpServer, SIGNAL(newConnection(TcpSocket*)), this, SLOT(newClient(TcpSocket*)));
    QObject::connect(tcpServer, SIGNAL(informUi(QString)), logger, SLOT(logGameMessage(QString)));
    QObject::connect(tcpServerThread, SIGNAL(finished()), tcpServerThread, SLOT(deleteLater()));
    QObject::connect(tcpServer, SIGNAL(destroyed(QObject*)), tcpServerThread, SLOT(quit()));

    QMetaObject::invokeMethod(tcpServer, "listen", Qt::QueuedConnection, Q_ARG(QString, serverAddress), Q_ARG(int, port));
}

void MainWindow::startGameAsClient()
{
    QString serverAddress = ui->addressLineEdit->text();
    uint port = ui->portLineEdit->text().toInt();

    TcpClient* tcpClient = new TcpClient();
    try
    {
        TcpSocket* clientSocket = tcpClient->connect(serverAddress, port);
        configureGameScreen();
        configureMessageExchanger(clientSocket);
        logger->logGameMessage("Connected to the server");
    }
    catch(...)
    {
        logger->logGameMessage("Error while connecting to the server");
        delete tcpClient;
    }
}

void MainWindow::configureModeOptionsScreen()
{
    ui->clientButton->hide();
    ui->serverButton->hide();
    ui->chooseModeLabel->hide();

    ui->addressLabel->show();
    ui->addressLineEdit->show();
    ui->portLabel->show();
    ui->portLineEdit->show();
}

void MainWindow::configureGameScreen()
{
    userBoard = new GameBoardWidget(ui->centralWidget);
    userBoard->setGeometry(QRect(40,200,312,277));

    opponentBoard = new GameBoardWidget(ui->centralWidget);
    opponentBoard->setGeometry(QRect(475,200,312,277));

    QFont labelFont = ui->youLabel->font();
    labelFont.setPointSize(17);
    ui->youLabel->setFont(labelFont);
    ui->opponentLabel->setFont(labelFont);

    ui->youLabel->show();
    ui->opponentLabel->show();
    userBoard->show();
    opponentBoard->show();
    ui->shootButton->show();
    shipsWidget->show();

    ui->connectButton->hide();
    ui->listenButton->hide();
    ui->addressLabel->hide();
    ui->addressLineEdit->hide();
    ui->portLabel->hide();
    ui->portLineEdit->hide();

    shipsWidget->setGameBoard(userBoard);
    gameProcessor->setUserGameBoard(userBoard);
    gameProcessor->setOpponentGameboard(opponentBoard);
}

void MainWindow::sendChatMessage()
{
    QString chatMessage = ui->chatLineEdit->text();
    exchanger->send(chatMessage);
    logger->logChatMessage("You", chatMessage);
    ui->chatLineEdit->clear();
}

void MainWindow::startGameWhenUserShipsConfigured()
{
    gameProcessor->setShips(shipsWidget->getShips());
    exchanger->send("/configured");
    usersShipsConfigured = true;
    if(opponentsShipConfigured && usersShipsConfigured)
        ui->shootButton->setEnabled(true);
}

void MainWindow::startGameWhenOpponentShipsConfigured()
{
    opponentsShipConfigured = true;
    if(opponentsShipConfigured && usersShipsConfigured)
        ui->shootButton->setEnabled(true);
}


void MainWindow::newClient(TcpSocket *tcpSocket)
{
    logger->logGameMessage("Client connected");
    configureMessageExchanger(tcpSocket);
    configureGameScreen();
}

void MainWindow::configureMessageExchanger(TcpSocket *socket)
{
    exchanger = new MessageExchanger(socket);

    QThread* exchangerThread = new QThread(this);
    exchanger->moveToThread(exchangerThread);
    exchangerThread->start();

    QObject::connect(exchanger, SIGNAL(messageFromOpponent(QString)), this, SLOT(messageFromOpponent(QString)));
    QMetaObject::invokeMethod(exchanger, "runListiningLoop", Qt::QueuedConnection);
}

void MainWindow::messageFromOpponent(QString message)
{
    if(message.startsWith("/shoot")
            || message.startsWith("/hit")
            || message.startsWith("/mishit")
            || message.startsWith("/configured"))
    {
        gameProcessor->processMessage(message);
    }
    else
    {
        logger->logChatMessage("Opponent", message);
    }
}

void MainWindow::shoot()
{
    int column = opponentBoard->currentColumn()+1;
    int row = opponentBoard->currentRow()+1;
    QString coords = translateCoordsToGameCoords(row, column);
    exchanger->send("/shoot " + coords);
    opponentTurn();
}

void MainWindow::sendMessageToOpponent(QString message)
{
    exchanger->send(message);
}

void MainWindow::yourTurn()
{
    ui->shootButton->setEnabled(true);
}

void MainWindow::opponentTurn()
{
    ui->shootButton->setDisabled(true);
}

QString MainWindow::translateCoordsToGameCoords(int row, int column)
{
    QString gameCoords;
    char firstSymbol = 'A' + (row-1);
    gameCoords += firstSymbol;
    gameCoords += QString::number(column);
    return gameCoords;
}
