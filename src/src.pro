include(Defines.pri)

TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = ./GUI \
          ./GUI/Actions \
          ./Settings \
          ./Game \
          ./Game/FourInALine \
          ./Application.pro
