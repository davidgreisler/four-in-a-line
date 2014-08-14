# Common configuration for all .pro files.

ROOT_DIRECTORY = $$PWD
BUILD_DIRECTORY = $$shadowed($$PWD)

QT += core gui widgets network printsupport quick quickwidgets svg qml multimedia

# Activate C++11 support.

QMAKE_CXXFLAGS += -std=c++11

# Add code coverage support.

CONFIG(debug) {
	LIBS += -lgcov
	QMAKE_CXXFLAGS += -g -fprofile-arcs -ftest-coverage -O0 -Wall -Wextra
	QMAKE_LFLAGS += -g -fprofile-arcs -ftest-coverage -O0
}

# Do not put libraries/executables/object files under release/debug directories.

win32 {
    DESTDIR = ./
    OBJECTS_DIR = ./
    MOC_DIR = ./
}
