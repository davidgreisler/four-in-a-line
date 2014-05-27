# Common configuration for all .pro files under tests/.
 
include(../Defines.pri)

LIBS += -Wl,--start-group \
        $${BUILD_DIRECTORY}/src/libApplication.a \
        $${BUILD_DIRECTORY}/src/GUI/libGUI.a \
        $${BUILD_DIRECTORY}/src/GUI/Actions/libActions.a \
        $${BUILD_DIRECTORY}/src/Settings/libSettings.a \
        $${BUILD_DIRECTORY}/src/Game/FourInALine/libFourInALine.a \
        $${BUILD_DIRECTORY}/src/Game/libGame.a \
        -Wl,--end-group
