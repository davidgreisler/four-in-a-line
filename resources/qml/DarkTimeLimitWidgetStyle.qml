import QtQuick 2.0

/**
 * Dark style for the time limit widget.
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
     * "Remaining time" text.
     */
    Text
    {
        id: remainingTimeText
        parent: _widget

        x: (_widget.width / 10)
        y: (_widget.height / 10) * 2
        z: 2
        width: (_widget.width / 10) * 8
        height: (_widget.height / 10) * 2

        text: qsTr("Remaining time")
        color: "#ffffff"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: (_widget.height / 100.0) * 20.0
    }

    /**
     * Displays remaining time as "mm:ss".
     */
    Text
    {
        id: remainingTime
        parent: _widget

        x: (_widget.width / 10)
        y: (_widget.height / 10) * 4
        z: 2
        width: (_widget.width / 10) * 8
        height: (_widget.height / 10) * 5

        color: "#1999b9"
        text: _widget.createTimeString(_widget.remainingMinutes, _widget.remainingSeconds)
        transformOrigin: Item.Center
        font.bold: true
        font.family: "Verdana"
        font.pixelSize: Math.floor((_widget.height / 100.0) * 30.0)
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    /**
     * Animation that is played when the player should hurry up.
     */
    SequentialAnimation
    {
        id: pulsatingTime
        running: false
        loops: Animation.Infinite

        PropertyAnimation {
            target: remainingTime
            property: "scale"
            duration: 500
            to: 1.3
        }
        PropertyAnimation {
            target: remainingTime
            property: "scale"
            duration: 500
            to: 1.0
        }
    }

    states: [
        State {
            name: "hurryUp"
            when: (_widget.remainingMinutes === 0 && _widget.remainingSeconds < 10)

            PropertyChanges
            {
                target: remainingTime
                color: "#e716a9"
            }

            PropertyChanges
            {
                target: pulsatingTime
                running: true
            }
        }
    ]
}
