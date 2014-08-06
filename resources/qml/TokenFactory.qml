import QtQuick 2.0

/**
 * Creates tokens and manages them.
 */
Item
{
    /**
     * List of tokens managed by this factory.
     */
    property var tokenList: []

    /**
     * Style used for tokens.
     */
    property Component tokenStyle: TokenStyle {}

    /**
     * Creates and returns a new token for the given player.
     *
     * @param playerId The player id (1 or 2).
     * @param parentObject The parent object.
     * @param gameBoard The game board (used to compute width/height).
     * @return The new token.
     */
    function createToken(playerId, parentObject, gameBoard)
    {
        var component = Qt.createComponent("Token.qml");
        var tokenObj = component.createObject(parentObject, { "board" : gameBoard, "style": tokenStyle });

        tokenObj.isVisible = false;
        tokenObj.playerId = playerId;
        tokenObj.parent = parentObject;

        tokenList[tokenList.length] = tokenObj;

        return tokenObj;
    }

    /**
     * Destroys all tokens created by this factory.
     *
     * @param delay How many milliseconds to wait until destruction.
     */
    function destroyAllTokens(delay)
    {
        delay = typeof delay !== 'undefined' ? delay : 1000;

        while (tokenList.length > 0)
        {
            _destroyTokenAtIndex(0, delay);
        }

        tokenList = [];
    }

    /**
     * Destroys the given token.
     *
     * @param token The token to destroy.
     * @param delay How many milliseconds to wait until destruction.
     */
    function destroyToken(token, delay)
    {
        delay = typeof delay !== 'undefined' ? delay : 1000;

        var tokenIndex = tokenList.indexOf(token);
        if (-1 != tokenIndex)
        {
            _destroyTokenAtIndex(tokenIndex, delay);
        }
    }

    /**
     * Destroys the token with the given index.
     *
     * @param index Index in the token list.
     * @param delay How many milliseconds to wait until destruction.
     */
    function _destroyTokenAtIndex(index, delay)
    {
        if (index >= tokenList.length)
        {
            console.log("ERROR: Tried to destroy token with index " + index + " but token list length is " + tokenList.length + ".");

            return;
        }

        var token = tokenList[index];
        tokenList.splice(index, 1);
        token.destroy(delay);
    }
}
