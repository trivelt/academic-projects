#-------------------------------------------------
#
# Project created by QtCreator 2017-01-29T20:52:37
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BiometryProject
TEMPLATE = app


SOURCES += main.cpp\
    XmlDatabaseReader.cpp \
    MainWindow.cpp \
    XmlDatabaseWriter.cpp \
    CompareRecordingsTab.cpp \
    RecognizeVoiceTab.cpp \
    AudioFilesComparator.cpp \
    VoiceRecognizer.cpp \
    Recording.cpp \
    InitParameters.cpp

HEADERS  += \
    XmlDatabaseReader.h \
    MainWindow.h \
    XmlDatabaseWriter.h \
    CompareRecordingsTab.h \
    RecognizeVoiceTab.h \
    AudioFilesComparator.h \
    VoiceRecognizer.h \
    Recording.h \
    InitParameters.h
