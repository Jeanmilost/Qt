import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

/**
* Main application window
*@author Jean-Milost Reymond
*/
ApplicationWindow
{
    // common properties
    id: wiMainWnd
    objectName: "wiMainWnd"
    visible: true
    width: 800
    height: 600
    title: "Connect Flow Interface"

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
            text: "Add box"

            /// Called when button is clicked
            onClicked:
            {
                cfiDocumentModel.addBox();
            }
        }
    }

    /**
    * Document
    */
    CFI_Document
    {
        // common properties
        id: dcDocument
        objectName: "dcDocument"
        anchors.left: parent.left
        anchors.top: rcButtons.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
