import QtQuick 2.0

/**
 * Game information widget style.
 */
AbstractStyle
{
    id: style

    /**
     * X coordinate of the first player information widget.
     */
    property int firstPlayerX: 0

    /**
     * X coordinate of the time limit widget.
     */
    property int timeLimitX: _widget.hasTimeLimit ? (_widget.width / 100) * 35.5 : 9999

    /**
     * X coordinate of the second player widget.
     */
    property int secondPlayerX: _widget.hasTimeLimit ? (_widget.width / 100) * 67 : (_widget.width / 100) * 52

    /**
     * Width of the first player widget.
     */
    property int firstPlayerWidth: _widget.hasTimeLimit ? (_widget.width / 100) * 33 : (_widget.width / 100) * 48

    /**
     * Width of the time limit widget.
     */
    property int timeLimitWidth: _widget.hasTimeLimit ? (_widget.width / 100) * 29 : 0

    /**
     * Width of the second player widget.
     */
    property int secondPlayerWidth: _widget.hasTimeLimit ? (_widget.width / 100) * 33 : (_widget.width / 100) * 48

    /**
     * Y coordinate of the container.
     */
    property int containerY: -(_widget.height * 1.3)

    /**
     * Style for player information widgets.
     */
    property Component playerInformationStyle: PlayerInformationWidgetStyle {}

    /**
     * Style for time limit widget.
     */
    property Component timeLimitStyle: TimeLimitWidgetStyle {}

    states: [
        State
        {
            name: "inGame"
            when: _widget.inGame === true

            PropertyChanges
            {
                target: style
                containerY: 0
            }
        }
    ]

    transitions: [
        Transition
        {
            PropertyAnimation
            {
                target: style
                properties: "containerY"
                duration: 500
            }
        }

    ]
}
