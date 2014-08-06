import QtQuick 2.0

/**
 * Column indicator widget.
 */
AbstractWidget
{
    id: columnIndicator
    style: ColumnIndicatorWidgetStyle {}

    /**
     * Score of this column (only set when the user invoked the hint function).
     *
     * Ranges from -100 to 100.
     */
    property int columnScore: 0

    /**
     * Whether to show the column score or not.
     */
    property bool showScore: false

    /**
     * Whether the column is hovered or not.
     */
    property bool isActive: false

    /**
     * Whether it is possible to drop a token in this column or not.
     */
    property bool isAvailable: false
}
