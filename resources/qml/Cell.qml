import QtQuick 2.0

/**
 * Cell widget.
 */
Item
{
    id: cell

    /**
     * Token in this cell (can be null).
     */
    property Token token: null

    /**
     * Used to position the token over the middle of the cell.
     */
    property var mapTarget: null

    onXChanged: _adjustPosition();
    onYChanged: _adjustPosition();

    /**
     * Drops the given token into this cell.
     *
     * @param token The token to drop into this cell.
     */
    function dropToken(token)
    {
        var position = _computeTokenPosition(token);

        token.dropToXY(position.x, position.y);
        cell.token = token;
    }

    /**
     * Removes and returns the token from the cell.
     *
     * @return The token.
     */
    function takeToken()
    {
        if (null === token)
        {
            console.log("ERROR: Tried to take token from cell which has no token.");

            return;
        }

        var retVal = token;
        token = null;

        return retVal;
    }

    /**
     * Computes the x/y coordinates for centering the given token in this cell.
     *
     * @param token The token.
     */
    function _computeTokenPosition(token)
    {
        var mappedToBoard = cell.mapToItem(mapTarget, 0, 0);

        var widthDelta = cell.width - token.tokenWidth;
        var heightDelta = cell.height - token.tokenHeight;

        var tokenX = mappedToBoard.x + (widthDelta / 2);
        var tokenY = mappedToBoard.y + (heightDelta / 2);

        return { 'x' : tokenX, 'y' : tokenY };
    }

    /**
     * Adjusts the position of the token when the cell changed it's X/Y position.
     */
    function _adjustPosition()
    {
        if (cell.token == null)
        {
            return;
        }

        var position = _computeTokenPosition(token);

        if (token.isMoving())
        {
            token.stopMoving();
        }

        token.x = position.x;
        token.y = position.y;
    }
}
