import QtQuick 2.3

/**
 * Token widget.
 */
AbstractWidget
{
    id: token
    z: 2

    style: TokenStyle {}

    /**
     * Width of the token.
     */
    property real tokenWidth: token._style.tokenWidth

    /**
     * Height of the token.
     */
    property real tokenHeight: token._style.tokenHeight

    /**
     * Player id, either 1 or 2.
     */
    property int playerId: 1

    /**
     * Destination X position, used by the moveToX()/moveToXY() methods.
     */
    property int destinationX: x

    /**
     * Destination Y position, used by the moveToX()/moveToXY() methods.
     */
    property int destinationY: y

    /**
     * Whether the token should be visible or not.
     */
    property bool isVisible: false

    /**
     * Whether the token should be highlighted or not.
     */
    property bool isHighlighted: false;

    /**
     * Reference to the game board, used to compute width/height.
     */
    property var board: null

    /**
     * Moves the token to the given X position.
     */
    function moveToX(destination)
    {
        token.destinationX = destination;
        _style.horizontalAnimation.start();
    }

    /**
     * Moves the token to the given Y position.
     */
    function moveToY(destination)
    {
        token.destinationY = destination;
        _style.verticalAnimation.start();
    }

    /**
     * Moves the token to the given X position and then to the given Y position.
     */
    function dropToXY(destX, destY)
    {
        token.destinationX = destX;
        token.destinationY = destY;

        _style.dropAnimation.running = true;
    }

    /**
     * Stops (pauses) moving the token.
     */
    function stopMoving()
    {
        if (_style.dropAnimation.running)
        {
            _style.dropAnimation.pause();
        }

        if (_style.horizontalAnimation.running)
        {
            _style.horizontalAnimation.pause();
        }

        if (_style.verticalAnimation.running)
        {
            _style.verticalAnimation.pause();
        }
    }

    /**
     * Returns whether the token is moving or not.
     */
    function isMoving()
    {
        return _style.dropAnimation.running || _style.horizontalAnimation.running || _style.verticalAnimation.running;
    }
}
