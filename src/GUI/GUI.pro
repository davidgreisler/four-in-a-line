!include(../../Common.pri) {
    error(Could not find Common.pri file!)
}

SOURCES +=  MainWindow.cpp \
	    MainMenuBar.cpp \
	    Actions/Game.cpp

HEADERS  += \
	    MainWindow.hpp \
	    MainMenuBar.hpp \
	    Actions/Game.hpp
