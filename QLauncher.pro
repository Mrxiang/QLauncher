#-------------------------------------------------
#
# Project created by QtCreator 2018-07-23T15:12:50
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QLauncher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parallaxhome.cpp \
    navibar.cpp \
    imagebutton.cpp \
    launcherrootview.cpp

HEADERS  += mainwindow.h \
    parallaxhome.h \
    navibar.h \
    imagebutton.h \
    launcherrootview.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    res/xml/launcher.xml
