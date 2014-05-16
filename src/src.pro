!include(../Common.pri) {
    error(Could not find Common.pri file!)
}

TEMPLATE = app

LIBS += -L./GUI -L./GUI/Actions -lGUI -lActions

SOURCES +=  main.cpp\
	    ConnectFour.cpp

HEADERS  += ConnectFour.hpp
