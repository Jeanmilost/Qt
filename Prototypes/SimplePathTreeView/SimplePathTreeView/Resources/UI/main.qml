import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

/**
* Main window
*@author Jean-Milost Reymond
*/
ApplicationWindow
{
    // FIXME
    property string m_PlusItemGlyph:         "qrc:/Resources/Images/plus.svg"
    property string m_MinusItemGlyph:        "qrc:/Resources/Images/minus.svg"
    property int    m_DefTransitionDuration: 0
    property int    m_TransitionDuration:    0

    // common properties
    id: awMain
    objectName: "awMain"
    visible: true
    width: 640
    height: 480
    title: qsTr("Tree view with c++ model")

    Rectangle
    {
        // common properties
        id: rcMain
        objectName: "rcMain"
        anchors.fill: parent
        color: "#808080"

        /**
        * Tree view
        */
        TreeView
        {
            // common properties
            id: tvTreeView
            objectName: "tvTreeView"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 250
        }






        /*REM
        ListModel
        {
            // common properties
            id: lmTreeModel
            objectName: "lmTreeModel"
        }

        Component
        {
            // common properties
            id: cpItem

            / **
            * Item column layout
            * /
            Column
            {
                property alias itemRepeater: rpItemRepeater
                property alias itemText:     txItemText
                property alias itemContent:  itItem

                property int m_ItemIndex: rcMain.getViewItemIndex(itItem)

                // common properties
                id: clItem
                objectName: "clItem"
                clip: true

                / **
                * Item content
                * /
                Item
                {
                    // common properties
                    id: itItem
                    objectName: "itItem"
                    width: lvTreeView.width
                    height: lvTreeView.m_ItemHeight//clItem.m_Collapsed ? 0 : lvTreeView.m_ItemHeight

                    / **
                    * Item background
                    * /
                    Rectangle
                    {
                        //REM property int m_BlankWidth: 0//FIXME imPlusItemGlyph.visible ? 0 : (imMinusItemGlyph.visible ? 0 : lvTreeView.m_ItemHeight + 5)

                        // common properties
                        id: rcItemBg
                        objectName: "rcItemBg"
                        anchors.fill: parent
                        color: "transparent"

                        / **
                        * Item indent
                        * /
                        Item
                        {
                            // common properties
                            id: itItemIndent
                            objectName: "itItemIndent"
                            width: level * 20 //FIXME rcItemBg.m_BlankWidth + (itemLevel * 20)
                            height: lvTreeView.m_ItemHeight
                        }
                        / **
                        * Item text
                        * /
                        Text
                        {
                            property string m_Text: maItemMouseArea.getNodeText() // FIXME

                            // common properties
                            id: txItemText
                            objectName: "txItemText"
                            text: m_Text//FIXME itemName
                            anchors.left: itItemIndent.right//REM imPlusItemGlyph.visible ? imPlusItemGlyph.right : (imMinusItemGlyph.visible ? imMinusItemGlyph.right : itItemIndent.right)
                            anchors.top: parent.top
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.margins: 5
                            font.family: "Arial"
                            font.pointSize: 9
                            verticalAlignment: Text.AlignVCenter
                            color: "#202020"
                            clip: true
                        }

                        / **
                        * Item mouse area
                        * /
                        MouseArea
                        {
                            // common properties
                            id: maItemMouseArea
                            objectName: "maItemMouseArea"
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton

                            /// called when item is clicked
                            onClicked:
                            {
                                // get the highlight move time and duration time from tree view
                                const moveTime     = (Math.abs(lvTreeView.currentIndex - m_ItemIndex) * lvTreeView.m_ItemHeight * 1000) / lvTreeView.highlightMoveVelocity;
                                const durationTime = lvTreeView.highlightMoveDuration > 0 ? lvTreeView.highlightMoveDuration : 0;

                                // calculate the next duration time
                                m_TransitionDuration = (durationTime > 0 && durationTime >= moveTime) ? durationTime : moveTime;

                                // select this item
                                lvTreeView.currentIndex = m_ItemIndex;
                            }

                            /// Called when item is double clicked
                            onDoubleClicked:
                            {
                                //tmTreeModel.onItemDblClicked(index);

                                // expand/collapse item children
                                for (let i = 0; i < itemRepeater.count; ++i)
                                    itemRepeater.itemAt(i).visible = !itemRepeater.itemAt(i).visible;

                                txItemText.m_Text = maItemMouseArea.getNodeText();
                            }

                            / **
                            * Gets the node text
                            *@return the node text
                            * /
                            // FIXME
                            function getNodeText()
                            {
                                return (itemRepeater.count ?
                                               itemRepeater.itemAt(0).visible ?
                                                       qsTr("- ") : qsTr("+ ") : qsTr("  ")) + name;
                            }
                        }
                    }

                    / **
                    * Component state array
                    * /
                    states:
                    [
                        State
                        {
                            name: "HIGHLIGHTED"
                            when: m_ItemIndex === lvTreeView.currentIndex
                            PropertyChanges {target: txItemText; color: "white"}
                        }
                    ]

                    / **
                    * Transitions between states
                    * /
                    transitions:
                    [
                        Transition
                        {
                            from: "*"; to: ""
                            ColorAnimation {property: "color"; easing.type: Easing.Linear; duration: m_DefTransitionDuration}
                        },
                        Transition
                        {
                            from: "*"; to: "HIGHLIGHTED"
                            ColorAnimation {property: "color"; easing.type: Easing.Linear; duration: m_TransitionDuration}
                        }
                    ]
                }

                / **
                * Children repeater
                * /
                Repeater
                {
                    // common properties
                    id: rpItemRepeater
                    objectName: "rpItemRepeater"
                    model: subNode
                    delegate: cpItem
                }
            }
        }

        / **
        * Tree view highlight
        * /
        Component
        {
            // common properties
            id: cpHighlightItem

            / **
            * Highlight content
            * /
            Item
            {
                // common properties
                id: itHighlightItem
                objectName: "itHighlightItem"
                width: lvTreeView.width
                height: lvTreeView.m_ItemHeight

                / **
                * Highlight background
                * /
                Rectangle
                {
                    // common properties
                    id: rcHighlightItem
                    objectName: "rcHighlightItem"
                    anchors.fill: parent
                    color: "#4e8cde"
                }
            }
        }

        ListView
        {
            property int m_ItemHeight: 25

            // common properties
            id: lvTreeView
            objectName: "lvTreeView"
            anchors.fill: parent

            model: lmTreeModel
            delegate: cpItem
            highlight: cpHighlightItem

            Component.onCompleted:
            {
                // FIXME remove object name
                lmTreeModel.append({"name": "Item 1", / *"objectName": "Item1Obj", * /"level": 0, "subNode": []});

                // get first item
                let node = lmTreeModel.get(0);

                node.subNode.append({"name": "Item 2", / *"objectName": "Item2Obj", * /"level": 1, "subNode": []});
                node.subNode.append({"name": "Item 3", / *"objectName": "Item3Obj", * /"level": 1, "subNode": []});
                node.subNode.append({"name": "Item 4", / *"objectName": "Item4Obj", * /"level": 1, "subNode": []});

                // get second sub-item of the first item
                node = node.subNode.get(1);

                node.subNode.append({"name": "Item 5", / *"objectName": "Item5Obj", * /"level": 2, "subNode": []});
                node.subNode.append({"name": "Item 6", / *"objectName": "Item6Obj", * /"level": 2, "subNode": []});
                node.subNode.append({"name": "Item 7", / *"objectName": "Item7Obj", * /"level": 2, "subNode": []});

                for (var i = 0; i < count; ++i)
                    console.log(children[i].children.length);
            }
        }

        function getViewItemIndex(item)
        {
            let itemIndex = -1;

            / *
            //let itemParent = parent;

            //while (itemParent)
            //{
            //    itemParent = itemParent.parent;
            //}
            console.log("Parent - " + parent + " - parent name - " + parent.itemText.text);
            console.log("test - " + model.count);

            for (let i = 0; i < parent.itemRepeater.count; ++i)
                console.log(parent.itemRepeater.itemAt(i) + " - " + parent.itemRepeater.itemAt(i).itemText.text + " - " + parent.itemRepeater.itemAt(i).subNode);

            //REM let parentRepeater = itemRepeater;

            console.log("Name - " + txItemText.m_Text + " - index - " + itemIndex + " - current - " + lvTreeView.currentIndex);
            * /
            //console.log("Name - " + txItemText.m_Text + " - " + lmTreeModel.count);

            return itemIndex;
        }
    */
    }
}
