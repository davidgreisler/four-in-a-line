import QtQuick 2.0

/**
 * Column indicator bar widget.
 */
AbstractWidget
{
    id: columnIndicatorBar

    style: ColumnIndicatorBarWidgetStyle {}

    /**
     * Emitted when the player made a move.
     */
    signal playerMadeMove(int columnNo);

    /**
     * Number of columns to display.
     */
    property int nColumns: 5

    /**
     * Whether a move is requested.
     */
    property bool moveRequested: false

    /**
     * Column indicator currently hovered by the token.
     */
    property ColumnIndicatorWidget currentColumn: null

    /**
     * Width of one column including spacing.
     */
    property int columnWidth: (columnIndicatorBar.width / nColumns)

    /**
     * The current token.
     */
    property Token currentToken: null

    /**
     * Half width of the current token in pixels.
     */
    property int currentTokenHalfWidth: (null == currentToken) ? 0 : currentToken.tokenWidth / 2

    /**
     * The game board, used to create tokens.
     */
    property BoardWidget gameBoard: null

    /**
     * Row containing indicator widgets.
     */
    property alias indicatorRow: indicatorRow

    /**
     * Row containing indicator widgets.
     */
    Row
    {
        id: indicatorRow
        spacing: columnIndicatorBar._style.indicatorRowSpacing
        opacity: columnIndicatorBar._style.indicatorRowOpacity
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: columnIndicatorBar.bottom
        anchors.bottomMargin: columnIndicatorBar._style.indicatorRowBottomMargin

        Repeater
        {
             model: columnIndicatorBar.nColumns
             ColumnIndicatorWidget
             {
                 style: columnIndicatorBar._style.columnIndicatorStyle
                 width: (columnIndicatorBar.width / nColumns) - 5
                 height: Math.min(columnIndicatorBar.height, (columnIndicatorBar.width / nColumns) - 5)
             }
        }

        onYChanged: _updateCurrentTokenYPosition();
    }

    /**
     * Initializes column indicator bar.
     *
     * @param nColumnsNew New number of columns.
     */
    function init(nColumnsNew)
    {
        columnIndicatorBar.nColumns = nColumnsNew;
        columnIndicatorBar.currentToken = null;
    }

    /**
     * Sets column scores to the given scores.
     *
     * @param scores List of scores.
     */
    function setColumnScores(scores)
    {
        for (var i = 0; i < nColumns; ++i)
        {
            indicatorRow.children[i].columnScore = scores[i];
        }
    }

    /**
     * Shows/hides column scores.
     *
     * @param show Whether to show the scores (true) or hide them (false).
     */
    function setShowColumnScores(show)
    {
        for (var i = 0; i < nColumns; ++i)
        {
            indicatorRow.children[i].showScore = show;
        }
    }

    /**
     * Moves the token one column to the left if possible.
     */
    function moveTokenLeft()
    {
        var currentColumnNo = getCurrentColumn();

        if (currentColumnNo > 0)
        {
            setCurrentColumn(currentColumnNo - 1);
        }
    }

    /**
     * Moves the token one column to the right if possible.
     */
    function moveTokenRight()
    {
        var currentColumnNo = getCurrentColumn();

        if (currentColumnNo < (nColumns - 1))
        {
            setCurrentColumn(currentColumnNo + 1);
        }
    }

    /**
     * Moves the current token to the current position of the mouse.
     *
     * @param x X coordinate of the position.
     * @param y Y coordinate of the position.
     */
    function moveTokenToMousePosition(x, y)
    {
        if (moveRequested)
        {
            var barPosition = mapToItem(columnIndicatorBar, x, y);

            setTokenPosition(barPosition.x);
        }
    }

    /**
     * Returns the column number of the column that is currently hovered by the token.
     */
    function getCurrentColumn()
    {
        // X coordinate of the current token.

        var tokenX = currentToken.x;

        // X coordinate of the center of the current token.

        tokenX += currentTokenHalfWidth;

        // X coordinate of the center of the current token relative to the indicator row's x coordinate.

        tokenX -= _getIndicatorRowX();

        return Math.floor(tokenX / columnWidth);
    }

    /**
     * Positions the token over the column with the given number.
     *
     * @param columnNo Column index/number.
     */
    function setCurrentColumn(columnNo)
    {
        var tokenX = columnNo * (columnIndicatorBar.width / nColumns);

        tokenX += currentTokenHalfWidth;

        tokenX += _getIndicatorRowX();

        setTokenPosition(tokenX);
    }

    /**
     * Sets the position of the token to the given position.
     */
    function setTokenPosition(positionX)
    {
        var indicatorRowStartX = _getIndicatorRowX();
        var indicatorRowEndX = indicatorRowStartX + (indicatorRow.width - currentToken.tokenWidth);

        // Token should be centered to the given position.

        positionX -= currentTokenHalfWidth;
        positionX += indicatorRowStartX;

        // Do not position token outside the indicator bar.

        if (positionX > indicatorRowEndX)
        {
            positionX = indicatorRowEndX;
        }

        if (positionX < indicatorRowStartX)
        {
            positionX = indicatorRowStartX;
        }

        // Set position.

        currentToken.x = positionX;

        // Update indicator.

        var columnIndicator = indicatorRow.childAt(positionX + currentTokenHalfWidth, 2);
        if (null !== columnIndicator)
        {
            if (null !== currentColumn)
            {
                currentColumn.isActive = false;
            }

            if (!columnIndicator.isAvailable)
            {
                columnIndicator.isActive = true;
            }

            currentColumn = columnIndicator;
        }
    }

    /**
     * Returns the current token and takes ownership away.
     */
    function takeToken()
    {
        var result = currentToken;
        currentToken = null;

        return result;
    }

    /**
     * Shows the column indicator bar and allows the user to make a move.
     */
    function requestMove(availableColumns, playerId, token)
    {
        if (availableColumns.length === 0)
        {
            console.log("ERROR: No columns available.");
            return;
        }

        var columnAvailable = [];
        var i;

        for (i = 0; i < columnIndicatorBar.nColumns; ++i)
        {
            columnAvailable[columnAvailable.length] = false;
        }

        for (i = 0; i < availableColumns.length; ++i)
        {
            var columnNo = availableColumns[i];
            columnAvailable[columnNo] = true;
        }

        for (i = 0; i < columnAvailable.length; ++i)
        {
            indicatorRow.children[i].isAvailable = !columnAvailable[i];
        }

        columnIndicatorBar.moveRequested = true;
        createToken(availableColumns[0], token);
    }

    /**
     * Hides the column indicator bar again.
     */
    function endRequestMove()
    {
        columnIndicatorBar.moveRequested = false;
    }

    /**
     * Creates a new token over the given column.
     */
    function createToken(columnNo, token)
    {
        var tokenY = indicatorRow.y;

        token.x = 0;
        token.y = tokenY;

        columnIndicatorBar.currentToken = token;

        _updateCurrentTokenYPosition();
        setTokenPosition(columnNo);

        token.isVisible = true;
    }

    /**
     * Updates/corrects the Y position of the current token.
     *
     * The current token has the game board as parent, which is why after changes to
     * the y position of the column indicator bar/after creating a new token it is
     * necessary to map the Y position to this item.
     */
    function _updateCurrentTokenYPosition()
    {
        if (currentToken != null && gameBoard != null)
        {
            var mappedObject = indicatorRow.mapToItem(gameBoard, 0, 0);

            var tokenY = mappedObject.y;

            // Adjust position in case the indicator bar is not shown (AI move/replay).

            tokenY -= Math.abs(indicatorRow.anchors.bottomMargin);

            currentToken.y = tokenY;
        }
    }

    /**
     * Returns the X coordinate of the indicator row relative to the game board.
     */
    function _getIndicatorRowX()
    {
        var mappedToBoard = indicatorRow.mapToItem(gameBoard, 0, 0);

        var indicatorRowX = mappedToBoard.x;

        return indicatorRowX;
    }
}
