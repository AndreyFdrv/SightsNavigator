#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T22:05:08
#
#-------------------------------------------------

QT       += core gui

QT += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SightsNavigator
TEMPLATE = app


SOURCES +=\
        MainWindow.cpp \
    MapWidget.cpp \
    Main.cpp

HEADERS  += MainWindow.h \
    MapWidget.h

FORMS    += MainWindow.ui
