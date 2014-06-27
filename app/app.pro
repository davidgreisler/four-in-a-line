# Builds the main application.

include(Defines.pri)

TEMPLATE = app
TARGET = FourInALine

LIBS += -Wl,--start-group \
        $${BUILD_DIRECTORY}/src/GUI/libGUI.a \
	$${BUILD_DIRECTORY}/src/GUI/Actions/libActions.a \
	$${BUILD_DIRECTORY}/src/GUI/Widgets/libWidgets.a \
	$${BUILD_DIRECTORY}/src/GUI/Dialogs/libDialogs.a \
        $${BUILD_DIRECTORY}/src/Settings/libSettings.a \
        $${BUILD_DIRECTORY}/src/Game/libGame.a \
        $${BUILD_DIRECTORY}/src/Game/FourInALine/libFourInALine.a \
        -Wl,--end-group

SOURCES += FourInALine.cpp \
           main.cpp

HEADERS  += FourInALine.hpp

RESOURCES += $${ROOT_DIRECTORY}/resources/resources.qrc

TRANSLATIONS = $${ROOT_DIRECTORY}/resources/i18n/fourinaline_en.ts \
               $${ROOT_DIRECTORY}/resources/i18n/fourinaline_de.ts
