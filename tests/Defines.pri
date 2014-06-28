# Common configuration for all .pro files under tests/.
 
include(../Defines.pri)

LIBS += -Wl,--start-group \
        $${BUILD_DIRECTORY}/src/GUI/libGUI.a \
        $${BUILD_DIRECTORY}/src/GUI/Actions/libActions.a \
        $${BUILD_DIRECTORY}/src/Settings/libSettings.a \
        $${BUILD_DIRECTORY}/src/GameLogic/FourInALine/libFourInALine.a \
        $${BUILD_DIRECTORY}/src/GameLogic/libGameLogic.a \
        $${BUILD_DIRECTORY}/src/Game/Players/libPlayers.a \
        $${BUILD_DIRECTORY}/src/Game/libGame.a \
        -Wl,--end-group
