#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T10:44:29
#
#-------------------------------------------------

QT += core gui network sql phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MedicalTerminal
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    patientinfo.cpp \
    doctorintr.cpp \
    calculator.cpp\
#    callKeyBoard.cpp\
#    chnpanel.cpp\
#    clicklabel.cpp\
#    im.cpp\
#    key.cpp\
#    keyboard.cpp\
    sendinformation.cpp\
    bloodgauge.cpp\
    peinfowidget.cpp\
    petestwidget.cpp \
    communication.cpp \
    recieveinformation.cpp \
    doctorselect.cpp \
    patientselect.cpp \
    clientdatabase.cpp \
    alarmwidget.cpp \
    calendarwidget.cpp \
    loginwidget.cpp \
    personalinformation.cpp \
    musicwidget.cpp \
    musicplaylist.cpp \
    buildingpaintwidget.cpp \
    dayarrangewidget.cpp

HEADERS  += mainwidget.h \
    patientinfo.h \
    doctorintr.h \
    calculator.h\
#    callKeyBoard.h\
#    chnpanel.h\
#    clicklabel.h\
#    im.h\
#    key.h\
#    keyboard.h\
    sendinformation.h\
    bloodgauge.h\
    peinfowidget.h\
    petestwidget.h \
    communication.h \
    recieveinformation.h \
    doctorselect.h \
    patientselect.h \
    clientdatabase.h \
    alarmwidget.h \
    calendarwidget.h \
    loginwidget.h \
    personalinformation.h \
    musicwidget.h \
    musicplaylist.h \
    buildingpaintwidget.h \
    dayarrangewidget.h

FORMS    += mainwidget.ui \
    patientinfo.ui \
    doctorintr.ui \
    calculator.ui\
    bloodgauge.ui\
    peinfowidget.ui \
    doctorselect.ui \
    patientselect.ui \
    alarmwidget.ui \
    loginwidget.ui \
    personalinformation.ui \
    musicwidget.ui \
    buildingpaintwidget.ui \
    dayarrangewidget.ui

RESOURCES += \
    imgs.qrc
