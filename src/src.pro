include(Defines.pri)

TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = ./GUI \
          ./GUI/Actions \
          ./GUI/Widgets \
          ./GUI/Dialogs \
          ./Settings \
          ./GameLogic \
          ./GameLogic/FourInALine \
	  ./Game \
          ./Game/Players \
          ./Highscore

