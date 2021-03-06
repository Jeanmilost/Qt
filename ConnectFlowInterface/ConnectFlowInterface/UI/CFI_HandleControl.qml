import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Control surrounded by handles, which may be moved and resized
*@author Jean-Milost Reymond
*/
T.Control
{
    // aliases
    property alias handleBackground: rcHandleControl

    // advanced properties
    property var    m_Target:            undefined
    property string m_Color:             "transparent"
    property string m_BorderColor:       Styles.m_HandleControlBorderColor
    property string m_HandleColor:       Styles.m_HandleBgColor
    property string m_HandleBorderColor: Styles.m_HandleBorderColor
    property int    m_BorderWidth:       Styles.m_HandleBorderWidth
    property int    m_Radius:            Styles.m_HandleRadius
    property bool   m_HandleVisible:     true

    // common properties
    id: ctHandleControl
    objectName: "ctHandleControl"

    /**
    * Handles control background
    */
    Rectangle
    {
        // common properties
        id: rcHandleControl
        objectName: "rcHandleControl"
        anchors.fill: parent
        color: m_Color
        border.color: m_BorderColor
        border.width: m_BorderWidth
        radius: m_Radius

        /**
        * Control mouse area
        */
        MouseArea
        {
            // advanced proeprties
            property int m_MouseDeltaX: 0
            property int m_MouseDeltaY: 0

            // common properties
            id: maHandleControl
            objectName: "maHandleControl"
            anchors.fill: parent
            cursorShape: Qt.SizeAllCursor
            acceptedButtons: Qt.LeftButton
            hoverEnabled: true
            visible: ctHandleControl.m_HandleVisible

            /// Called when mouse is double-clicked onto the control
            onDoubleClicked: function(mouseEvent)
            {
                if (m_Target)
                    m_Target.dblClick();
            }

            /// Called when mouse is pressed above the control
            onPressed: function(mouseEvent)
            {
                if (m_Target)
                    m_Target.moveStart();

                m_MouseDeltaX = mouseEvent.x - parent.x;
                m_MouseDeltaY = mouseEvent.y - parent.y;
            }

            /// Called when mouse is released after pressed above the control
            onReleased: function(mouseEvent)
            {
                if (m_Target)
                    m_Target.moveEnd();
            }

            /// Called when mouse moved on the x axis above the handle
            onMouseXChanged: function(mouseEvent)
            {
                if (!pressed)
                    return;

                if (m_Target)
                    m_Target.move(mouseX - m_MouseDeltaX, 0);
            }

            /// Called when mouse moved on the y axis above the handle
            onMouseYChanged: function(mouseEvent)
            {
                if (!pressed)
                    return;

                if (m_Target)
                    m_Target.move(0, mouseY - m_MouseDeltaY);
            }
        }

        /**
        * Left handle
        */
        CFI_Handle
        {
            // common properties
            id: haLeftHandle
            objectName: "haLeftHandle"
            x:   parent.x                       - 5
            y: ((parent.y + parent.height) / 2) - (height / 2)
            visible: ctHandleControl.m_HandleVisible

            // advanced proeprties
            m_Target: ctHandleControl.m_Target
            m_Color: ctHandleControl.m_HandleColor
            m_BorderColor: ctHandleControl.m_HandleBorderColor
            m_Direction: CFI_Handle.IEDirection.IE_D_Left
        }

        /**
        * Left and top handle
        */
        CFI_Handle
        {
            // common properties
            id: haLeftTopHandle
            objectName: "haLeftTopHandle"
            x: parent.x - 5
            y: parent.y - 5
            visible: ctHandleControl.m_HandleVisible

            // advanced proeprties
            m_Target: ctHandleControl.m_Target
            m_Color: ctHandleControl.m_HandleColor
            m_BorderColor: ctHandleControl.m_HandleBorderColor
            m_Direction: CFI_Handle.IEDirection.IE_D_LeftTop
        }

        /**
        * Top handle
        */
        CFI_Handle
        {
            // common properties
            id: haTopHandle
            objectName: "haTopHandle"
            x: ((parent.x + parent.width) / 2) - (width / 2)
            y:  parent.y - 5
            visible: ctHandleControl.m_HandleVisible

            // advanced proeprties
            m_Target: ctHandleControl.m_Target
            m_Color: ctHandleControl.m_HandleColor
            m_BorderColor: ctHandleControl.m_HandleBorderColor
            m_Direction: CFI_Handle.IEDirection.IE_D_Top
        }

        /**
        * Right and top handle
        */
        CFI_Handle
        {
            // common properties
            id: haTopRightHandle
            objectName: "haTopRightHandle"
            x: (parent.x + parent.width) - 2
            y:  parent.y                 - 5
            visible: ctHandleControl.m_HandleVisible

            // advanced proeprties
            m_Target: ctHandleControl.m_Target
            m_Color: ctHandleControl.m_HandleColor
            m_BorderColor: ctHandleControl.m_HandleBorderColor
            m_Direction: CFI_Handle.IEDirection.IE_D_RightTop
        }

        /**
        * Right handle
        */
        CFI_Handle
        {
            // common properties
            id: haRightHandle
            objectName: "haRightHandle"
            x:  (parent.x + parent.width)       - 2
            y: ((parent.y + parent.height) / 2) - (height / 2)
            visible: ctHandleControl.m_HandleVisible

            // advanced proeprties
            m_Target: ctHandleControl.m_Target
            m_Color: ctHandleControl.m_HandleColor
            m_BorderColor: ctHandleControl.m_HandleBorderColor
            m_Direction: CFI_Handle.IEDirection.IE_D_Right
        }

        /**
        * Right and bottom handle
        */
        CFI_Handle
        {
            // common properties
            id: haRightBottomHandle
            objectName: "haRightBottomHandle"
            x: (parent.x + parent.width)  - 2
            y: (parent.y + parent.height) - 2
            visible: ctHandleControl.m_HandleVisible

            // advanced proeprties
            m_Target: ctHandleControl.m_Target
            m_Color: ctHandleControl.m_HandleColor
            m_BorderColor: ctHandleControl.m_HandleBorderColor
            m_Direction: CFI_Handle.IEDirection.IE_D_RightBottom
        }

        /**
        * Bottom handle
        */
        CFI_Handle
        {
            // common properties
            id: haBottomHandle
            objectName: "haBottomHandle"
            x: ((parent.x + parent.width) / 2) - (width / 2)
            y:  (parent.y + parent.height)     - 2
            visible: ctHandleControl.m_HandleVisible

            // advanced proeprties
            m_Target: ctHandleControl.m_Target
            m_Color: ctHandleControl.m_HandleColor
            m_BorderColor: ctHandleControl.m_HandleBorderColor
            m_Direction: CFI_Handle.IEDirection.IE_D_Bottom
        }

        /**
        * Left and bottom handle
        */
        CFI_Handle
        {
            // common properties
            id: haBottomLeftHandle
            objectName: "haBottomLeftHandle"
            x:  parent.x                  - 5
            y: (parent.y + parent.height) - 2
            visible: ctHandleControl.m_HandleVisible

            // advanced proeprties
            m_Target: ctHandleControl.m_Target
            m_Color: ctHandleControl.m_HandleColor
            m_BorderColor: ctHandleControl.m_HandleBorderColor
            m_Direction: CFI_Handle.IEDirection.IE_D_LeftBottom
        }
    }
}
