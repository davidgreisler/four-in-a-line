import QtQuick 2.0

/**
 * Abstract widget that can be styled.
 */
Item
{
    id: _abstractWidget

    /**
     * Style of this widget.
     */
    property Component style

    /**
     * The actual style component.
     */
    property alias _style: _styleLoader.item

    /**
     * Loads the style.
     */
    Loader
    {
        id: _styleLoader
        sourceComponent: style
        property Item _styleWidget: _abstractWidget
        onStatusChanged: {
            if (status === Loader.Error)
            {
                console.error("Failed to load style for widget: " + _abstractWidget);
            }
        }
    }
}
