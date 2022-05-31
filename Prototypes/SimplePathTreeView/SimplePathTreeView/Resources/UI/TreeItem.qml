import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Generic tree item
*@author Jean-Milost Reymond
*/
Column
{
    // declared properties
    property var m_Component: null

    // common properties
    id: clItem
    objectName: "clItem"
    clip: true

    /**
    * Item mouse area
    */
    MouseArea
    {
        // common properties
        id: maItem
        objectName: "maItem"
        width: rwItem.implicitWidth
        height: rwItem.implicitHeight

        /// Called when item is double clicked
        onDoubleClicked:
        {
            // expand/collapse item children
            for (let i = 1; i < parent.children.length - 1; ++i)
                parent.children[i].visible = !parent.children[i].visible;

            txItemLabel.m_Text = maItem.getNodeText();
        }

        /**
        * Item background
        */
        Row
        {
            // common properties
            id: rwItem
            objectName: "rwItem"

            /**
            * Item indent
            */
            Item
            {
                // common properties
                width: model.level * 20
                height: 1
            }

            /**
            * Item label
            */
            Text
            {
                // declared properties
                property string m_Text: maItem.getNodeText()

                // common properties
                id: txItemLabel
                objectName: "txItemLabel"
                text: m_Text
                color: clItem.children.length > 2 ? "#3186ea" : "#e9d675"
                font
                {
                    bold: true;
                    pixelSize: 14
                }
            }
        }

        /**
        * Gets the node text
        *@return the node text
        */
        function getNodeText()
        {
            return (clItem.children.length > 2 ?
                            clItem.children[1].visible ?
                                    qsTr("- ") : qsTr("+ ") : qsTr("  ")) + model.treeItem.name;
        }
    }

    /**
    * Children repeater
    */
    Repeater
    {
        // common properties
        model: childArray
        delegate: m_Component
    }
}
