import QtQuick 2.0

/**
 * Dark style for column indicator widgets.
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
        z: 2
        width: _widget.width
        height: _widget.height

        color: "#00000000"
        border.color: "#1999b9"
        border.width: _widget.width * 0.03
    }

    /**
     * The column score box.
     */
    Rectangle
    {
        id: columnScoreBox
        parent: _widget

        x: background.x
        y: background.y
        z: 3
        width: background.width
        height: background.height

        color: "#00000000"
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
            color: "#ffffff"
            text: _widget.columnScore
            font.family: "Verdana"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: (parent.height / 100) * 20
        }
    }

    states: [
        State {
            name: "isFull"
            when: _widget.isAvailable === true

            PropertyChanges {
                target: background
                border.width: 0
            }
        },
        State {
            name: "showScore"
            when: _widget.isActive === false && _widget.showScore === true

            PropertyChanges {
                target: columnScoreBox
                opacity: 1
            }
        },
        State {
            name: "isActiveAndShowScore"
            when: _widget.isActive === true && _widget.showScore === true

            PropertyChanges {
                target: columnScoreBox
                opacity: 1
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
