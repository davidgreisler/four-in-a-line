import QtQuick 2.0

Item
{
    id: gameView

    /**
     * Used to create/manage tokens.
     */
    TokenFactory
    {
        id: tokenManager
        tokenStyle: DarkTokenStyle {}
    }

    /**
     * Controls game flow.
     */
    GameController
    {
        id: gameController
        objectName: "gameController"
    }

    /**
     * Background.
     */
    Rectangle
    {
        id: background
        width: parent.width
        height: parent.height
        color: "#111111"
    }

    /**
     * Game information (player names/time limit) at the top.
     */
    GameInformationWidget
    {
        id: gameInfo
        firstPlayerName: gameController.firstPlayerName
        secondPlayerName: gameController.secondPlayerName
        activePlayerId: gameController.currentPlayerId
        inGame: gameController.inGame
        hasTimeLimit: gameController.hasTimeLimit

        x: 0
        y: 0
        width: parent.width
        height: (parent.height / 100) * 10

        style: GameInformationWidgetStyle {
            playerInformationStyle: DarkPlayerInformationWidgetStyle {}
            timeLimitStyle: DarkTimeLimitWidgetStyle {}
        }
    }

    Item
    {
        id: container

        x: 0
        anchors.top: gameInfo.bottom
        anchors.topMargin: parent.height
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.02
        width: parent.width

        BoardWidget
        {
            id: gameBoard
            nColumns: gameController.nColumns
            nRows: gameController.nRows

            z: 1
            height: (parent.height / 100) * 76
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: (parent.height / 100) * 2
            anchors.top: columnIndicatorBar.bottom
            anchors.topMargin: (parent.height / 100) * 2

            style: DarkBoardWidgetStyle {}
        }

        Controls
        {
            id: controls

            anchors.top: columnIndicatorBar.top
            anchors.left: columnIndicatorBar.left
            anchors.right: columnIndicatorBar.right
            anchors.bottom: gameBoard.bottom

            onMoveLeft: columnIndicatorBar.moveTokenLeft();
            onMoveRight: columnIndicatorBar.moveTokenRight();
            onMoveToCursor: columnIndicatorBar.moveTokenToMousePosition(x, y);
            onDrop: gameController.tryToDropToken(columnIndicatorBar.getCurrentColumn());
        }

        ColumnIndicatorBarWidget
        {
            id: columnIndicatorBar
            nColumns: gameController.nColumns

            width: gameBoard.width
            height: (parent.height / 100) * 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: (parent.height / 100) * 2

            gameBoard: gameBoard
            style: DarkColumnIndicatorBarWidgetStyle {}
        }

        // Hide container when no game is being played.

        states: [
            State
            {
                name: "inGame"
                when: gameController.inGame === true

                PropertyChanges
                {
                    target: container
                    anchors.topMargin: 0
                }
            }
        ]

        transitions: [
            Transition
            {
                PropertyAnimation
                {
                    target: container
                    properties: "anchors.topMargin"
                    duration: 500
                }
            }

        ]
    }

    Connections {
        target: Game
        onNewGameStarted: {
            columnIndicatorBar.init(nColumns);
            columnIndicatorBar.setShowColumnScores(false);

            tokenManager.destroyAllTokens(0);

            gameInfo.updateRemainingTime(0, 0, 0, 0);

            gameController.startGame(nColumns, nRows, firstPlayerName, secondPlayerName, hasTimeLimit);
        }

        onGameEnded: {
            gameController.endGame();
        }

        onRemainingTimeUpdated: {
            gameInfo.updateRemainingTime(totalMinutes, totalSeconds, remainingMinutes, remainingSeconds);
        }

        onFirstPlayerTurn: {
            gameController.beginTurn(1);
        }

        onSecondPlayerTurn: {
            gameController.beginTurn(2);
        }

        onPlayerTurnEnded: {
            columnIndicatorBar.endRequestMove();
            columnIndicatorBar.setShowColumnScores(false);
            gameController.endTurn();
        }

        onMoveRequested: {
            gameController.requestMove(availableColumns, allowMouse, allowKeyboard);

            var token = tokenManager.createToken(gameController.currentPlayerId, gameBoard, gameBoard);
            columnIndicatorBar.requestMove(availableColumns, gameController.currentPlayerId, token);

            if (allowMouse)
            {
                controls.emitMoveToCursor();
            }
        }

        onMoveRequestAborted: {
            columnIndicatorBar.endRequestMove();
            columnIndicatorBar.setShowColumnScores(false);

            var token = columnIndicatorBar.takeToken();
            if (null !== token)
            {
                tokenManager.destroyToken(token, 0);
            }
        }

        onTokenDropped: {
            var token = columnIndicatorBar.takeToken();
            if (null === token)
            {
                // AI/Network move.

                token = tokenManager.createToken(gameController.currentPlayerId, gameBoard, gameBoard);
                columnIndicatorBar.createToken(x, token);
                token = columnIndicatorBar.takeToken();

                if (null === token)
                {
                    console.log("ERROR: Failed to create token.");
                }
            }

            var cell = gameBoard.getCellAt(x, y);
            cell.dropToken(token);
        }

        onTokenRemoved: {
            var cell = gameBoard.getCellAt(x, y);
            var token = cell.takeToken();

            token.isVisible = false;
            token.moveToY(0);

            tokenManager.destroyToken(token, 1000);
        }

        onCellHighlightedChanged: {
            // The highlighting feature is only used to highlight cells with tokens.

            var cell = gameBoard.getCellAt(x, y);
            var token = cell.token;
            if (token)
            {
                token.isHighlighted = highlight;
            }
        }

        onColumnHintsShown: {
            columnIndicatorBar.setColumnScores(columnScores);
            columnIndicatorBar.setShowColumnScores(true);
        }
    }

    Component.onCompleted: {
        gameController.controls = controls;
    }
}
