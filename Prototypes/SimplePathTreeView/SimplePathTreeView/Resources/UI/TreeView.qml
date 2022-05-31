import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Tree view
*@author JMR
*/
T.Frame
{
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

        /**
        * Tree content model
        */
        ListModel
        {
            // common properties
            id: lmTreeContentModel
            objectName: "lmTreeContentModel"
        }

        /**
        * Tree item component
        */
        Component
        {
            // common properties
            id: cpItem

            /**
            * Tree item content
            */
            TreeItem
            {
                // advanced properties
                m_Component: cpItem
            }
        }

        /**
        * Tree view
        */
        ListView
        {
            // common properties
            anchors.left: parent.left
            anchors.top: rcTreeHeader.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            model: lmTreeContentModel
            delegate: cpItem
            clip: true
        }

        /**
        * Tree view signal connections
        */
        Connections
        {
            // common properties
            target: tmTreeModel

            /**
            * Called when a new item was added to tree
            *@param {TreeItem} parentItem - parent item in which the item was added
            *@param {TreeItem} item - added item
            */
            function onAddItemToView(parentItem, item)
            {
                // is a root node?
                if (!parentItem)
                {
                    // add root node to tree
                    lmTreeContentModel.append({"treeItem":   item,
                                               "level":      0,
                                               "childArray": []});

                    return;
                }

                // search for parent node in which the new node should be added
                var [parentNode, parentLevel] = findNode(parentItem.getId());

                // found it?
                if (!parentNode)
                    return;

                // add node to parent
                parentNode.childArray.append({"treeItem":   item,
                                              "level":      parentLevel + 1,
                                              "childArray": []});
            }
        }
    }

    /**
    * Finds a node from its unique identifier
    *@param {string} uid - node unique identifier to find
    *@return [node, level] array containing the node matching with identifier and its level, [null, -1] if not found or on error
    */
    function findNode(uid)
    {
        var deep = 0;

        // iterate through root items
        for (var i = 0; i < lmTreeContentModel.count; ++i)
        {
            // get root node
            var node = lmTreeContentModel.get(i);

            // must exist
            if (!node)
            {
                console.error("Find item - FAILED - found invalid node - index - " + i + " - uid to find - " + uid);
                continue;
            }

            // found the node?
            if (node.treeItem.getId() === uid)
                return [node, deep];

            // search in children
            var [child, level] = findChild(uid, node, deep + 1);

            // found the node in the children?
            if (child)
                return [child, level];
        }

        return [null, -1];
    }

    /**
    * Finds a child node from its unique identifier
    *@param {string} uid - node unique identifier to find
    "@param {TreeItem} node - parent node to start from
    *@param {int} deep - item deep
    *@return [node, level] array containing the node matching with identifier and its level, [null, -1] if not found or on error
    */
    function findChild(uid, node, deep)
    {
        if (!node)
            return [null, -1];

        // found the node?
        if (node.treeItem.getId() === uid)
            return [node, deep - 1];

        // iterate through children items
        for (var i = 0; i < node.childArray.count; ++i)
        {
            // get child
            var child = node.childArray.get(i);

            // must exist
            if (!child)
            {
                console.error("Find child - FAILED - found invalid child - index - " + i                     +
                              " - parent - "                                         + node.treeItem.getId() +
                              " - uid to find - "                                    + uid);
                continue;
            }

            // search in children
            var [foundChild, level] = findChild(uid, child, deep + 1);

            // found the node in the children?
            if (foundChild)
                return [foundChild, level];
        }

        return [null, -1];
    }
}
