QT       += core gui widgets

TARGET = FourInALine
TEMPLATE = subdirs

SUBDIRS = src/GUI src/GUI/Actions src/Settings

CONFIG += ordered
SUBDIRS += src

OTHER_FILES += \
    Common.pri

TRANSLATIONS = resources/i18n/fourinaline_en.ts \
	       resources/i18n/fourinaline_de.ts
