import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Page item
*@author Jean-Milost Reymond
*/
T.Control
{
    // aliases
    property alias pageBg: rcBackground

    // advanced properties
    property int m_PageNb
    property int m_Index

    // common properties
    id: ctPage

    // signals
    signal remove(int index)

    /**
    * Background
    */
    Rectangle
    {
        // common properties
        id: rcBackground
        anchors.fill: parent

        /**
        * Page text
        */
        Text
        {
            // common properties
            id: txText
            anchors.centerIn: parent
            text: "Page %1 - Index %2".arg(m_PageNb).arg(m_Index)
        }

        /**
        * Page mouse area
        */
        MouseArea
        {
            // common properties
            anchors.fill: parent

            /// Called when the page is clicked
            onClicked:
            {
                // remove this page
                remove(m_Index)
            }
        }
    }
}
