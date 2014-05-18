!include(../../Common.pri) {
    error(Could not find Common.pri file!)
}

SOURCES +=  MainWindow.cpp \
	    MainMenuBar.cpp

HEADERS  += \
	    MainWindow.hpp \
	    MainMenuBar.hpp
