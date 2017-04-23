#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T23:33:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets

TARGET = RegexToNFA
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp \
           MainWindow.cpp \
           Canvas.cpp \
           AutomatonWidget.cpp \
           StateWidget.cpp \
           TransitionWidget.cpp \
           NFA.cpp \

HEADERS += MainWindow.h \
           Canvas.h \
           AutomatonWidget.h \
           StateWidget.h \
           TransitionWidget.h \
           NFA.h \
           Utils.h \
