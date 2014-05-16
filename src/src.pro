!include(../Common.pri) {
    error(Could not find Common.pri file!)
}

TEMPLATE = app

LIBS += -L./GUI -L./GUI/Actions -lGUI -lActions

SOURCES +=  main.cpp\
	    ConnectFour.cpp \
    ConnectFourSettings.cpp \
    Settings/Application.cpp \
    Settings/AbstractSettings.cpp

HEADERS  += ConnectFour.hpp \
    ConnectFourSettings.hpp \
    Settings/Application.hpp \
    Settings/AbstractSettings.hpp

RESOURCES += \
    ../resources/resources.qrc
