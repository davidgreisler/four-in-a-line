include(Defines.pri)

TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = ./GUI \
          ./GUI/Actions \
          ./GUI/Widgets \
          ./GUI/Dialogs \
          ./Settings \
          ./Game \
          ./Game/FourInALine
