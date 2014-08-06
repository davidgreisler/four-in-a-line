import QtQuick 2.0

Item
{
    id: game

    /**
     * Emitted when the player made a move.
     */
    signal playerMadeMove(int columnNo);

    /**
     * Emitted when the player made an invalid move.
     */
    signal playerMadeInvalidMove(int columnNo);

    /**
     * Id of the current player (1 or 2).
     *
     * 0 means no player is currently active.
     */
    property var currentPlayerId: 0

    /**
     * Name of the first player.
     */
    property string firstPlayerName: ""

    /**
     * Name of the second player.
     */
    property string secondPlayerName: ""

    /**
     * Number of columns in the game board.
     */
    property int nColumns: 0

    /**
     * Number of rows in the game board.
     */
    property int nRows: 0

    /**
     * Array containing indexes of available columns.
     *
     * This array is empty when no move is requested or no column is available.
     */
    property var availableColumns: []

    /**
     * Reference to the controls.
     */
    property Controls controls: null

    /**
     * Whether a game is running or not.
     */
    property bool inGame: false

    /**
     * Whether there is a time limit or not.
     */
    property bool hasTimeLimit: false

    /**
     * Starts a new game.
     *
     * @param nColumns Number of columns in the board.
     * @param nRows Number of rows in the board.
     * @param firstPlayerName Name of the first player.
     * @param secondPlayerName Name of the second player.
     * @param hasTimeLimit Whether the game has a time limit or not.
     */
    function startGame(nColumns, nRows, firstPlayerName, secondPlayerName, hasTimeLimit)
    {
        game.nColumns = nColumns;
        game.nRows = nRows;
        game.firstPlayerName = firstPlayerName;
        game.secondPlayerName = secondPlayerName;
        game.currentPlayerId = 0;
        game.inGame = true;
        game.hasTimeLimit = hasTimeLimit;
    }

    /**
     * Ends/closes current game.
     */
    function endGame()
    {
        game.inGame = false;
        game.currentPlayerId = 0;
    }

    /**
     * Begins a new turn for the player with the given id.
     *
     * @param playerId Id of the player.
     */
    function beginTurn(playerId)
    {
        game.currentPlayerId = playerId;
    }

    /**
     * Ends the current turn.
     */
    function endTurn(playerId)
    {
        game.currentPlayerId = 0;

        game.controls.endRequestMove();
    }

    /**
     * Requests a new move.
     *
     * @param availableColumns Array containing column indexes of available columns.
     * @param allowMouse Whether the user is allowed to use the mouse for input.
     * @param allowKeyboard Whether the user is allowed to use the keyboard for input.
     */
    function requestMove(availableColumns, allowMouse, allowKeyboard)
    {
        game.availableColumns = availableColumns;

        game.controls.requestMove(allowMouse, allowKeyboard);
    }

    /**
     * Returns whether a token can be dropped in the column with the given number/index.
     *
     * This method will always return false when no move is currently requested.
     *
     * @param columnNo Index/number of the column to check.
     */
    function isColumnAvailable(columnNo)
    {
        var isAvailable = false;

        for (var i = 0; i < game.availableColumns.length; ++i)
        {
            if (game.availableColumns[i] === columnNo)
            {
                isAvailable = true;
                break;
            }
            else if (game.availableColumns[i] > columnNo)
            {
                break;
            }
        }

        return isAvailable;
    }

    /**
     * Tries to drop a token in the given column.
     *
     * Emits playerMadeMove/playerMadeInvalidMove.
     *
     * @param columnNo Index/number of the column.
     */
    function tryToDropToken(columnNo)
    {
        if (game.isColumnAvailable(columnNo))
        {
            game.playerMadeMove(columnNo);
        }
        else
        {
            game.playerMadeInvalidMove(columnNo);
        }
    }
}
