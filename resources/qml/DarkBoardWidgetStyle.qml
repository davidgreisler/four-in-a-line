import QtQuick 2.3

/**
 * Dark style for board widget.
 */
AbstractStyle
{
    id: style

    property real cellSpacing: Math.ceil(_widget.cellWidth * 0.05)

    /**
     * Width of the board widget.
     */
    property real widgetWidth: gridWidth

    /**
     * Height of a cell in pixels.
     */
    property real cellHeight: Math.floor(_widget.height / _widget.nRows)

    /**
     * Width of a cell in pixels.
     */
    property real cellWidth: cellHeight

    /**
     * X coordinate of the grid.
     */
    property real gridX: 0

    /**
     * Y coordinate of the grid.
     */
    property real gridY: 0

    /**
     * Z coordinate of the grid.
     */
    property real gridZ: 3

    /**
     * Width of the grid.
     */
    property real gridWidth: _widget.nColumns * _widget.cellWidth + (cellSpacing * (_widget.nColumns - 1))

    /**
     * Height of the grid.
     */
    property real gridHeight: _widget.nRows * _widget.cellHeight + (cellSpacing * (_widget.nRows - 1))

    /**
     * Board cells (background).
     */
    Grid
    {
        id: background
        parent: _widget

        x: 0
        y: 0
        z: 1
        width: gridWidth
        height: gridHeight
        spacing: cellSpacing

        rows: _widget.nRows
        columns: _widget.nColumns

        Repeater
        {
            model: _widget.nColumns * _widget.nRows
            Rectangle
            {
                id: boardTile
                width: style.cellWidth
                height: style.cellHeight
                color: "#222222"
            }
        }
    }
}
