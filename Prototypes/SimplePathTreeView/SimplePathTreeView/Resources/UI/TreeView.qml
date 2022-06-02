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

                    if (!m_Model)
                        return;

                    // get the selected node
                    let [selectedNode, selectedNodeLevel, selectedNodeIndex] = getSelectedNode();

                    // no selection?
                    if (!selectedNode)
                    {
                        // notify the model that a new item should be added (but out of selection)
                        m_Model.onAddItemClicked(null, -1);
                        return;
                    }

                    // notify the model that a new item should be added
                    m_Model.onAddItemClicked(selectedNode.treeItem, selectedNodeLevel);
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
                enabled: lmTreeContentModel.count && lvTreeView.m_SelectedItem

                /// called when button is clicked
                onClicked:
                {
                    console.log("GUI - Delete item clicked");

                    if (!m_Model)
                        return;

                    // get the selected node
                    let [selectedNode, selectedNodeLevel, selectedNodeIndex] = getSelectedNode();

                    // no selection?
                    if (!selectedNode)
                        return;

                    // notify the model that the item should be deleted
                    m_Model.onDeleteItemClicked(selectedNode.treeItem, selectedNodeLevel);
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
            // declared properties
            property var m_SelectedItem: null

            // common properties
            id: lvTreeView
            objectName: "lvTreeView"
            anchors.left: parent.left
            anchors.top: rcTreeHeader.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            model: lmTreeContentModel
            delegate: cpItem
            clip: true

            /**
            * Vertical scrollbar
            */
            ScrollBar.vertical: ScrollBar
            {
                // common properties
                id: sbTreeView
                objectName: "sbTreeView"
                parent: lvTreeView
                visible: true
                minimumSize: 0.1
            }

            /**
            * Unselects all the tree nodes
            */
            function unselectAll()
            {
                changeNodeSelection(false);
            }
        }

        /**
        * Tree view signal connections
        */
        Connections
        {
            // common properties
            target: m_Model

            /**
            * Called when a new item was added to tree
            *@param {TreeItem} parentItem - parent item in which the item was added
            *@param {TreeItem} item - added item
            */
            function onAddItemToView(parentItem, item)
            {
                if (!item)
                {
                    console.error("Add item to view - FAILED - item is empty");
                    return;
                }

                // is a root node?
                if (!parentItem)
                {
                    console.log("Add item to view - root - " + item.uid);

                    // add root node to tree
                    lmTreeContentModel.append({"treeItem":   item,
                                               "level":      0,
                                               "selected":   false,
                                               "childArray": []});

                    // todo -cCheck -oJean: This is required otherwise the item is not always visible
                    //                      after added. But I sincerely don't know why
                    lvTreeView.forceLayout();

                    return;
                }

                console.log("Add item to view - parent - " + parentItem.uid + " - item - " + item.uid);

                // search for parent node in which the new node should be added
                var [parentNode, parentLevel, parentIndex] = findNode(parentItem.uid);

                // found it?
                if (!parentNode)
                    return;

                // add node to parent
                parentNode.childArray.append({"treeItem":   item,
                                              "level":      parentLevel + 1,
                                              "selected":   false,
                                              "childArray": []});
            }

            /**
            * Called when an item was removed from tree
            *@param {TreeItem} parentItem - parent item owning the item to remove
            *@param {TreeItem} item - removed item
            */
            function onRemoveItemFromView(parentItem, item)
            {
                if (!item)
                {
                    console.error("Remove item from view - FAILED - item is empty");
                    return;
                }

                // find the node to remove from view
                let [nodeToDel, nodeToDelLevel, nodeToDelIndex] = findNode(item.uid);

                // should always exist
                if (!nodeToDel)
                {
                    console.error("Remove item from view - FAILED - no node is matching with item - id - " + item.uid);
                    return;
                }

                // is a root item?
                if (!parentItem)
                {
                    // remove it from list model
                    lmTreeContentModel.remove(nodeToDelIndex);
                    return;
                }

                // find the parent node owning the node to remove
                let [parentNode, parentNodeLevel, parentNodeIndex] = findNode(parentItem.uid);

                // should always exist
                if (!parentNode)
                {
                    console.error("Remove item from view - FAILED - parent node could not be found - item id - " + item.uid);
                    return;
                }

                // remove item from its parent
                parentNode.childArray.remove(nodeToDelIndex);
            }
        }
    }

    /**
    * Finds a node from its unique identifier
    *@param {string} uid - node unique identifier to find
    *@return [node, level, index] array containing the node matching with identifier and its level
    *                             and index, [null, -1, -1] if not found or on error
    */
    function findNode(uid)
    {
        var deep = 0;

        // iterate through root nodes
        for (var i = 0; i < lmTreeContentModel.count; ++i)
        {
            // get root node
            var node = lmTreeContentModel.get(i);

            // must exist
            if (!node)
            {
                console.error("Find node - FAILED - found invalid node - index - " + i + " - uid to find - " + uid);
                continue;
            }

            // found the node?
            if (node.treeItem.uid === uid)
                return [node, deep, i];

            // search in children
            var [child, level, index] = findChild(uid, node, deep + 1, i);

            // found the node in the children?
            if (child)
                return [child, level, index];
        }

        return [null, -1, -1];
    }

    /**
    * Finds a child node from its unique identifier
    *@param {string} uid - node unique identifier to find
    *@param {TreeItem} node - parent node to start from
    *@param {int} deep - item deep
    *@param {int} nodeIndex - parent node index
    *@return [node, level, index] array containing the node matching with identifier and its level
    *                             and index, [null, -1, -1] if not found or on error
    */
    function findChild(uid, node, deep, nodeIndex)
    {
        if (!node)
            return [null, -1, -1];

        // found the node?
        if (node.treeItem.uid === uid)
            return [node, deep - 1, nodeIndex];

        // iterate through children nodes
        for (var i = 0; i < node.childArray.count; ++i)
        {
            // get child
            var child = node.childArray.get(i);

            // must exist
            if (!child)
            {
                console.error("Find child - FAILED - found invalid child - index - " + i                 +
                              " - parent - "                                         + node.treeItem.uid +
                              " - uid to find - "                                    + uid);
                continue;
            }

            // search in children
            var [foundChild, level, index] = findChild(uid, child, deep + 1, i);

            // found the node in the children?
            if (foundChild)
                return [foundChild, level, index];
        }

        return [null, -1, -1];
    }

    /**
    * Changes the selection state in all nodes
    *@param {bool} selection - if true, all nodes will be selected, otherwise unselected
    */
    function changeNodeSelection(selection)
    {
        // iterate through root nodes
        for (var i = 0; i < lmTreeContentModel.count; ++i)
        {
            // get root node
            var node = lmTreeContentModel.get(i);

            // must exist
            if (!node)
            {
                console.error("Change node selection - FAILED - found invalid node - index - " + i + " - uid to find - " + uid);
                continue;
            }

            // set the node selection state
            node.selected = selection;

            // change the selection in all children
            changeChildSelection(node, selection);
        }
    }

    /**
    * Changes the selection state in all children nodes
    *@param {TreeItem} node - parent node from which the selection should be changed
    *@param {bool} selection - if true, all nodes will be selected, otherwise unselected
    */
    function changeChildSelection(node, selection)
    {
        // no node?
        if (!node)
            return;

        // iterate through children nodes
        for (var i = 0; i < node.childArray.count; ++i)
        {
            // get child
            var child = node.childArray.get(i);

            // must exist
            if (!child)
            {
                console.error("Change child selection - FAILED - found invalid child - index - " + i +
                              " - parent - "                                                     + node.treeItem.uid);
                continue;
            }

            // set the node selection state
            child.selected = selection;

            // change the selection in all children
            changeChildSelection(child, selection);
        }
    }

    /**
    * Gets the currently selected node
    *@return [node, level, index] array containing the selected node and its level and index, [null, -1, -1] if not found or on error
    */
    function getSelectedNode()
    {
        var deep = 0;

        // iterate through root nodes
        for (var i = 0; i < lmTreeContentModel.count; ++i)
        {
            // get root node
            var node = lmTreeContentModel.get(i);

            // must exist
            if (!node)
            {
                console.error("Get selected node - FAILED - found invalid node - index - " + i);
                continue;
            }

            // found the node?
            if (node.selected)
                return [node, deep, i];

            // search in children
            var [child, level, index] = getSelectedChild(node, deep + 1, i);

            // found the node in the children?
            if (child)
                return [child, level, index];
        }

        return [null, -1, -1];
    }

    /**
    * Gets the currently selected child node
    *@param {TreeItem} node - parent node to start from
    *@param {int} deep - item deep
    *@param {int} nodeIndex - parent node index
    *@return [node, level, index] array containing the selected node and its level and index, [null, -1, -1] if not found or on error
    */
    function getSelectedChild(node, deep, nodeIndex)
    {
        if (!node)
            return [null, -1, -1];

        // found the node?
        if (node.selected)
            return [node, deep - 1, nodeIndex];

        // iterate through children nodes
        for (var i = 0; i < node.childArray.count; ++i)
        {
            // get child
            var child = node.childArray.get(i);

            // must exist
            if (!child)
            {
                console.error("Get selected child - FAILED - found invalid child - index - " + i +
                              " - parent - "                                                 + node.treeItem.uid);
                continue;
            }

            // search in children
            var [foundChild, level, index] = getSelectedChild(child, deep + 1, i);

            // found the node in the children?
            if (foundChild)
                return [foundChild, level, index];
        }

        return [null, -1, -1];
    }
}
