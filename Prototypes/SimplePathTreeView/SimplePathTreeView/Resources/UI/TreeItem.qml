import QtQuick 2.15
import QtQuick.Controls 2.15

/**
* Generic tree item
*@author Jean-Milost Reymond
*/
Column
{
    // declared properties
    property var    m_Component:      null
    property string m_PlusItemGlyph:  "qrc:/Resources/Images/plus.svg"
    property string m_MinusItemGlyph: "qrc:/Resources/Images/minus.svg"

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

        /// Called when item is clicked
        onClicked:
        {
            // unselect all currently selected items
            lvTreeView.unselectAll();

            // select this item
            model.selected = true;
        }

        /// Called when item is double clicked
        onDoubleClicked:
        {
            // expand/collapse item children
            for (let i = 1; i < parent.children.length - 1; ++i)
                parent.children[i].visible = !parent.children[i].visible;
        }

        /**
        * Item row
        */
        Row
        {
            // common properties
            id: rwItem
            objectName: "rwItem"

            /**
            * Item background
            */
            Rectangle
            {
                // common properties
                id: rcItemBg
                objectName: "rcItemBg"
                width: lvTreeView.width
                height: txItemLabelMetrics.height
                color: model.selected ? "#4e8cde" : "transparent"

                /**
                * Item indent
                */
                Item
                {
                    // common properties
                    id: itItemIndent
                    objectName: "itItemIndent"
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: model.level * 20
                    height: 1
                }

                Rectangle
                {
                    // common properties
                    id: rcItemGlyph
                    objectName: "rcItemGlyph"
                    anchors.left: itItemIndent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: height
                    color: "transparent"

                    /**
                    * Plus item glyph
                    */
                    Image
                    {
                        // common properties
                        id: imPlusItemGlyph
                        objectName: "imPlusItemGlyph"
                        anchors.fill: parent
                        anchors.margins: 5
                        source: m_PlusItemGlyph
                        sourceSize: Qt.size(width, height)
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                        visible: clItem.children.length > 2 && !clItem.children[1].visible

                        /**
                        * Glyph mouse area
                        */
                        MouseArea
                        {
                            // common properties
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            cursorShape: Qt.PointingHandCursor

                            /// called when item is clicked
                            onClicked:
                            {
                                // unselect all currently selected items
                                lvTreeView.unselectAll();

                                // select this item
                                model.selected = true;

                                // expand/collapse item children
                                for (let i = 1; i < clItem.children.length - 1; ++i)
                                    clItem.children[i].visible = true;
                            }
                        }
                    }

                    /**
                    * Minus item glyph
                    */
                    Image
                    {
                        // common properties
                        id: imMinusItemGlyph
                        objectName: "imMinusItemGlyph"
                        anchors.fill: parent
                        anchors.margins: 5
                        source: m_MinusItemGlyph
                        sourceSize: Qt.size(width, height)
                        fillMode: Image.PreserveAspectFit
                        smooth: true
                        visible: clItem.children.length > 2 && clItem.children[1].visible

                        /**
                        * Glyph mouse area
                        */
                        MouseArea
                        {
                            // common properties
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            cursorShape: Qt.PointingHandCursor

                            /// called when item is clicked
                            onClicked:
                            {
                                // unselect all currently selected items
                                lvTreeView.unselectAll();

                                // select this item
                                model.selected = true;

                                // expand/collapse item children
                                for (let i = 1; i < clItem.children.length - 1; ++i)
                                    clItem.children[i].visible = false;
                            }
                        }
                    }
                }

                /**
                * Item label
                */
                Text
                {
                    // declared properties
                    property string m_Text: model.treeItem.name

                    // common properties
                    id: txItemLabel
                    objectName: "txItemLabel"
                    anchors.left: rcItemGlyph.right
                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    text: m_Text
                    color: selected ? "white" : "#202020"
                    font
                    {
                        family: "Arial"
                        bold: true;
                        pixelSize: 14
                    }

                    /**
                    * Item label text metrics
                    */
                    TextMetrics
                    {
                        // common properties
                        id: txItemLabelMetrics
                        objectName: "txItemLabelMetrics"
                        text: txItemLabel.text
                        font: txItemLabel.font
                    }
                }
            }
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
