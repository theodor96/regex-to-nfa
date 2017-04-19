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
           Automaton.cpp \
           State.cpp \

HEADERS += MainWindow.h \
           Canvas.h \
           Automaton.h \
           State.h \
    utils.h
