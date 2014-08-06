import QtQuick 2.0

/**
 * Default style for column indicator widgets.
 */
AbstractStyle
{
    id: style

    /**
     * The background.
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

        color: "#80dcd4c7"
        radius: 3
    }

    /**
     * The column score box.
     */
    Rectangle
    {
        id: columnScoreBox
        parent: _widget

        x: 0
        y: (_widget.height / 100) * -50
        z: 2
        width: _widget.width
        height: (_widget.height / 100) * 30

        color: "#dcd4c7"
        radius: 5
        opacity: 0
        visible: true
        border.width: 0

        /**
         * The column score text.
         */
        Text
        {
            id: columnScoreText
            x: (parent.width / 100) * 10
            y: (parent.height / 100) * 10
            width: (parent.width / 100) * 80
            height: (parent.height / 100) * 80
            color: (_widget.columnScore >= 0) ? "#40822b" : "#ad3906"
            text: _widget.columnScore
            font.family: "Verdana"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: (parent.height / 100) * 50
        }
    }

    states: [
        State {
            name: "isActive"
            when: _widget.isActive === true && _widget.showScore === false

            PropertyChanges {
                target: background
                color: "#ffdcd4c7"
            }
        },
        State {
            name: "isFull"
            when: _widget.isAvailable === true

            PropertyChanges {
                target: background
                color: "#00dcd4c7"
            }
        },
        State {
            name: "showScore"
            when: _widget.isActive === false && _widget.showScore === true

            PropertyChanges {
                target: columnScoreBox
                y: (parent.height / 100) * -35
                opacity: 1
            }
        },
        State {
            name: "isActiveAndShowScore"
            when: _widget.isActive === true && _widget.showScore === true

            PropertyChanges {
                target: columnScoreBox
                y: (parent.height / 100) * -35
                opacity: 1
            }

            PropertyChanges {
                target: background
                color: "#ffdcd4c7"
            }
        }
    ]

    transitions: [
        Transition {
            PropertyAnimation {
                properties: "color, opacity, y"
                duration: 500
            }
        }
    ]
}
