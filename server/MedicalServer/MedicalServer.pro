#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T15:56:44
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MedicalServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp\
        serverdatabase.cpp \
    recievedata.cpp \
    senddata.cpp \
    communication.cpp \
    fortuneserver.cpp

HEADERS  += mainwidget.h\
        serverdatabase.h \
    senddata.h \
    communication.h \
    receivedata.h \
    fortuneserver.h

FORMS    += mainwidget.ui
