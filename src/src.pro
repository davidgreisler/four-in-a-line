!include(../Common.pri) {
    error(Could not find Common.pri file!)
}

TEMPLATE = app

LIBS += -L./GUI -L./GUI/Actions -L./Settings -lGUI -lActions -lSettings

SOURCES +=  main.cpp\
	    ConnectFour.cpp \
    ConnectFourSettings.cpp

HEADERS  += ConnectFour.hpp \
    ConnectFourSettings.hpp

RESOURCES += \
    ../resources/resources.qrc
