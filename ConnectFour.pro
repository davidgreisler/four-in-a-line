#-------------------------------------------------
#
# Project created by QtCreator 2014-04-24T16:59:43
#
#-------------------------------------------------

QT       += core gui widgets


TARGET = ConnectFour
TEMPLATE = subdirs

SUBDIRS = src/GUI src/GUI/Actions

CONFIG += ordered
SUBDIRS += src

OTHER_FILES += \
    Common.pri
