QT       += core gui widgets

TARGET = ConnectFour
TEMPLATE = subdirs

SUBDIRS = src/GUI src/GUI/Actions

CONFIG += ordered
SUBDIRS += src

OTHER_FILES += \
    Common.pri

TRANSLATIONS = resources/i18n/connectfour_en.ts \
	       resources/i18n/connectfour_de.ts
