import QtQuick 2.0

/**
 * Abstract widget style.
 */
Item
{
    /**
     * The styled widget.
     *
     * _styleWidget is set by the style loader (see AbstractWidget.qml).
     */
    readonly property AbstractWidget _widget: _styleWidget
}
