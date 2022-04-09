import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15

/**
* Main form
*@author Jean-Milost Reymond
*/
Window
{
    // advanced properties
    property int m_PageCount: 0

    // common properties
    id: wnMain
    width: 640
    height: 480
    visible: true
    title: qsTr("Dynamic pages")

    /**
    * Buttons background
    */
    Rectangle
    {
        // common properties
        id: rcButtons
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        height: 45
        color: "gray"

        /**
        * Add button
        */
        Button
        {
            // common properties
            id: btAdd
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            text: "Add page"

            /// Called when button is clicked
            onClicked:
            {
                lmViewModel.append({"bgColor": "lightblue", "pageNb": ++m_PageCount});
                slView.currentIndex = slView.count - 1;
            }
        }

        /**
        * Delete button
        */
        Button
        {
            // common properties
            id: btDel
            anchors.left: btAdd.right
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            text: "Delete page"

            /// Called when button is clicked
            onClicked:
            {
                if (!slView.count)
                    return;

                lmViewModel.remove(slView.currentIndex);
            }
        }

        /**
        * Previous button
        */
        Button
        {
            // common properties
            id: btPrev
            anchors.left: btDel.right
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            text: "< Prev"

            /// Called when button is clicked
            onClicked: slView.prevPage()
        }

        /**
        * Next button
        */
        Button
        {
            // common properties
            id: btNext
            anchors.left: btPrev.right
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            text: "Next >"

            /// Called when button is clicked
            onClicked: slView.nextPage()
        }
    }

    /**
    * Page stack model
    */
    ListModel
    {
        // common properties
        id: lmViewModel
    }

    /**
    * Page stack
    */
    StackLayout
    {
        // common properties
        id: slView
        anchors.left: parent.left
        anchors.top: rcButtons.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        /**
        * Page repeater
        */
        Repeater
        {
            // advanced properties
            property int pageNb

            // common properties
            id: rpView
            model: lmViewModel

            /**
            * Page item template
            */
            PageItem
            {
                // advanced properties
                pageBg.color: bgColor
                m_PageNb: pageNb
                m_Index: index  // index provided by Repeater

                /// Called when the component was opened
                Component.onCompleted:
                {
                    // link remove signal between list model and page item
                    remove.connect(lmViewModel.remove);

                    console.log("Page Nb. - " + pageNb + " - " + m_PageNb);
                }
            }
        }

        /**
        * Go to previous page
        */
        function prevPage()
        {
            if (!count)
            {
                currentIndex = -1;
                return;
            }

            let index = currentIndex;

            --index;

            if (index < 0)
                index = count - 1;

            currentIndex = index;
        }

        /**
        * Go to next page
        */
        function nextPage()
        {
            if (!count)
            {
                currentIndex = -1;
                return;
            }

            let index = currentIndex;

            ++index;

            if (index >= count)
                index = 0;

            currentIndex = index;
        }
    }

    /// Called when the main form is loaded
    Component.onCompleted:
    {
        lmViewModel.append({"bgColor": "pink", "pageNb": ++m_PageCount});
    }
}
