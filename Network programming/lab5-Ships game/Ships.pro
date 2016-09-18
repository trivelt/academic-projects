#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T18:32:58
#
#-------------------------------------------------

QT       += core gui network

TARGET = Ships
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GameBoardWidget.cpp \
    TcpServer.cpp \
    TcpClient.cpp \
    TcpSocket.cpp \
    MessageExchanger.cpp \
    Logger.cpp \
    ShipsConfigurator.cpp \
    GameMessageProcessor.cpp \
    Ship.cpp \
    ShipsRandomizer.cpp

HEADERS  += mainwindow.h \
    GameBoardWidget.h \
    TcpServer.h \
    TcpClient.h \
    TcpSocket.h \
    MessageExchanger.h \
    Logger.h \
    ShipsConfigurator.h \
    GameMessageProcessor.h \
    Ship.h \
    ShipsRandomizer.h

FORMS    += mainwindow.ui \
    ShipsConfigurator.ui
