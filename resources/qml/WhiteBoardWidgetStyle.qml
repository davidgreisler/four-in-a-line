import QtQuick 2.3

/**
 * White/blue style for board widget.
 */
AbstractStyle
{
    id: style

    /**
     * Cell spacing.
     */
    property real cellSpacing: 0

    /**
     * Border width.
     */
    property real borderWidth: Math.floor((_widget.height / 100) * 6)

    /**
     * Width of the board widget.
     */
    property real widgetWidth: gridWidth + (borderWidth * 2)

    /**
     * Height of a cell in pixels.
     */
    property real cellHeight: Math.floor(((_widget.height - borderWidth * 2)) / _widget.nRows)

    /**
     * Width of a cell in pixels.
     */
    property real cellWidth: cellHeight

    /**
     * X coordinate of the grid.
     */
    property real gridX: borderWidth

    /**
     * Y coordinate of the grid.
     */
    property real gridY: borderWidth

    /**
     * Z coordinate of the grid.
     */
    property real gridZ: 3

    /**
     * Width of the grid.
     */
    property real gridWidth: _widget.nColumns * _widget.cellWidth

    /**
     * Height of the grid.
     */
    property real gridHeight: _widget.nRows * _widget.cellHeight

    /**
     * Positioning isn't 100% exact, therefore this helper is used to hide
     * ugly gaps that would be visible without it.
     */
    Rectangle
    {
        id: helperBackground
        parent: _widget

        x: Math.ceil(borderWidth / 2)
        y: Math.ceil(borderWidth / 2)
        z: 1
        width: widgetWidth - Math.ceil(borderWidth)
        height: _widget.height - Math.ceil(borderWidth)

        color: "#23426b"
        radius: 5
    }

    /**
     * Rounded border around the board.
     */
    Rectangle
    {
        id: border
        parent: _widget

        x: 0
        y: 0
        z: 4
        width: widgetWidth
        height: _widget.height

        color: "#00000000"
        border.color: "#23426b"
        border.width: borderWidth
        radius: 15
    }

    /**
     * Background of the board.
     */
    Rectangle
    {
        id: background
        parent: _widget

        x: borderWidth
        y: borderWidth
        z: 2
        width: gridWidth
        height: gridHeight

        color: "#061b37"
    }

    /**
     * Board cells (foreground).
     */
    Grid
    {
        id: foreground
        parent: _widget

        x: borderWidth
        y: borderWidth
        z: 4
        width: gridWidth
        height: gridHeight

        rows: _widget.nRows
        columns: _widget.nColumns

        Repeater {
            model: _widget.nColumns * _widget.nRows
            Image {
                id: boardTile
                width: style.cellWidth
                height: style.cellHeight
                source: "images/boardTileBlue.svg"
                smooth: true
                mipmap: true
            }
        }
    }
}
