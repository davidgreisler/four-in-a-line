import QtQuick 2.0

/**
 * Default style for column indicator bar widgets.
 */
AbstractStyle
{
    id: style

    /**
     * Indicator row spacing.
     */
    property int indicatorRowSpacing: 5

    /**
     * Opacity of the indicator bar.
     */
    property real indicatorRowOpacity: 0.0

    /**
     * Bottom margin for the indicator row.
     */
    property int indicatorRowBottomMargin: -(_widget.height)

    /**
     * Style for column indicator widgets.
     */
    property Component columnIndicatorStyle: ColumnIndicatorWidgetStyle {}

    states: [
        State
        {
            name: "showIndicatorBar"
            when: _widget.moveRequested === true

            PropertyChanges
            {
                target: style
                indicatorRowOpacity: 1.0
            }

            PropertyChanges
            {
                target: style
                indicatorRowBottomMargin: 0
            }
        }
    ]

    transitions: [
        Transition
        {
            PropertyAnimation
            {
                properties: "indicatorRowOpacity, indicatorRowBottomMargin"
                duration: 500
            }
        }
    ]
}
