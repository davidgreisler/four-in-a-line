!include(../../Common.pri) {
    error(Could not find Common.pri file!)
}

SOURCES +=  AbstractSettings.cpp \
	    Application.cpp \
    View.cpp

HEADERS  += AbstractSettings.hpp \
	    Application.hpp \
    View.hpp
