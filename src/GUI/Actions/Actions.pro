!include(../../../Common.pri) {
    error(Could not find Common.pri file!)
}

SOURCES +=  Game.cpp \
    Settings.cpp \
    View.cpp

HEADERS  += Game.hpp \
    Settings.hpp \
    View.hpp
