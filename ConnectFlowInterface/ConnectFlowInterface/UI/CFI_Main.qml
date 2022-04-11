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

        /**
        * Use curved lines checkbox
        */
        CheckBox
        {
            // common properties
            id: ckUseCurvedLines
            objectName: "ckUseCurvedLines"
            anchors.left: btAdd.right
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            text: "Use curved lines"

            /// Checkbox check mark
            indicator: Rectangle
            {
                id: ckUseCurvedLinesCheck
                objectName: "ckUseCurvedLinesCheck"
                implicitWidth: parent.height
                implicitHeight: parent.height
                x: ckUseCurvedLines.leftPadding
                y: parent.height / 2 - height / 2
                radius: 3
                border.color: ckUseCurvedLines.down ? Styles.m_CheckBoxPressed : Styles.m_CheckBoxDefault

                Rectangle
                {
                    width: parent.width - 4
                    height: parent.height - 4
                    x: 2
                    y: 2
                    radius: 2
                    color: ckUseCurvedLines.down ? Styles.m_CheckBoxPressed : Styles.m_CheckBoxDefault
                    visible: ckUseCurvedLines.checked
                }
            }

            /// Checkbox Text
            contentItem: Text
            {
                id: ckUseCurvedLinesText
                objectName: "ckUseCurvedLinesText"
                anchors.fill: parent
                leftPadding: parent.height + 10
                text: ckUseCurvedLines.text
                font: ckUseCurvedLines.font
                opacity: enabled ? 1.0 : 0.3
                color: Styles.m_LightTextColor
                verticalAlignment: Text.AlignVCenter
            }

            /// Called when button is clicked
            onClicked:
            {
                Styles.m_UseCurvedLines = ckUseCurvedLines.checked;
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
