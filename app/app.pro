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
        $${BUILD_DIRECTORY}/src/Game/Players/libPlayers.a \
        $${BUILD_DIRECTORY}/src/GameLogic/libGameLogic.a \
        $${BUILD_DIRECTORY}/src/GameLogic/FourInALine/libFourInALine.a \
        $${BUILD_DIRECTORY}/app/libFourInALine.a \
        -Wl,--end-group

PRE_TARGETDEPS += $${BUILD_DIRECTORY}/src/GUI/libGUI.a \
	          $${BUILD_DIRECTORY}/src/GUI/Actions/libActions.a \
          	  $${BUILD_DIRECTORY}/src/GUI/Widgets/libWidgets.a \
          	  $${BUILD_DIRECTORY}/src/GUI/Dialogs/libDialogs.a \
                  $${BUILD_DIRECTORY}/src/Settings/libSettings.a \
                  $${BUILD_DIRECTORY}/src/Game/libGame.a \
                  $${BUILD_DIRECTORY}/src/Game/Players/libPlayers.a \
                  $${BUILD_DIRECTORY}/src/GameLogic/libGameLogic.a \
                  $${BUILD_DIRECTORY}/src/GameLogic/FourInALine/libFourInALine.a \
                  $${BUILD_DIRECTORY}/app/libFourInALine.a

SOURCES += main.cpp

RESOURCES += $${ROOT_DIRECTORY}/resources/resources.qrc
