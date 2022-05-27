import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Tree view
*@author JMR
*/
T.Frame
{
    /*REM
    // declared properties
    property string m_PlusItemGlyph:         "qrc:/Resources/Images/plus.svg"
    property string m_MinusItemGlyph:        "qrc:/Resources/Images/minus.svg"
    property int    m_DefTransitionDuration: 0
    property int    m_TransitionDuration:    0
    */
    // declared properties
    property var m_Model: tmTreeModel

    // common properties
    id: frTreeViewFrame
    objectName: "frTreeViewFrame"

    /**
    * Tree view background
    */
    Rectangle
    {
        // common properties
        id: rcTreeViewBg
        objectName: "rcTreeViewBg"
        anchors.fill: parent

        /**
        * Tree header
        */
        Rectangle
        {
            // common properties
            id: rcTreeHeader
            objectName: "rcTreeHeader"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            height: 26
            color: "#f0f0f0"

            /**
            * Add item button
            */
            RoundButton
            {
                // common properties
                id: btAddItem
                objectName: "btAddItem"
                anchors.right: btDeleteItem.left
                anchors.rightMargin: 3
                anchors.verticalCenter: parent.verticalCenter
                width: parent.height - 6
                height: parent.height - 6
                radius: 3
                text: "+"

                /// called when button is clicked
                onClicked:
                {
                    console.log("GUI - Add item clicked");

                    /*FIXME
                    if (m_Model)
                        m_Model.onAddItemClicked(lvTreeView.currentIndex);
                    */
                }
            }

            /**
            * Delete item button
            */
            RoundButton
            {
                // common properties
                id: btDeleteItem
                objectName: "btDeleteItem"
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.verticalCenter: parent.verticalCenter
                width: parent.height - 6
                height: parent.height - 6
                radius: 3
                text: "-"
                enabled: false

                /// called when button is clicked
                onClicked:
                {
                    console.log("GUI - Delete item clicked");

                    /*FIXME
                    if (m_Model)
                        m_Model.onDeleteItemClicked(lvTreeView.currentIndex);
                    */
                }
            }
        }

        /*REM
        Component
        {
            // common properties
            id: cpItem

            Rectangle
            {
                // common properties
                //REM anchors.fill: parent
                width: parent.width
                height: 25
                y: index * 25

                color: index % 2 ? "red" : "blue"
            }
        }
        */

        Component
        {
            id: cpItemContent

            Rectangle
            {
                property string m_Text
                property int    m_Level: 0

                id: rcItemContent
                anchors.fill: parent
                border.width: 1
                color: "red"

                /**
                * Item indent
                */
                Item
                {
                    // common properties
                    id: itItemIndent
                    objectName: "itItemIndent"
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    x: 0
                    width: fcTreeView.m_BlankWidth * m_Level
                }

                Text
                {
                    anchors.left: itItemIndent.right
                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    text: m_Text //REM m_Model.getText(m_ID) // FIXME make a property
                }
            }
        }

        /**
        * Tree view content model
        */
        ListModel
        {
            // common properties
            id: lmTreeViewContent
            objectName: "lmTreeViewContent"
        }

        /**
        * Tree view
        */
        Flickable
        {
            property int m_ItemHeight: 25
            property int m_BlankWidth: 10

            // common properties
            id: fcTreeView
            objectName: "fcTreeView"
            anchors.left: parent.left
            anchors.top: rcTreeHeader.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            focus: true
            clip: true

            contentWidth: width
            contentHeight: m_ItemHeight * 25
            //boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {}

            /*REM
            Repeater
            {
                // common properties
                id: rpItemRepeater
                objectName: "rpItemRepeater"
                model: 25
                delegate: cpItem
            }
            */

            /*REM
            Column
            {
                id: clItem

                Repeater
                {
                    model: 3

                    Row
                    {
                        id: rwItem
                        x: 0

                        Rectangle
                        {
                            width: 200
                            height: 40
                            border.width: 1
                            color: "yellow"
                        }
                    }
                }
            }
            */

            /*REM
            Component
            {
                id: cpItem2

                Column
                {
                    property alias itemContent: rcItem2

                    id: clItem2

                    Row
                    {
                        id: rwItem2
                        leftPadding: 20

                        Rectangle
                        {
                            id: rcItem2
                            width: 200
                            height: 40
                            border.width: 1
                            color: "red"
                        }
                    }
                }
            }
            */

            /*REM
            Component
            {
                // common properties
                id: cpItem

                / **
                * Item column layout
                * /
                Column
                {
                    // declared properties
                    property var m_SourceComponent: cpItemContent
                    property var m_Content:         ldItem.item
                    property int m_ChildrenCount:   0

                    // common properties
                    id: clItem

                    / **
                    * Item row layout
                    * /
                    Row
                    {
                        // common properties
                        id: rwItem

                        / **
                        * Item content loader
                        * /
                        Loader
                        {
                            // common properties
                            id: ldItem
                            objectName: "ldItem"
                            sourceComponent: m_SourceComponent
                            width: fcTreeView.width
                            height: 40
                        }
                    }

                    / **
                    * Item children repeater
                    * /
                    Repeater
                    {
                        // common properties
                        id: rpChildren
                        model: m_ChildrenCount
                        delegate: cpItem
                    }

                    //REM Binding { target: cpItem; property: "model"; value: m_ChildrenCount; when: loader.status == Loader.Ready }


                    function getNb2()
                    {
                        return rpChildren.itemAt(1).m_Content;
                    }

                    function changeNb2(count)
                    {
                        return rpChildren.itemAt(2).m_ChildrenCount = count;
                    }

                    function changeTo5()
                    {
                        return rpChildren.model = 5;
                    }
                }
            }
            */

            /*REM
            Loader
            {
                // common properties
                id: ldRoot
                objectName: "ldRoot"
                //REM sourceComponent: cpItem
            }
            */

            /**
            * Main item repeater
            */
            Repeater
            {
                // common properties
                id: rpMainItem
                objectName: "rpMainItem"
                anchors.fill: parent
                model: lmTreeViewContent

                /**
                * Component loader
                */
                Loader
                {
                    // common properties
                    objectName: loaderId

                    /*REM
                    /// Called when component is loaded
                    Component.onCompleted:
                    {}
                    */
                }
            }

            /*REM
            Repeater
            {
                // common properties
                id: rpMainItem
                objectName: "rpMainItem"
                model: lmTreeViewContent
                delegate: ldMainItem

                Loader
                {
                    // common properties
                    id: ldMainItem
                    objectName: "ldMainItem"
                    //REM sourceComponent: cpItem
                }
            }
            */

            /*REM
            Loader
            {
                id: ldRootItem
                anchors.fill: parent
            }
            */

            /*REM
            Component.onCompleted:
            {
                const itemRootId = "tiRootItem";

                // create a new document view
                ldRoot.setSource("TreeItem.qml", {"id":                itemRootId,
                                                  "objectName":        itemRootId,
                                                  "m_SourceComponent": cpItemContent});

                // succeeded?
                if (!ldRoot.item)
                {
                    console.error("Create root item - FAILED - an error occurred while the item was created");
                    return;
                }

                console.log(ldRoot.item);
                //REM ldRootItem.item.m_ChildrenCount = 5;

                ldRoot.item.m_Item.m_ChildrenCount = 2;

                //REM ldRoot.item.model = 2;
                ldRoot.item.changeTo5();
                ldRoot.item.getNb2().color = "blue";
                //REM ldRoot.item.getNb2().childrenCount = 4;
                ldRoot.item.changeNb2(4);
            }
            */

            /*REM
            Repeater
            {
                // common properties
                id: rpItemRepeater
                objectName: "rpItemRepeater"
                model: 1

                delegate: TreeItem
                {
                    //anchors.left: parent.left
                    //anchors.top: parent.top
                    //anchors.right: parent.right
                    //width: fcTreeView.width
                    //height: 25

                    //m_Width: fcTreeView.width
                    //m_Height: 25
                }
            }
            */
        }

        Connections
        {
            target: tmTreeModel
            ignoreUnknownSignals: true

            function onAddItemToView(parentId, id)
            {
                console.log("parent - " + parentId + " - id - " + id);

                if (!parentId || !parentId.length)
                {
                    // build item loader identifier
                    const loaderId = "ldItem_" + id;

                    // create a loader to load the item
                    lmTreeViewContent.append({"id": loaderId, "loaderId": loaderId});

                    const itemIndex = rpMainItem.count - 1;

                    // get the newly added loader
                    let loader = rpMainItem.itemAt(itemIndex);

                    // found it?
                    if (!loader)
                    {
                        console.error("Add item - an error occurred while the loader was created");
                        return;
                    }

                    // build item identifier
                    const itemId = "itItem_" + id;

                    // load the item
                    loader.setSource("TreeItem.qml", {"id":                itemId,
                                                      "objectName":        itemId,
                                                      "x":                 0,
                                                      "y":                 itemIndex * fcTreeView.m_ItemHeight * 6,
                                                      "width":             fcTreeView.width,
                                                      "height":            fcTreeView.m_ItemHeight * 6,
                                                      "m_ID":              id,
                                                      "m_Model":           m_Model,
                                                      "m_SourceComponent": cpItemContent});

                    // get the loaded item
                    let item = loader.item;

                    // found it?
                    if (!item)
                    {
                        console.error("Add item - an error occurred while the item was created");
                        return;
                    }

                    item.changeTo5();//REM FIXME

                    console.log("Add item - succeeded - new item - " + item.objectName);

                    return;
                }
            }
        }

        /*REM
        / **
        * Tree view item
        * /
        Component
        {
            // common properties
            id: cpItem

            / **
            * Item column layout
            * /
            Column
            {
                property bool m_ContainsChildren: false
                property bool m_ShowExpand:       false
                property bool m_Collapsed:        false

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
                    height: clItem.m_Collapsed ? 0 : lvTreeView.m_ItemHeight

                    / **
                    * Item background
                    * /
                    Rectangle
                    {
                        property int m_BlankWidth: imPlusItemGlyph.visible ? 0 : (imMinusItemGlyph.visible ? 0 : lvTreeView.m_ItemHeight + 5)

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
                            width: rcItemBg.m_BlankWidth + (itemLevel * 20)
                            height: lvTreeView.m_ItemHeight
                        }

                        / **
                        * Plus item glyph
                        * /
                        Image
                        {
                            // common properties
                            id: imPlusItemGlyph
                            objectName: "imPlusItemGlyph"
                            width: lvTreeView.m_ItemHeight
                            anchors.left: itItemIndent.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.margins: 5
                            z: 1
                            source: m_PlusItemGlyph
                            sourceSize: Qt.size(lvTreeView.m_ItemHeight, lvTreeView.m_ItemHeight)
                            fillMode: Image.PreserveAspectFit
                            smooth: true
                            visible: clItem.m_ContainsChildren && clItem.m_ShowExpand

                            MouseArea
                            {
                                anchors.fill: parent
                                acceptedButtons: Qt.LeftButton

                                /// called when item is clicked
                                onClicked:
                                {
                                    lvTreeView.model.setCollapsed(index, false);
                                }
                            }
                        }

                        / **
                        * Minus item glyph
                        * /
                        Image
                        {
                            // common properties
                            id: imMinusItemGlyph
                            objectName: "imMinusItemGlyph"
                            width: lvTreeView.m_ItemHeight
                            anchors.left: itItemIndent.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.margins: 5
                            z: 1
                            source: m_MinusItemGlyph
                            sourceSize: Qt.size(lvTreeView.m_ItemHeight, lvTreeView.m_ItemHeight)
                            fillMode: Image.PreserveAspectFit
                            smooth: true
                            visible: clItem.m_ContainsChildren && !clItem.m_ShowExpand

                            MouseArea
                            {
                                anchors.fill: parent
                                acceptedButtons: Qt.LeftButton

                                /// called when item is clicked
                                onClicked:
                                {
                                    lvTreeView.model.setCollapsed(index, true);
                                }
                            }
                        }

                        / **
                        * Item text
                        * /
                        Text
                        {
                            // common properties
                            id: txItemText
                            objectName: "txItemText"
                            text: itemName
                            anchors.left: imPlusItemGlyph.visible ? imPlusItemGlyph.right : (imMinusItemGlyph.visible ? imMinusItemGlyph.right : itItemIndent.right)
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
                                const moveTime     = (Math.abs(lvTreeView.currentIndex - index) * lvTreeView.m_ItemHeight * 1000) / lvTreeView.highlightMoveVelocity;
                                const durationTime = lvTreeView.highlightMoveDuration > 0 ? lvTreeView.highlightMoveDuration : 0;

                                // calculate the next duration time
                                m_TransitionDuration = (durationTime > 0 && durationTime >= moveTime) ? durationTime : moveTime;

                                // select this item
                                lvTreeView.currentIndex = index;
                            }

                            /// Called when item is double clicked
                            onDoubleClicked:
                            {
                                tmTreeModel.onItemDblClicked(index);
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
                            when: index === lvTreeView.currentIndex
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

        / **
        * Tree view
        * /
        ListView
        {
            // declared properties
            property int m_ItemHeight: 25
            //REM property int m_LastKnownCount: 0

            // common properties
            id: lvTreeView
            objectName: "lvTreeView"
            anchors.left: parent.left
            anchors.top: rcTreeHeader.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            focus: true
            clip: true

            // link properties
            model: tmTreeModel
            delegate: cpItem
            highlight: cpHighlightItem

            / **
            * Vertical scrollbar
            * /
            ScrollBar.vertical: ScrollBar
            {
                // common properties
                id: sbTreeView
                objectName: "sbTreeView"
                parent: lvTreeView
                visible: true
                minimumSize: 0.1
            }

            /// called when the current index changed
            onCurrentIndexChanged:
            {
                updateDeleteItemEnableState();
            }

            /// called when the item count changed
            onCountChanged:
            {
                updateDeleteItemEnableState();
            }

            / **
            * Update the delete item enable state
            * /
            function updateDeleteItemEnableState()
            {
                // enable the delete button only if the view contains more than 1 item
                btDeleteItem.enabled = currentIndex !== 0 && count > 1;
            }
        }
    }

    Connections
    {
        target: tmTreeModel
        ignoreUnknownSignals: true

        / **
        * Called when the tree content changed
        *@aram index - item index which is influenced by the change (i.e. item index on added, parent index on removed)
        * /
        function onTreeContentChanged(index)
        {
            const item = lvTreeView.itemAtIndex(index);

            if (!item)
                return;

            item.m_ContainsChildren = !tmTreeModel.isLeaf(index);
        }

        / **
        * Called when the collapse state changed on an item
        *@param index - item index which collapse state changed
        *@param isParent - if true, the item is the parent which is owning the changing children items
        *@param value - if true, item is collapsed, extended otherwise
        * /
        function onCollapseStateChanged(index, isParent, value)
        {
            const item = lvTreeView.itemAtIndex(index);

            if (!item)
                return;

            if (isParent)
                item.m_ShowExpand = value;
            else
                item.m_Collapsed = value;
        }
        */
    }
}
