import QtQuick 2.0

/**
 * Game information widget, shows player/time limit information.
 */
AbstractWidget
{
    id: root

    style: GameInformationWidgetStyle {}

    /**
     * Name of the first player.
     */
    property alias firstPlayerName: firstPlayerInformationWidget.playerName

    /**
     * Name of the second player.
     */
    property alias secondPlayerName: secondPlayerInformationWidget.playerName

    /**
     * Id of the currently active player (1 or 2).
     */
    property int activePlayerId: null

    /**
     * Whether a game is running or not.
     */
    property bool inGame: false

    /**
     * Whether there is a time limit or not.
     */
    property bool hasTimeLimit: false

    /**
     * First player information widget.
     */
    property alias firstPlayerWidget: firstPlayerInformationWidget

    /**
     * Second player information widget.
     */
    property alias secondPlayerWidget: secondPlayerInformationWidget

    /**
     * Time limit widget.
     */
    property alias timeLimitWidget: timeLimitDisplay

    /**
     * Container for the 3 widgets.
     */
    property alias container: container

    /**
     * Container for the 3 widgets to make it easier to move them together.
     */
    Item
    {
        id: container
        y: root._style.containerY

        /**
         * Player information widget for the first player.
         */
        PlayerInformationWidget
        {
            id: firstPlayerInformationWidget
            isActive: (activePlayerId === 1) ? true : false
            style: root._style.playerInformationStyle
            playerId: 1

            x: root._style.firstPlayerX
            y: 0
            width: root._style.firstPlayerWidth
            height: root.height
        }

        /**
         * Displays remaining time.
         */
        TimeLimitWidget
        {
            id: timeLimitDisplay
            style: root._style.timeLimitStyle

            x: root._style.timeLimitX
            y: 0
            width: root._style.timeLimitWidth
            height: root.height
        }

        /**
         * Player information widget for the second player.
         */
        PlayerInformationWidget
        {
            id: secondPlayerInformationWidget
            isActive: (activePlayerId === 2) ? true : false
            style: root._style.playerInformationStyle
            playerId: 2

            x: root._style.secondPlayerX
            y: 0
            width: root._style.secondPlayerWidth
            height: root.height
        }
    }

    /**
     * Updates the remaining time.
     *
     * @param totalMinutes Time limit (minutes part).
     * @param totalSeconds Time limit (seconds part).
     * @param remainingMinutes Remaining time (minutes part).
     * @param remainingSeconds Remaining time (seconds part).
     */
    function updateRemainingTime(totalMinutes, totalSeconds, remainingMinutes, remainingSeconds)
    {
        timeLimitDisplay.updateRemainingTime(totalMinutes, totalSeconds, remainingMinutes, remainingSeconds);
    }
}
