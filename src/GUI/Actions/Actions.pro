!include(../../../Common.pri) {
    error(Could not find Common.pri file!)
}

SOURCES +=  Game.cpp \
    Settings.cpp \
    View.cpp \
    Help.cpp \
    Move.cpp \
    Replay.cpp

HEADERS  += Game.hpp \
    Settings.hpp \
    View.hpp \
    Help.hpp \
    Move.hpp \
    Replay.hpp
