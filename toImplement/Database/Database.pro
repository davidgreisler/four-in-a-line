#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T22:11:37
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Database
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    highscore.cpp

HEADERS  += mainwindow.h \
    database.h \
    highscore.h

FORMS    += mainwindow.ui
