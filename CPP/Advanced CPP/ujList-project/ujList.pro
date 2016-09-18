TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    unitTests.cpp

HEADERS += \
    ujList.h


LIBS += -lcppunit

QMAKE_CXXFLAGS += -std=c++0x
