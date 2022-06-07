import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

/**
* Main window
*@author Jean-Milost Reymond
*/
ApplicationWindow
{
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
    }
}
