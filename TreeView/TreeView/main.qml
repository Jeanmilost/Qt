import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.0

/**
* Main application window
*@author Jean-Milost Reymond, based on Code Project Spandan Sharma article,
*        available here:
*        https://www.codeproject.com/Articles/632795/QML-TreeModel-and-TreeView
*/
ApplicationWindow
{
    // common properties
    id: wiMainWnd
    objectName: "wiMainWnd"
    visible: true
    width: 800
    height: 600
    title: "Tree view"

    /**
    * Background
    */
    Rectangle
    {
        // common properties
        id: rcBackground
        objectName: "rcBackground"
        anchors.fill: parent
        color: "#303234"

        /**
        * Tree model
        */
        ListModel
        {
            // common properties
            id: lmTreeModel
            objectName: "lmTreeModel"
        }

        /**
        * Tree item
        */
        Component
        {
            // common properties
            id: cpItem

            /**
            * Item column layout
            */
            Column
            {
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
                                               qsTr("- ") : qsTr("+ ") : qsTr("  ")) + model.name;
                    }
                }

                /**
                * Children repeater
                */
                Repeater
                {
                    // common properties
                    model: childArray
                    delegate: cpItem
                }
            }
        }

        /**
        * Background layout
        */
        ColumnLayout
        {
            // common properties
            anchors.fill: parent

            /**
            * Tree view
            */
            ListView
            {
                // common properties
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: lmTreeModel
                delegate: cpItem
            }

            /**
            * Input dialog
            */
            Window
            {
                // common properties
                id: objModalInput
                modality: Qt.ApplicationModal
                width: 400
                height: 50
                color: "#101214"
                visible: false

                /**
                * Input label
                */
                Text
                {
                    // common properties
                    id: txInputLabel
                    objectName: "txInputLabel"
                    text: "\"Name\" = root node, <ItemIndex>,<SubItemIndex>,<...>,\"Name\"=child node"
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.right: parent.right
                    height: 20
                    color: "white"
                }

                /**
                * Input edit
                */
                TextInput
                {
                    // common properties
                    anchors.left: parent.left
                    anchors.top: txInputLabel.bottom
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    text: qsTr("node0")
                    font
                    {
                        bold: true;
                        pixelSize: 20
                    }
                    verticalAlignment: TextInput.AlignVCenter
                    horizontalAlignment: TextInput.AlignHCenter
                    color: "white"

                    validator: RegExpValidator
                    {
                        regExp: /(\d{1,},)*.{1,}/
                    }

                    /// Called when focus changed
                    onFocusChanged:
                    {
                        if (focus)
                            selectAll();
                    }

                    /// Called when input should be accepted
                    onAccepted:
                    {
                        if (acceptableInput)
                        {
                            objModalInput.close();

                            let szSplit = text.split(',');

                            if (szSplit.length === 1)
                                lmTreeModel.append({"name": szSplit[0], "level": 0, "childArray": []});
                            else
                            {
                                if (lmTreeModel.get(parseInt(szSplit[0])) === undefined)
                                {
                                    console.log("Error - Given node does not exist !");
                                    return;
                                }

                                let node = lmTreeModel.get(parseInt(szSplit[0]));

                                for (var i = 1; i < szSplit.length - 1; ++i)
                                {
                                    if (node.childArray.get(parseInt(szSplit[i])) === undefined)
                                    {
                                        console.log("Error - Given node does not exist !");
                                        return;
                                    }

                                    node = node.childArray.get(parseInt(szSplit[i]));
                                }

                                node.childArray.append({"name": szSplit[i], "level": i, "childArray": []});
                            }
                        }
                    }
                }
            }

            /**
            * Add item button
            */
            Button
            {
                // common properties
                text: "add data to tree"

                /// Called when button was clicked
                onClicked:
                {
                    objModalInput.show();
                }
            }
        }
    }
}
