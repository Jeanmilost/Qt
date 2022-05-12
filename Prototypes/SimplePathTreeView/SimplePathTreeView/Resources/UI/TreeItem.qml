import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Tree item
*@author Jean-Milost Reymond
*/
Item
{
    // declared properties
    property var m_View:          undefined
    property var m_Delegate:      undefined // FIXME create a default delegate?
    property int m_ChildrenCount: 0

    // common properties
    id: itItem
    objectName: "itItem"

    width: parent.width

    Loader
    {
        id: ldContent
        anchors.fill: parent

        sourceComponent: m_Delegate
    }

    /**
    * Children repeater
    */
    Repeater
    {
        // common properties
        id: rpItemRepeater
        objectName: "rpItemRepeater"
        model: m_ChildrenCount
        delegate: m_Delegate
    }
}
