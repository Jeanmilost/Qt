import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Handle, used to resize the control
*@author Jean-Milost Reymond
*/
T.Control
{
    /**
    * Handle moving directions
    */
    enum IEDirection
    {
        IE_D_None,
        IE_D_Left,
        IE_D_LeftTop,
        IE_D_Top,
        IE_D_RightTop,
        IE_D_Right,
        IE_D_RightBottom,
        IE_D_Bottom,
        IE_D_LeftBottom
    }

    // aliases
    property alias handleRect: rcHandle

    // advanced properties
    property var    m_Target:      undefined
    property string m_Color:       Styles.m_HandleBgColor
    property string m_BorderColor: Styles.m_HandleBorderColor
    property int    m_Direction:   IEDirection.IE_D_None

    // common properties
    id: ctHandle
    objectName: "ctHandle"
    width: Styles.m_HandleWidth
    height: Styles.m_HandleHeight

    /**
    * Handle rectangle
    */
    Rectangle
    {
        // common properties
        id: rcHandle
        objectName: "rcHandle"
        anchors.fill: parent
        color: m_Color
        border.color: m_BorderColor
        border.width: Styles.m_HandleBorderWidth
        radius: Styles.m_HandleRadius
    }

    /**
    * Handle mouse area
    */
    MouseArea
    {
        // common properties
        id: maHandle
        objectName: "maHandle"
        anchors.fill: parent
        cursorShape: getCursorShape(ctHandle.m_Direction)
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true

        /// called when mouse moved on the x axis above the handle
        onMouseXChanged:
        {
            if (!pressed)
                return;

            if (m_Target)
                m_Target.resize(m_Direction, mouseX, 0);
        }

        /// called when mouse moved on the y axis above the handle
        onMouseYChanged:
        {
            if (!pressed)
                return;

            if (m_Target)
                m_Target.resize(m_Direction, 0, mouseY);
        }
    }

    /**
    * Gets the cursor shape to show for this handle
    *@param {IEDirection} direction - direction the handle is moving
    *@return cursor shape to show
    */
    function getCursorShape(direction)
    {
        switch (direction)
        {
            case CFI_Handle.IEDirection.IE_D_Left:        return Qt.SizeHorCursor;
            case CFI_Handle.IEDirection.IE_D_LeftTop:     return Qt.SizeFDiagCursor;
            case CFI_Handle.IEDirection.IE_D_Top:         return Qt.SizeVerCursor;
            case CFI_Handle.IEDirection.IE_D_RightTop:    return Qt.SizeBDiagCursor;
            case CFI_Handle.IEDirection.IE_D_Right:       return Qt.SizeHorCursor;
            case CFI_Handle.IEDirection.IE_D_RightBottom: return Qt.SizeFDiagCursor;
            case CFI_Handle.IEDirection.IE_D_Bottom:      return Qt.SizeVerCursor;
            case CFI_Handle.IEDirection.IE_D_LeftBottom:  return Qt.SizeBDiagCursor;
        }

        return Qt.ArrowCursor;
    }
}
