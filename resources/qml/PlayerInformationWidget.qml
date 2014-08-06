import QtQuick 2.0

/**
 * Player information widget.
 */
AbstractWidget
{
    id: playerInformation

    /**
     * Name of the player.
     */
    property string playerName: "Unknown player"

    /**
     * Whether it's the player's turn or not.
     */
    property bool isActive: false

    /**
     * Player id.
     */
    property int playerId: 0

    style: PlayerInformationWidgetStyle {}
}
