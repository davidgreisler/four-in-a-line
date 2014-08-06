import QtQuick 2.0

/**
 * Game board widget.
 */
AbstractWidget
{
    id: board

    width: _style.widgetWidth

    /**
     * Style for this widget.
     */
    style: BoardWidgetStyle {}

    /**
     * Number of columns.
     */
    property int nColumns: 5

    /**
     * Number of rows.
     */
    property int nRows: 5

    /**
     * Number of cells in the board.
     */
    property int nCells: nColumns * nRows

    /**
     * Used for determining the size of tokens.
     */
    property int cellWidth: _style.cellWidth

    /**
     * Used for determining the size of tokens.
     */
    property int cellHeight: _style.cellHeight

    /**
     * Grid containing the tokens.
     */
    Grid
    {
        id: boardGrid

        x: _style.gridX
        y: _style.gridY
        z: _style.gridZ
        width: _style.gridWidth
        height: _style.gridHeight
        spacing: _style.cellSpacing

        rows: board.nRows
        columns: board.nColumns

        Repeater {
            model: board.nCells
            Cell {
                mapTarget: board
                width: _style.cellWidth
                height: _style.cellHeight
            }
        }
    }

    /**
     * Returns the cell at the given position.
     *
     * @param columnNo Column number.
     * @param rowNo Row number.
     * @return The cell at the given position.
     */
    function getCellAt(columnNo, rowNo)
    {
        var cell = boardGrid.children[(rowNo * nColumns) + columnNo];

        return cell;
    }
}
