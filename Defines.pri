# Common configuration for all .pro files.

ROOT_DIRECTORY = $$PWD
BUILD_DIRECTORY = $${ROOT_DIRECTORY}/build

QT += core gui widgets

# Activate C++11 support.

QMAKE_CXXFLAGS += -std=c++11
