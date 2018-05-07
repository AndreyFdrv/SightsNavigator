#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T22:05:08
#
#-------------------------------------------------

QT       += core gui webengine webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SightsNavigator
TEMPLATE = app


SOURCES +=\
        MainWindow.cpp \
    MapWidget.cpp \
    Main.cpp \
    Sight.cpp

HEADERS  += MainWindow.h \
    MapWidget.h \
    Sight.h

FORMS    += MainWindow.ui

RESOURCES += \
    MapPage.qrc

DISTFILES +=
