import QtQuick 2.0

/**
 * Receives mouse/keyboard events and emits signals accordingly.
 */
Item
{
    /**
     * Emitted when the token should be moved one column to the left.
     */
    signal moveLeft

    /**
     * Emitted when the token should be moved one column to the right.
     */
    signal moveRight

    /**
     * Emitted when the token should be moved to the cursor.
     */
    signal moveToCursor(int x, int y)

    /**
     * Emitted when the token should be dropped.
     */
    signal drop

    /**
     * Whether the mouse can be used by the user to make a move.
     */
    property bool isMouseEnabled: true

    /**
     * Whether the keyboard can be used by the user to make a move.
     */
    property bool isKeyboardEnabled: true

    /**
     * Whether a move is requested or not.
     */
    property bool isMoveRequested: false

    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
        onPositionChanged: isMoveRequested && isMouseEnabled && emitMoveToCursor();
        onClicked: isMoveRequested && isMouseEnabled && drop();
    }

    // For keyboard input.

    focus: true

    /**
     * Moves/drops the token on key press.
     *
     * Does nothing if keyboard controls are disabled.
     */
    Keys.onPressed:
    {
        if (isMoveRequested && isKeyboardEnabled)
        {
            if (event.key === Qt.Key_Left)
            {
                moveLeft();
            }
            else if (event.key === Qt.Key_Right)
            {
                moveRight();
            }
            else if (event.key === Qt.Key_Enter || event.key === Qt.Key_Space || event.key === Qt.Key_Down)
            {
                drop();
            }
        }
    }

    /**
     * Emits the moveToCursor signal.
     */
    function emitMoveToCursor()
    {
        moveToCursor(mouseArea.mouseX, mouseArea.mouseY);
    }

    /**
     * Requests a new move with the given controls enabled.
     */
    function requestMove(enableMouse, enableKeyboard)
    {
        isMoveRequested = true;
        isMouseEnabled = enableMouse;
        isKeyboardEnabled = enableKeyboard;
    }

    /**
     * Ends the move request.
     */
    function endRequestMove()
    {
        isMoveRequested = false;
        isMouseEnabled = false;
        isKeyboardEnabled = false;
    }
}
