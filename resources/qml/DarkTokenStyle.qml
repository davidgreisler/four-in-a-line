import QtQuick 2.3
import QtGraphicalEffects 1.0

/**
 * Dark style for tokens.
 */
AbstractStyle
{
    id: style

    /**
     * Horizontal move animation.
     */
    property alias horizontalAnimation: horizontalAnimation

    /**
     * Vertical move animation.
     */
    property alias verticalAnimation: verticalAnimation

    /**
     * Drop animation.
     */
    property alias dropAnimation: dropAnimation

    /**
     * Animation played when a token is highlighed.
     */
    property alias highlightAnimation: highlightAnimation

    /**
     * Width of the token.
     */
    property alias tokenWidth: tokenImage.width

    /**
     * Height of the token.
     */
    property alias tokenHeight: tokenImage.height

    /**
     * Token rectangle.
     */
    Rectangle
    {
        id: tokenImage
        parent: _widget.parent

        x: _widget.x
        y: _widget.y
        z: 2
        width: _widget.board.cellWidth
        height: _widget.board.cellHeight

        opacity: 0.0
        color: (_widget.playerId === 1) ? "#1999b9" : "#e716a9"
    }

    /**
     * Color overlay used to animate token when highlighted.
     */
    ColorOverlay
    {
        id: colorOverlay
        parent: _widget.parent

        z: 3
        color: "#ffffff"
        anchors.fill: tokenImage
        source: tokenImage
        opacity: 0.0
    }

    states: [
        State
        {
            name: "isVisible"
            when: _widget.isVisible === true && _widget.isHighlighted === false

            PropertyChanges
            {
                target: tokenImage
                opacity: 1.0
            }
        },
        State
        {
            name: "highlight"
            when: _widget.isVisible === true && _widget.isHighlighted === true

            PropertyChanges
            {
                target: tokenImage
                opacity: 1.0
            }

            PropertyChanges
            {
                target: highlightAnimation
                running: true
            }
        }
    ]

    transitions: [
        Transition
        {
            PropertyAnimation
            {
                target: tokenImage
                properties: "opacity"
                duration: 500
            }
        }
    ]

    NumberAnimation
    {
        id: horizontalAnimation
        target: tokenImage
        to: _widget.destinationX
        duration: 200
    }

    NumberAnimation
    {
        id: verticalAnimation
        target: tokenImage
        to: _widget.destinationY
        duration: 500
    }

    SequentialAnimation
    {
        id: highlightAnimation
        running: false
        loops: Animation.Infinite
        alwaysRunToEnd: true

        NumberAnimation
        {
            target: colorOverlay
            property: "opacity"
            to: 0.5
            duration: 1000
        }

        NumberAnimation
        {
            target: colorOverlay
            property: "opacity"
            to: 0.0
            duration: 1000
        }
    }

    SequentialAnimation
    {
        id: dropAnimation
        running: false

        NumberAnimation
        {
            target: tokenImage
            property: "x"
            to: _widget.destinationX
            duration: 150
        }

        NumberAnimation
        {
            target: tokenImage
            property: "y"
            to: _widget.destinationY
            duration: 550
            easing
            {
                type: Easing.OutBounce
                amplitude: 0.5
                period: 0.5
            }
        }
    }
}
