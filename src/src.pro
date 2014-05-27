!include(../Common.pri) {
    error(Could not find Common.pri file!)
}

TEMPLATE = app

LIBS += -L./GUI -L./GUI/Actions -L./Settings -lGUI -lActions -lSettings

SOURCES += main.cpp\
	   FourInALine.cpp \
           FourInALineSettings.cpp

HEADERS  += FourInALine.hpp \
            FourInALineSettings.hpp

RESOURCES += \
    ../resources/resources.qrc
