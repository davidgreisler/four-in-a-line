include(Defines.pri)

TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = ./GUI \
          ./GUI/Actions \
          ./Settings \
          ./Application.pro
