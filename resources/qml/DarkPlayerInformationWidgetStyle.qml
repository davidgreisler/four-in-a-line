import QtQuick 2.0

/**
 * Dark style for player information widget.
 */
AbstractStyle
{
    id: style

    /**
     * Background.
     */
    Rectangle
    {
        id: background
        parent: _widget

        x: 0
        y: 0
        z: 1
        width: _widget.width
        height: _widget.height

        color: "#000000"
        radius: 0
    }

    /**
     * Displays player name.
     */
    Text
    {
        id: playerNameText
        parent: _widget

        x: (_widget.width / 10)
        y: (_widget.height / 10)
        z: 2
        width: (_widget.width / 10) * 8
        height: (_widget.height / 10) * 8

        color: "#ffffff"
        text: _widget.playerName
        font.bold: false
        font.family: "Verdana"
        font.pixelSize: (_widget.height / 10) * 3
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    states: [
        State
        {
            name: "isActive"
            when: _widget.isActive === true

            PropertyChanges
            {
                target: background
                color: _widget.playerId === 1 ? "#1999b9" : "#e716a9"
            }

            PropertyChanges
            {
                target: playerNameText
                color: "#000000"
            }
        }
    ]
}
