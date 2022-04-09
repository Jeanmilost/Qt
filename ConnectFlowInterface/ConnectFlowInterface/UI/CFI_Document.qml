import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Templates 2.15 as T

/**
* Document view
*@author Jean-Milost Reymond
*/
T.Control
{
    // advanced properties
    property var m_Document: this
    property var m_Model:    cfiDocumentModel

    // common properties
    id: ctDocumentView
    objectName: "ctDocumentView"

    /**
    * Document background
    */
    Rectangle
    {
        // common properties
        id: rcDocumentView
        objectName: "rcDocumentView"
        anchors.fill: parent
        color: Styles.m_DocumentBackground

        /**
        * Page stack model
        */
        ListModel
        {
            // common properties
            id: lmPageStack
            objectName: "lmPageStack"
        }

        /**
        * Page view stack
        */
        StackLayout
        {
            // common properties
            id: slPageStack
            objectName: "slPageStack"
            anchors.fill: parent
            clip: true

            /**
            * Page repeater
            */
            Repeater
            {
                // common properties
                id: rpPageStack
                objectName: "rpPageStack"
                model: lmPageStack

                /**
                * Page template
                */
                CFI_Page
                {
                    // advanced properties
                    id:            pageID
                    objectName:    pageObjName
                    pageProxy.uid: uid
                }
            }
        }
    }

    /**
    * Bind signals from the c++ model to the view
    */
    Connections
    {
        // common properties
        id: cnDocumentView
        objectName: "cnDocumentView"
        target: m_Model

        /**
        * Called when a page should be added to the document view
        *@param {string} uid - page unique identifier to add
        */
        function onAddPageToView(uid)
        {
            addPage(uid);
        }

        /**
        * Called when a page should be removed from the document view
        *@param {string} uid - page unique identifier to remove
        */
        function onRemovePageFromView(uid)
        {
            removePage(uid, true);
        }

        /**
        * Called when a row is inserted
        *@param {QModelIndex} parentIndex - parent index which will own the row(s) to insert
        *@param {QModelIndex} first - first added row index
        *@param {QModelIndex} last - last added row index
        */
        function onRowsInserted(parentIndex, first, last)
        {
            console.log("Page(s) inserted in document - first - " + first + " - last - " + last + " - parent index - " + parentIndex);
        }

        /**
        * Called when row(s) is(are) removed
        *@param {QModelIndex} parentIndex - parent index owning the row(s) to remove
        *@param {QModelIndex} first - first removed row index
        *@param {QModelIndex} last - last removed row index
        */
        function onRowsRemoved(parentIndex, first, last)
        {
            console.log("Page(s) removed from document - first - " + first + " - last - " + last + " - parent index - " + parentIndex);
        }
    }

    /**
    * Creates a new page and adds it to the document view
    *@param {string} uid - page unique identifier
    *@return newly created page, undefined on error
    */
    function addPage(uid)
    {
        try
        {
            // cannot create an page if its uid is invalid
            if (!uid.length)
            {
                console.error("Add page - FAILED - cannot create page if unique identifier is empty");
                return undefined;
            }

            console.log("Add page - uid - " + uid);

            // build page identifier
            const pageId = "paPage_" + uid;

            // add a new page on the stack end
            lmPageStack.append({"uid": uid, "pageID": pageId, "pageObjName": pageId});

            // get the newly added page
            let item = rpPageStack.itemAt(slPageStack.count - 1);

            // found it?
            if (!item || item.pageProxy.uid !== uid)
            {
                console.error("Add page - an error occurred while the view was created");
                return undefined;
            }

            console.log("Add page - succeeded - view name - " + item.objectName);

            return item;
        }
        catch (e)
        {
            console.exception("Add page - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }

        // remove the partially added page, if any
        removePage(uid, false);

        return undefined;
    }

    /**
    * Removes a page from the document view
    *@param {string} uid - page unique identifier
    *@param {bool} verbose - if true, the error and success messages will be logged
    */
    function removePage(uid, verbose)
    {
        try
        {
            // cannot remove a page if its uid is invalid
            if (!uid.length)
                return;

            if (verbose)
                console.log("Remove page - uid - " + uid);

            let pageName;
            let index = -1;

            // iterate through pages
            for (var i = 0; i < rpPageStack.count; ++i)
            {
                // get child
                let child = rpPageStack.itemAt(i);

                if (!child)
                {
                    console.warn("Remove page - invalid child - index - " + i + " - count - " + rpPageStack.count);
                    continue;
                }

                // found the page to delete?
                if (child instanceof TSP_Page && child.pageProxy.uid === uid)
                {
                    // keep the page name for logging
                    pageName = slPageStack.children[i].objectName;

                    // get the page index to delete
                    index = i;

                    break;
                }
            }

            // found the page to delete?
            if (index < 0)
            {
                if (verbose)
                    console.log("Remove page - FAILED - view not found");

                return;
            }

            // delete page
            lmPageStack.remove(index);

            // log deleted page
            if (verbose && pageName && pageName.length)
                console.log("Remove page - view was removed - view name - " + pageName);

            if (verbose)
                console.log("Remove page - succeeded");
        }
        catch (e)
        {
            console.exception("Remove page - exception caught - " + e.message + "\ncall stack:\n" + e.stack);
        }
    }
}
